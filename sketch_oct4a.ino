#include <Servo.h> // Include the Servo library

Servo myservoLeft;  // Create a servo object to control the servo
Servo myservoRight;  // Create a servo object to control the servo
int pos = 0;    // Variable to store the servo position

void setup() {
  Serial.begin(9600);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  myservoRight.attach(D3);
  myservoLeft.attach(D4); 
  myservoRight.write(90);
  myservoLeft.write(90); 
}

void loop() {
   //Scan from 0 degrees to 180 degrees
 int sensorValue = digitalRead(D7);
 int BtnValue = digitalRead(D8);

 if(sensorValue==1)
  {  
    myservoRight.write(180);
    myservoLeft.write(-180);
  } 
  if(Serial.available() > 0){
        myservoRight.write(90);
        myservoLeft.write(90);  
      while(true){}
  }
 
  if(BtnValue==1){
     while(Serial.available() > 0){
      Serial.read();
  }
    //Send value to python
    int valueToSend = 123; 
    Serial.println(valueToSend);
  }
}