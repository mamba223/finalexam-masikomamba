import cv2
import tkinter as tk
from tkinter import *
import pyaudio
import speech_recognition as sr
import threading
from PIL import Image, ImageTk  # Ensure Image is imported from PIL

audio_data = None
exit_threads = False


def get_audio():
    global audio_data, exit_threads
    mic = sr.Microphone()
    
    while not exit_threads:
        with mic as source:
            mic.adjust_for_ambient_noise(source)
            audio = mic.listen(source)
            audio_data = audio
        
# Function to access the webcam feed
def webcam_access(label):
    
    global audio_data
    
    vc = cv2.VideoCapture(0)
    vid_cod = cv2.VideoWriter_fourcc(*'mp4v')
    output = cv2.VideoWriter("cam_video.mp4", vid_cod, 20.0, (1280,1080))

    if not vc.isOpened():
        print("Error: Could not open the webcam")
        return

    def update_frame():
        global exit_threads
        rval, frame = vc.read()
        if rval:
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            
            #resize frame to fit the label dimensions
            width = label.winfo_width() 
            height = label.winfo_height() 
            frame = cv2.resize(frame, (1600, 780 ))
            
            # Convert the frame to an ImageTk format
            photo = ImageTk.PhotoImage(image=Image.fromarray(frame))
            label.imgtk = photo
            label.config(image=photo)
        
        # Call the update_frame function again after 15 milliseconds
        if not exit_threads:
            label.after(15, update_frame)
    
    update_frame()


# Function to handle the 'mute' button click
def mute():
    # Add functionality to mute audio (if applicable)
    global audio_data

    audio_thread = threading.Thread(target=get_audio)
    audio_thread.start()

    # Video capture
    label = tk.Label(root)
    label.pack(expand = TRUE, fill=tk.BOTH)
    label.bind('<configure>', lambda e: webcam_access(label))
    #webcam_access(label)

    # Access the audio data while capturing video
    if audio_data:
        # Process audio data (e.g., using r.recognize_google(audio_data))
        pass

# Function to handle the 'close camera' button click
def close_camera():
    global exit_threads

    exit_threads = True  # Signal threads to exit
    cv2.destroyAllWindows()  # Close the OpenCV window
    root.destroy()  # Close the tkinter window

# Function to set up the tkinter GUI
def layout():
    global root
    root = tk.Tk()
    root.geometry('750x550')
    root.minsize(200,200)
    
    root.grid_rowconfigure(0, weight=1)
    root.grid_rowconfigure(1, weight=0)
    root.grid_columnconfigure(0, weight=1)
    root.grid_columnconfigure(1, weight=0)

    
    label = tk.Label(root)
    label.pack()
    webcam_access(label)
    
    button_frame = tk.Frame(root, padx = 30, pady= 30)
    button_frame.pack(fill=tk.BOTH, expand = True)
    #button_frame.grid(row=1, column=0, sticky='ew')  # Place the frame in row 1, spanning across the width

    button1 = Button(root, text="Mute", fg="blue", command=mute)
    button1.pack(side=tk.LEFT, padx=10)  # Use pack to add the button to the window
    
    button2 = Button(root, text="Close Camera", fg="blue", command=close_camera)
    button2.pack(side=tk.LEFT, padx= 10)  # Use pack to add the button to the window
    
      # Create a frame for the video feed
    video_frame = tk.Frame(root)
    #video_frame.grid(row=0, column=0, sticky='nsew')  # Place the frame in row 0, spanning across all columns

    # Simulating the video feed with a label
    video_label = tk.Label(video_frame, text="Video Feed", bg="lightgray", width=40, height=10)
    video_label.pack()
    
    root.mainloop()

# Entry point of the program
if __name__ == "__main__":
    # Run the layout function to start the tkinter GUI
    layout()
