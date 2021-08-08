#include "pitches.h"
 
void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
}
 
void loop() {
  if(digitalRead(8)){
    tone(10, NOTE_C5, 10);
  }
  if(digitalRead(7)){
    tone(10, NOTE_D5, 10); 
  }
  if(digitalRead(6)){
    tone(10, NOTE_E5, 10);
  }
  if(digitalRead(5)){
    tone(10, NOTE_F5, 10);
  }
  if(digitalRead(4)){
    tone(10, NOTE_G5, 10);
  }
  if(digitalRead(3)){
    tone(10, NOTE_A5, 10);
  }
  if(digitalRead(2)){
    tone(10, NOTE_B5, 10);
  }
}
