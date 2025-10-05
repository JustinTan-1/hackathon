#include <Servo.h> // Include the Servo
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

Servo myservoLeft;  // Create a servo object to control the servo
Servo myservoRight;  // Create a servo object to control the servo
int pos = 0;    // Variable to store the servo position

void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);

  pinMode(D5, OUTPUT);
 
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
 
 
  delay(100);
  lcd.clear();
  if(analogRead(A0) < 960){
    lcd.setCursor(0,0);
    lcd.print("Danger,");

    lcd.setCursor(0,1);
    lcd.print("leak detected. ");
   
    analogWrite(D5, 50);
  }
  else{
    lcd.print("Monitoring...");
    analogWrite(D5, 0);
  }
  lcd.display();

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
