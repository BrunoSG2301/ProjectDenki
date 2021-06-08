import serial
import time 
import os
import sys, getopt
import signal
import time
import pygame
import os
import pyttsx3
from DT import DT, DT_voice
from datetime import date
from Weather import Weather , Weather_voice
from RPi import GPIO
from gpiozero import Button
from time import sleep
from Media_player import Media_player as MP
from edge_impulse_linux.audio import AudioImpulseRunner
aion = Button(18)
runner = None
engine = pyttsx3.init()
engine.setProperty('voice','english_rp+f4')
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
            auto_nxt = False
            model_info = runner.init()
            labels = model_info['model_parameters']['labels']
            print('Loaded runner for "' + model_info['project']['owner'] + ' / ' + model_info['project']['name'] + '"')

            #Let the library choose an audio interface suitable for this model, or pass device ID parameter to manually select a specific audio interface
            selected_device_id = None
            if len(args) >= 2:
                selected_device_id=int(args[1])
                print("Device ID "+ str(selected_device_id) + " has been provided as an argument.")

            for res,audio in runner.classifier(device_id=selected_device_id):
                if aion.is_pressed:
                    command = []
                    keys = []
                    for label in labels:
                        score = res['result']['classification'][label]
                        command.append(label)
                        keys.append(score)
                    prev_cmd = cmd
                    cmd = command[keys.index(max(keys))]
                    if cmd != prev_cmd and max(keys) > 0.80:
                        if cmd == "call":
                            state = "on"
                            pygame.mixer.music.set_volume(pygame.mixer.music.get_volume()//2)
                            engine.say('Hi Driver, How Can I Help You')
                            engine.runAndWait()
                            pygame.mixer.music.set_volume((pygame.mixer.music.get_volume()+1)*2)
                    
                        if state == "on":
                            if cmd == "play music":
                                MP("control","play", None)
                                auto_nxt = True
                                if pygame.mixer.music.get_busy():
                                    pass
                                else:
                                    state = "off"
                            elif cmd == "pause":
                                MP("control","ps", None)
                                state = "off"
                            elif cmd == "next":
                                MP("control","nxt", None)
                            elif cmd == "prev":
                                MP("control","prv", None)
                            elif cmd == "rewind":
                                MP("control","rew", None)
                                state = "off"
                            elif cmd == "stop":
                                MP("control","stp", None)
                                state = "off"
                            elif cmd == "bye":
                                pygame.mixer.music.set_volume(pygame.mixer.music.get_volume()/2)
                                engine.say('Goodbye, See you later')
                                engine.runAndWait()
                                state = "off"
                                pygame.mixer.music.set_volume((pygame.mixer.music.get_volume()+0.1)*2)
                            elif cmd == "sad":
                                pygame.mixer.music.set_volume(pygame.mixer.music.get_volume()/2)
                                engine.say('Im sorry to hear that')
                                engine.runAndWait()
                                engine.say('Hope this cheers you up')
                                engine.runAndWait()
                                MP("list","plist", "Joy")
                                pygame.mixer.music.set_volume((pygame.mixer.music.get_volume()+0.1)*2)
                                state = "off"
                            elif cmd == "relax":
                                pygame.mixer.music.set_volume(pygame.mixer.music.get_volume()/2)
                                engine.say('You need to calm down')
                                engine.runAndWait()
                                engine.say('Hope this could help')
                                engine.runAndWait()
                                MP("list","plist", "Relax")
                                pygame.mixer.music.set_volume((pygame.mixer.music.get_volume()+0.1)*2)
                                state = "off"
                            elif cmd == "weather":
                                pygame.mixer.music.set_volume(pygame.mixer.music.get_volume()/2)
                                Weather_voice()
                                print(Weather())
                                pygame.mixer.music.set_volume((pygame.mixer.music.get_volume()+0.1)*2)
                                state = "off"
                            elif cmd == "date":
                                pygame.mixer.music.set_volume(pygame.mixer.music.get_volume()/2)
                                DT_voice()
                                print(DT())
                                pygame.mixer.music.set_volume((pygame.mixer.music.get_volume()+0.1)*2)
                                state = "off"
                        
                        print('Result (%d ms.) ' % (res['timing']['dsp'] + res['timing']['classification']), end='')
                        print(cmd)
                        print('%.2f\t' % (max(keys)),end='')
                        print(state, end='')
                        print('', flush=True)
                        sleep(0.5) 
                else:
                    print("AI off")
                    state = "off"
                    #nombre del dispositivo serial: dsmesg | grep -v disconnect | grep -Eo "tty(ACM|USB)." |tail -1
                    portSerial =  serial.Serial('/dev/ttyACM0',9600)
                    portSerial.flushInput()
                    while True:
                        try:
                            dataInput = portSerial.readline()
                            dataBus = dataInput.decode('latin-1').strip() # decodifica el valor para poder ser leid
                            print(dataBus)
                            time.sleep(0.5)
                            if dataBus == "stop":
                                MP("control","stp", None)
                                actualSong = MP("control","gs", None).encode('latin-1')
                                portSerial.write(actualSong)
                                
                            elif dataBus == "play":
                                MP("control","play", None)
                                actualSong = MP("control","gs", None).encode('latin-1')
                                portSerial.write(actualSong)
                            elif dataBus == "pause":
                                MP("control","ps", None)
                                actualSong = MP("control","gs", None).encode('latin-1')
                                portSerial.write(actualSong)
                            elif dataBus == "rewind":
                                MP("control","rew", None)  
                                actualSong = MP("control","gs", None).encode('latin-1')
                                portSerial.write(actualSong)
                            elif dataBus == "next":
                                MP("control","nxt", None)
                                actualSong = MP("control","gs", None).encode('latin-1')
                                portSerial.write(actualSong)
                            elif dataBus == "preview":
                                MP("control","prv", None)
                                actualSong = MP("control","gs", None).encode('latin-1')
                                portSerial.write(actualSong)
                            elif dataBus == "random":
                                MP("control","random", None)
                                actualSong = MP("control","gs", None).encode('latin-1')
                                portSerial.write(actualSong)
                        except KeyboardInterrupt:
                            print("\n Interrupt by Ctrl+C")
                            break
                    
                if pygame.mixer.music.get_busy() == False and auto_nxt == True:
                        MP("control","nxt", None)
        finally:
            if (runner):
                runner.stop()

if __name__ == '__main__':
    MP("init", None, None)
    main(sys.argv[1:])
