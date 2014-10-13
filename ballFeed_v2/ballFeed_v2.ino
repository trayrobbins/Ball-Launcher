//added stop button
//added premotor detection
//added shut off if ball doesnt reach motor

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
int shutOffState = 0;
int errorState = 0;
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
  motordriver.setSpeed(100,MOTORA);
  motordriver.setSpeed(255,MOTORB);
  
  ballReleaseServo.attach(49);
  ballReleaseServo.write(servoPos);
  
  Serial.begin(9600);
}

void loop() {
  readyButtonState = digitalRead(readyButton);
  preMotorButtonState = digitalRead(preMotorButton);
  exitButtonState = digitalRead(exitButton);
  ballReleaseServo.write(90);

  if((currentState == LOW && previousState == LOW) ||
        (currentState == HIGH && previousState == HIGH)) {   
    if(readyButtonState == HIGH){
      Serial.println("ready button pressed");
      currentState = HIGH;
      previousState = LOW;
      startTime = millis();
      errorState = LOW;
    }
  }
  
  if(currentState == LOW && previousState == HIGH){
    if(readyButtonState == HIGH){
      Serial.println("ready button pressed");
      currentState = HIGH;
      previousState == LOW;
      startTime = millis();
      errorState=LOW;
    }
  }
elapsedTime = millis() - startTime;
 
  if(currentState == HIGH && previousState == LOW){
    if(readyButtonState == HIGH){
      Serial.println("readButton pressed again");
    }
    if(preMotorButtonState == HIGH){
      shutOffState = LOW;
      startTime = millis();
      Serial.println("preMotorButton pressed");
    }
    if(exitButtonState == HIGH){
      Serial.println("exitButton pressed");
      previousState = currentState;
      currentState = LOW;
      motorStop();
      preMotorButtonState = LOW;
    }
  }
  if(elapsedTime >5000 && currentState == HIGH){
    Serial.println("error - Stopping motor");
    errorState = HIGH;
    currentState = LOW;
  }
  
  while(errorState==HIGH){
    motordriver.stop();
    digitalWrite(offLed,HIGH);
    delay(100);
    digitalWrite(offLed,LOW);
    delay(100);
  }
    Serial.print("elapsedTime: ");
    Serial.print(elapsedTime);
    Serial.print("---- errorState: ");
    Serial.println(errorState);
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
  delay(100);
  motordriver.stop();
}

void errorBlink(){
  digitalWrite(readyLed,LOW);
  digitalWrite(offLed,HIGH);
  delay(100);
  digitalWrite(offLed,LOW);
}
