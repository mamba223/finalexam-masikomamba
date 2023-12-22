import pyttsx3
import speech_recognition as sr
import webbrowser  
import datetime  
import wikipedia 
import pyaudio
import requests
from bs4 import BeautifulSoup, SoupStrainer
from gtts import gTTS
import os
import time
import http.client
import re
 
def search_and_read_aloud(query):
    google_search_url = f"https://www.google.com/search?q={query}"
    webbrowser.open(google_search_url)
    
    # Assuming you have a function takeCommand() to listen for commands
    speaking = True
    while speaking:
        result = takeCommand().lower()
        if "stop" in result:
            speaking = False
        else:
            # Use pyttsx3 to read out the result
            engine = pyttsx3.init()
            engine.say(result)
            engine.runAndWait()

 
# this method is for taking the commands
# and recognizing the command from the
# speech_Recognition module we will use
# the recongizer method for recognizing
def takeCommand():
    r = sr.Recognizer()
    
    mic = sr.Microphone()
    

    # Using a context manager to handle the microphone
    with mic as source:
        print('Listening...')
         
        # Adjusting pause_threshold for potential better recognition
        r.pause_threshold = 0.5  # You might tweak this based on your environment

        # Adjusting the energy_threshold for ambient noise levels
        r.energy_threshold = 4000  # You might need to adjust this for your environment

        # Adding a timeout for listening
        try:
            # Listening to the microphone
            audio = r.listen(source)  # Timeout set to 5 seconds

            print("Recognizing...")
             
            # Using Google's speech recognition to recognize the audio
            Query = r.recognize_google(audio, language='en-in')
            print("The command is:", Query)
             
        except sr.UnknownValueError:
            print("Sorry, I couldn't understand that.")
            return "None"
        except sr.RequestError as e:
            print("Request error; check your internet connection.")
            return "None"
        except Exception as e:
            print(e)
            print("Say that again, please.")
            return "None"
         
        return Query
 
def speak(audio):
     
    engine = pyttsx3.init()
    # getter method(gets the current value
    # of engine property)
    voices = engine.getProperty('voices')
     
    # setter method .[0]=male voice and 
    # [1]=female voice in set Property.
    engine.setProperty('voice', voices[1].id)
     
    # Method for the speaking of the assistant
    engine.say(audio)  
     
    # Blocks while processing all the currently
    # queued commands
    engine.runAndWait()
 
 
def Hello():
     
    # This function is for when the assistant 
    # is called it will say hello and then 
    # take query
   speak("hello sir I am your desktop assistant." +
       "Tell me how may I help you")

def text_to_speech(text):
    tts = gTTS(text=text, lang='en')
    tts.save("result.mp3")
    os.system("start result.mp3")
    

 
def Take_query():
 
    # calling the Hello function for 
    # making it more interactive
    Hello()
     
    # This loop is infinite as it will take
    # our queries continuously until and unless
    # we do not say bye to exit or terminate 
    # the program
    while(True):
         
        # taking the query and making it into
        # lower case so that most of the times 
        # query matches and we get the perfect 
        # output
        query = takeCommand().lower()
         
        if "open google" in query:
            speak("Opening Google ")
            webbrowser.open("www.google.com")
            continue
            

        elif "search on google" in query:
            speak("What do you want to search on Google?")
            search_query = takeCommand().lower()
        
            google_search_url = f"https://www.google.com/search?q={search_query}"
            webbrowser.open(google_search_url)
            continue
         
        elif "play on google" in query:
         speak("What video do you want to play on Google?")
         video_name = takeCommand().lower()
    
         # Generate the Google search URL for the video on YouTube
         google_search_url = f"https://www.google.com/search?q={video_name.replace(' ', '+')}+site%3Ayoutube.com"
    
         # Send a GET request to fetch the HTML content
         response = requests.get(google_search_url, headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36 Edge/16.16299'})

    
         # Parse the HTML content using BeautifulSoup
         soup = BeautifulSoup(response.text, 'html.parser')
    
         # Find the first search result link pointing to YouTube
         search_results = soup.find_all('a', href=True)
         video_link = None
    
         for link in search_results:
             href = link.get('href', '')
             if 'youtube.com' in href and 'watch' in href:
                 video_link = href
                 break
    
         if video_link:
             # Open the found YouTube video link in the browser
             webbrowser.open(video_link)



        elif "from wikipedia" in query:
             
            # if any one wants to have a information
            # from wikipedia
            speak("Checking the wikipedia ")
            query = query.replace("wikipedia", "")
             
            # it will give the summary of 4 lines from 
            # wikipedia we can increase and decrease 
            # it also.
            result = wikipedia.summary(query, sentences=10)
            speak("According to wikipedia")
            speak(result)
            
        elif "play on youtube" in query:
            speak("What video do you want to play on YouTube?")
            video_name = takeCommand().lower()
            
            # Generate the YouTube search URL for the video
            youtube_search_url = f"https://www.youtube.com/results?search_query={video_name.replace(' ', '+')}"
            webbrowser.open(youtube_search_url)
            
        # Inside the 'Take_query' function, replace the relevant portion with this:
        elif "what" in query or "who" in query or "how" in query or "when" in query:
            search_query = takeCommand().lower()  # Assuming takeCommand() gets the search query
            google_search_url = f"https://www.google.com/search?q={search_query}"
            webbrowser.open(google_search_url)
            # Add code here to read first 10 lines or perform additional actions based on search
            continue
        
        
        elif "Hey" in query or "hey" in query or "hello" in query or "Hello" in query:
            speak("Hello, what can I can do for you")
            search_query = takeCommand().lower()  # Assuming takeCommand() gets the search query
            google_search_url = f"https://www.google.com/search?q={search_query}"
            webbrowser.open(google_search_url)
            continue



        elif "tell me your name" in query:
            speak("I am Mamba. Your desktop Assistant")
            

 
if __name__ == '__main__':
     
    # main method for executing
    # the functions
    Take_query()
    
