#include<Servo.h>

const int pingPin = 7;
int servoPin = 8;
int sensorValue = 0;

Servo servo1;



void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  servo1.attach(servoPin);
  
 
  
 
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A5,OUTPUT);
  
}

void loop() {
  
  long duration, inches, cm;

  pinMode(pingPin, OUTPUT);
  
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
 
  digitalWrite(12,LOW);

 
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  
  
  servo1.write(0);
  
  if(cm < 40)
  {
    servo1.write(90);
    delay(2000);
  }
  else
  {
    servo1.write(0);
  }
  
  // bulb
  int pir = digitalRead(10);
  int ldrvalue= analogRead(A0);
  
  if(pir == HIGH && ldrvalue<10)
  {
    digitalWrite(13,HIGH);
    delay(1000);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  
  //fan
  
  int reading = analogRead(A1);
  float voltage = reading * 5.0;
  voltage /= 1024.0; 
  float temperatureC = (voltage - 0.5) * 100 ;
  if(temperatureC >= 20 && pir == HIGH)
  {
    analogWrite(11,5000);
  }
  else
  {
    digitalWrite(11,LOW);
  }
  
  //fire alarm
  
  sensorValue = analogRead(A2);
  
  if (sensorValue > 250) {
    
    digitalWrite(12, HIGH);
    digitalWrite(A5,HIGH);
  }
  else if(sensorValue <=199) {
   
    digitalWrite(12, LOW);
    digitalWrite(A5,LOW);
  }
  
  
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
