import time
import requests
import pyttsx3
def Weather():
    engine = pyttsx3.init()
    engine.setProperty('voice','english_rp+f4')
    settings = {
        'api_key':'0520df16be489542f0eb4a1fd5f1d307',
        'zip_code':'54900',
        'country_code':'mx',
        'temp_unit':'metric'} #unit can be metric, imperial, or kelvin

    BASE_URL = "http://api.openweathermap.org/data/2.5/weather?appid={0}&zip={1},{2}&units={3}"

    final_url = BASE_URL.format(settings["api_key"],settings["zip_code"],settings["country_code"],settings["temp_unit"])
    weather_data = requests.get(final_url).json()
    
    return(str(weather_data["main"]["temp"]), str(weather_data["main"]["temp_max"]), str(weather_data["main"]["temp_min"]), str(weather_data["weather"][0]["description"]))
def Weather_voice():
    engine = pyttsx3.init()
    engine.setProperty('voice','english_rp+f4')
    settings = {
        'api_key':'0520df16be489542f0eb4a1fd5f1d307',
        'zip_code':'54900',
        'country_code':'mx',
        'temp_unit':'metric'} #unit can be metric, imperial, or kelvin

    BASE_URL = "http://api.openweathermap.org/data/2.5/weather?appid={0}&zip={1},{2}&units={3}"

    final_url = BASE_URL.format(settings["api_key"],settings["zip_code"],settings["country_code"],settings["temp_unit"])
    weather_data = requests.get(final_url).json()
    engine.say("For today")
    engine.runAndWait()
    engine.say("aim expecting")
    engine.say(weather_data["weather"][0]["description"])
    engine.runAndWait()
    engine.say("The current temperature is")
    engine.runAndWait()
    engine.say(str(weather_data["main"]["temp"])+" Degrees")
    engine.runAndWait()
    engine.say("expecting" + str(weather_data["main"]["temp_max"])+ " Degrees")
    engine.runAndWait()
    engine.say("as the highest")
    engine.runAndWait()
    engine.say("And" + str(weather_data["main"]["temp_min"]) + " Degrees")
    engine.runAndWait()
    engine.say("as the lowest")
    engine.runAndWait()
# time.sleep(20) #get new data every 20 seconds