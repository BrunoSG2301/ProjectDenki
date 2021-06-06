import os
import sys, getopt
import signal
import time
import pygame
import os
from RPi import GPIO
from gpiozero import Button
from time import sleep
from Media_player import Media_player as MP
from edge_impulse_linux.audio import AudioImpulseRunner
aion = Button(18)
runner = None

def signal_handler(sig, frame):
    print('Interrupted')
    if (runner):
        runner.stop()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

def help():
    print('python Main.py <path_to_model.eim> <audio_device_ID, optional>' )

def main(argv):
    print(argv)
    try:
        opts, args = getopt.getopt(argv, "h", ["--help"])
    except getopt.GetoptError:
        help()
        sys.exit(2)

    for opt, arg in opts:
        if opt in ('-h', '--help'):
            help()
            sys.exit()

    if len(args) == 0:
        help()
        sys.exit(2)

    model = args[0]

    dir_path = os.path.dirname(os.path.realpath(__file__))
    modelfile = os.path.join(dir_path, model)

    with AudioImpulseRunner(modelfile) as runner:
        try:
            prev_cmd = ""
            cmd = ""
            state = "off"
            model_info = runner.init()
            labels = model_info['model_parameters']['labels']
            print('Loaded runner for "' + model_info['project']['owner'] + ' / ' + model_info['project']['name'] + '"')

            #Let the library choose an audio interface suitable for this model, or pass device ID parameter to manually select a specific audio interface
            selected_device_id = None
            if len(args) >= 2:
                selected_device_id=int(args[1])
                print("Device ID "+ str(selected_device_id) + " has been provided as an argument.")

            for res, audio in runner.classifier(device_id=selected_device_id):    
                if aion.is_pressed:
                    command = []
                    keys = []
                    prev_cmd = cmd
                    for label in labels:
                        score = res['result']['classification'][label]
                        command.append(label)
                        keys.append(score)
                    cmd = command[keys.index(max(keys))]
                    if cmd != prev_cmd:
                        print('Result (%d ms.) ' % (res['timing']['dsp'] + res['timing']['classification']), end='')
                        print('%s: %.2f\t' % (cmd,max(keys)),end='')
                        print(state, end='')
                        print('', flush=True)
                    if cmd == "call":
                        state = "on"
                    elif cmd == "bye":
                        state = "off"
                    
                    if state == "on":
                        if cmd == "play music":
                            MP("control","play", None)
                        if cmd == "pause":
                            MP("control","ps", None)
                        if cmd == "next":
                            MP("control","nxt", None)
                        if cmd == "prev":
                            MP("control","prv", None)
                        if cmd == "rewind":
                            MP("control","rew", None)
                        if cmd == "stop":
                            MP("control","stp", None)
                else:
                    print("AI off")

        finally:
            if (runner):
                runner.stop()

if __name__ == '__main__':
    MP("init", None, None)
    main(sys.argv[1:])
