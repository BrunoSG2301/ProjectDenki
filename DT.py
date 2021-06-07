import pyttsx3
from datetime import date, datetime
engine = pyttsx3.init()
engine.setProperty('voice','english_rp+f4')
now = datetime.now()
today = date.today()
def DT_voice():
    date = today.strftime("%B %d")
    year = today.strftime("%Y")
    hour = now.strftime("%H")
    minutes = now.strftime("%M")
    engine.say('Today is ')
    engine.runAndWait()
    engine.say(date)
    engine.runAndWait()
    engine.say('On year')
    engine.runAndWait()
    engine.say(year)
    engine.runAndWait()
    engine.say("Its")
    engine.runAndWait()
    engine.say(hour+"hours")
    engine.runAndWait()
    engine.say("with"+minutes+"minutes")
    engine.runAndWait()

def DT():
    date = today.strftime("%d/%m/%Y")
    time = now.strftime("%H:%M:%S")
    return(date,time)
    