import numpy as np
import cv2
import face_recognition
import serial
import time

cap = cv2.VideoCapture(0)
example_face = face_recognition.load_image_file("./assets/Justin.jpg")
example_face_encoding = face_recognition.face_encodings(example_face)[0]

known_face_encodings = [
    example_face_encoding
]

known_face_names = [
    "Operator 1"
]

face_locations = []
face_encodings = []
face_names = []

process_frame = True

t = 0
PORT = "/dev/ttyACM0"         
BAUD = 9600

while True:
    # ret -> did it work?
    # frame -> actual image
    ret, frame = cap.read()
    if process_frame:

        resized = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)
        rgb_frame = cv2.cvtColor(resized , cv2.COLOR_BGR2RGB)

        face_locations = face_recognition.face_locations(rgb_frame)
        face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)
        
        face_names = []
        for encoding in face_encodings:
            matches = face_recognition.compare_faces(known_face_encodings, encoding)
            name = "Unknown"
            face_distances = face_recognition.face_distance(known_face_encodings, encoding)
            best_index = np.argmin(face_distances)
            if matches[best_index]:
                name = known_face_names[best_index]
                t = 1
            face_names.append(name)
    for name, (top,right,bottom,left) in zip(face_names, face_locations):
        top *= 4
        right *= 4
        bottom *= 4
        left *= 4
        cv2.rectangle(frame, (left, top), (right, bottom), (0,0,225), 2)
        cv2.putText(frame, name, (left, bottom + 20), cv2.FONT_HERSHEY_COMPLEX, 0.5, (0,0,255), 1)
    
    if t == 1:
        try:
            with serial.Serial(PORT, BAUD, timeout=1) as arduino:
                time.sleep(2)
                message = f"{t}\n"   
                arduino.write(message.encode('utf-8'))
                print("Sent:", t)
        except Exception as e:
            print(e)
    t = 0 
     
    cv2.imshow("frame", frame)
    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

