#include <Servo.h>
#include "MotorDriver.h"

//button pins
int readyButton = 53;
int preMotorButton = 52;
int exitButton = 51;
//led pins
int readyLed = 31;
int offLed = 30;

//deafult states
int readyButtonState = 0;
int preMotorButtonState = 0;
int exitButtonState = 0;

int currentState = 0;
int previousState = 0;

//feed timer setup
long startTime;
long elapsedTime;

//servo setup
Servo ballReleaseServo;
int servoPos = 0;

void setup() {
  pinMode(readyButton,INPUT);
  pinMode(preMotorButton,INPUT);
  pinMode(exitButton,INPUT);
  
  pinMode(readyLed,OUTPUT);
  pinMode(offLed,OUTPUT);
  
  motordriver.init();
  motordriver.setSpeed(255,MOTORA);
  motordriver.setSpeed(255,MOTORB);
  
  ballReleaseServo.attach(33);
  ballReleaseServo.write(servoPos);
  
  Serial.begin(9600);
}

void loop() {
  readyButtonState = digitalRead(readyButton);
  preMotorButtonState = digitalRead(preMotorButton);
  exitButtonState = digitalRead(exitButton);


  if((currentState == LOW && previousState == LOW) ||
        (currentState == HIGH && previousState == HIGH)) {   
    if(readyButtonState == HIGH){
      Serial.println("ready button pressed");
      currentState = HIGH;
      previousState = LOW;
      startTime = millis();
    }
  }
  
  if(currentState == LOW && previousState == HIGH){
    if(readyButtonState == HIGH){
      Serial.println("ready button pressed");
      currentState = HIGH;
      previousState == LOW;
      startTime = millis();
    }
  }
  
  if(currentState == HIGH && previousState == LOW){
    if(readyButtonState == HIGH){
      Serial.println("readButton pressed again");
    }
    if(preMotorButtonState == HIGH){
      Serial.println("preMotorButton pressed");
    }
    if(exitButtonState == HIGH){
      Serial.println("exitButton pressed");
      previousState = currentState;
      currentState = LOW;
      motorStop();
      ballReleaseServo.write(100);
    }
  }

  elapsedTime = millis() - startTime;
  
  
    Serial.println(elapsedTime);
//  Serial.print("currentState: ");
//  Serial.print(currentState);
//  Serial.print(" <> previousState: ");
//  Serial.println(previousState);
    if(currentState == HIGH){
      digitalWrite(readyLed,HIGH);
      digitalWrite(offLed,LOW);
      motordriver.goForward();
    }else{
      digitalWrite(offLed,HIGH);
      digitalWrite(readyLed,LOW);
    }
 
}

void motorStop(){
  motordriver.stop();
  motordriver.goBackward();
  delay(2000);
  motordriver.stop();
}

void errorBlink(){
  digitalWrite(readyLed,LOW);
  digitalWrite(offLed,HIGH);
  delay(100);
  digitalWrite(offLed,LOW);
  delay(100);
}
