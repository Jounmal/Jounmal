#include <Servo.h>
#include <LedControl.h>

#define DIN 12
#define CLK 10
#define CS 11

LedControl DM(DIN, CLK, CS, 2); 
Servo sv1;
Servo sv2;

byte face_nothing[]={
  0b00000000,
  0b00000000,
  0b00011000,
  0b00111100,
  0b00111100,
  0b00011000,
  0b00000000,
  0b00000000,
};
byte face_happy[]={
  0b00100000,
  0b00110000,
  0b00011000,
  0b00001100,
  0b00001100,
  0b00011000,
  0b00110000,
  0b00100000,
};

byte face_angry1[]={
  0b00000100,
  0b00001100,
  0b00011100,
  0b00011000,
  0b00110000,
  0b01100000,
  0b01100000,
  0b01000000
};

byte face_angry2[]={
  0b01000000,
  0b01100000,
  0b01100000,
  0b00110000,
  0b00011000,
  0b00011100,
  0b00001100,
  0b00000100
};

byte face_sad[]={
  0b00000100,
  0b00111100,
  0b00111100,
  0b00000100,
  0b00000100,
  0b00111100,
  0b00111100,
  0b00000100
};

void setup() {
  DM.shutdown(0, false);
  DM.setIntensity(0, 1);
  DM.clearDisplay(0);
  DM.shutdown(1, false);
  DM.setIntensity(1, 1);
  DM.clearDisplay(1);
  sv1.attach(2);
  sv2.attach(3);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
  Serial.println("start");
  sv1.write(90);
  sv2.write(90);
  
  int size = sizeof(face_nothing)/sizeof(byte);
    for(int i = 0; i < size; i++){
      DM.setRow(0, i, face_nothing[i]);
      DM.setRow(1, i, face_nothing[i]);
      delay(200);
    }
      
}

void loop() {
   
   if(digitalRead(6)==LOW&&digitalRead(7)==LOW){
   int size = sizeof(face_nothing)/sizeof(byte);
    for(int i = 0; i < size; i++){
      DM.setRow(0, i, face_nothing[i]);
      DM.setRow(1, i, face_nothing[i]);
     delay(200);
    }
    sv1.write(90);
    delay(300);
    sv2.write(90);
    delay(300);
  }
  
   if(digitalRead(6)==LOW){
   int size = sizeof(face_happy)/sizeof(byte);
    for(int i = 0; i < size; i++){
      DM.setRow(0, i, face_happy[i]);
      DM.setRow(1, i, face_happy[i]);
     delay(200);
    }
    delay(100);
    sv1.write(180);
    delay(300);
    sv1.write(0);
    delay(300);
    sv1.write(90);
    delay(500);
    sv2.write(0);
    delay(300);
    sv2.write(180);
    delay(300);
    sv2.write(90);
    delay(500);
  }

  if(digitalRead(7)==LOW){
   int size = sizeof(face_sad)/sizeof(byte);
    for(int i = 0; i < size; i++){
      DM.setRow(0, i, face_sad[i]);
      DM.setRow(1, i, face_sad[i]);
     delay(200);
    }
    sv1.write(180);
    delay(300);
    sv2.write(0);
    delay(300);
  }
  
  if(digitalRead(8)==LOW){
   int size = sizeof(face_angry1)/sizeof(byte);
    for(int i = 0; i < size; i++){
      DM.setRow(0, i, face_angry1[i]);
      DM.setRow(1, i, face_angry2[i]);
     delay(200);
    }
    sv1.write(0);
    delay(300);
    sv2.write(90);
    delay(300);
  }

  delay(1000);  
}
