//button pins
int readyButton = 53;
int preMotorButton = 52;

//led pins
int readyLed = 31;
int errorLed = 30;

//deafult states
int readyButtonState = 0;
int preMotorButtonState = 0;

void setup() {
  pinMode(readyButton,INPUT);
  pinMode(preMotorButton,INPUT);
  
  pinMode(readyLed,OUTPUT);
  pinMode(errorLed,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  readyButtonState = digitalRead(readyButton);
  preMotorButtonState = digitalRead(preMotorButton);
  
  if(readyButtonState == HIGH){
    digitalWrite(readyLed, HIGH);
    digitalWrite(errorLed, LOW);
  }else{
    digitalWrite(readyLed, LOW);
    digitalWrite(errorLed, HIGH);
  }
}
