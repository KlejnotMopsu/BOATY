#include <Servo.h>
Servo myservo;
 
void setup() {
  Serial.begin(9600);
  myservo.attach(10);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(7, HIGH);
}
 
char cmd[100];
byte cmdIndex;
int throttle = 0;

 
void exeCmd() {
 
  if (cmd[0] == 's') {
    unsigned int val = atof(cmd + 2);
    myservo.write(val);
  }

  if (cmd[0] == 't') {
    unsigned int val = atof(cmd + 2);
    throttle = val;
  }

  if (cmd[0] == 'e') {
    digitalWrite(7, HIGH);
  }

  if (cmd[0] == 'd') {
    digitalWrite(7, LOW);
  }
}

 
void loop() {
  
  analogWrite(6, throttle);
  if (Serial.available() > 0)
  {
    char c = (char)Serial.read();
    if (c == '\n') {
      cmd[cmdIndex] = 0;
      exeCmd();
      cmdIndex = 0;
    } else {
      cmd[cmdIndex] = c;
      if (cmdIndex < 99) cmdIndex++;
    }
  }
 
 
 
  

}
