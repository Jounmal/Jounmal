#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 6, NEO_GRB + NEO_KHZ800);

#define C2  65
#define CS2 69
#define D2  73
#define DS2 78
#define E2  82
#define F2  87
#define FS2 93
#define G2  98
#define GS2 104
#define A2  110
#define AS2 117
#define B2  123
#define C3  131
#define CS3 139
#define D3  147
#define DS3 156
#define E3  165
#define F3  175
#define FS3 185
#define G3  196
#define GS3 208
#define A3  220
#define AS3 233
#define B3  247
#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494
#define C5  523
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988

int trig = 11;
int echo = 12;
int piezo = 10;
int notes_jong[] = { G4, G4, A4, A4, G4, G4, E4, G4, G4, E4, E4, D4, G4, G4, A4, A4, G4, G4, E4, G4, E4, D4, E4, C4 }; 
int jong_len[] = {4,4,4,4,4,4,2,4,4,4,4,2,4,4,4,4,4,4,2,4,4,4,4,2};

int notes_mario[] = { E5, E5, 0, E5, 0, C5, E5, G5, 0, G4 };
int mario_len[] = {8,8,8,8,8,8,4,4,4,4};

int notes_elli[] = { E4, DS4, E4, DS4, E4, B3, D4, C4, A3, C3, E3, G3, B3, E4, GS4, B4, C5 };
int elli_len[] = { 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 4, 4 }; 

int value;
int SenLow = 1023;
int SenHigh = 0;

void playmusic_jong(){
  for(int i=0;i<24;i++){
    tone(piezo,notes_jong[i],1000/jong_len[i]);
    delay(1000/jong_len[i]*1.3);
  }
}

void playmusic_mario() {
  for (int j = 0; j < 10; j ++) {
    tone (piezo,notes_mario[j], 1000/mario_len[j]);
    delay (1000/mario_len[j]*1.3);
  }
}

void playmusic_elli() {
  for (int n = 0; n < 17; n ++) {
    tone (piezo,notes_elli[n], 1000/elli_len[n]);
    delay (1000/elli_len[n]*1.3);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(piezo, OUTPUT);
  Serial.println("start"); 
  noTone(piezo);
  randomSeed(analogRead(0));
  strip.begin();
  strip.show();
  while(millis()>5000){
    value = analogRead(A0);
    if(value > SenHigh) SenHigh = value;
    if(value < SenLow) SenLow = value;
  }
  colorWipe(strip.Color(34, 116, 28), 50);
}

 void loop() {

  value = analogRead(A0);
  int pitch = map(value, SenLow, SenHigh, 50, 40000);
  Serial.println(pitch);
  
  digitalWrite(trig,LOW);
  delayMicroseconds(10);
  digitalWrite(trig,HIGH);

  int a = random(3);
  Serial.print("랜덤 값 : ");
  Serial.println(a);
  
  long distance=pulseIn(echo,HIGH)/58.2;

  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.println("");

  if(pitch <= -30000){
    colorWipe(strip.Color(16, 98, 10), 50);
  }
  if(-30000 < pitch && pitch <= -20000){
    colorWipe(strip.Color(47, 157, 39), 50);
  }
  if(-20000 < pitch && pitch <= -10000){
    colorWipe(strip.Color(71, 200, 62), 50);
  }
  if(-10000 < pitch && pitch <= 0){
    colorWipe(strip.Color(29, 219, 22), 50);
  }
  if(0 < pitch && pitch <= 10000){
    colorWipe(strip.Color(134, 229, 127), 50);
  }
  if(10000 < pitch && pitch <= 20000){
    colorWipe(strip.Color(183, 240, 177), 50);
  }
  if(20000 < pitch){
    colorWipe(strip.Color(206, 251, 201), 50);
  }
  
  if(distance <= 30){
    if(a == 0){
      playmusic_jong();
      Serial.println("재생중인 곡 : 학교 종이 땡땡땡");
      Serial.println("");
    }
    if(a == 1){
      playmusic_mario();
      Serial.println("재생중인 곡 : 마리오");
      Serial.println("");
    }
    if(a == 2){
      playmusic_elli();
      Serial.println("재생중인 곡 : 엘리제를 위하여");
      Serial.println("");
    }
    rainbow(20);
  }
  else{
    noTone(piezo);
  }
  delay(1000);
}

//NeoPixel에 달린 LED를 각각 주어진 인자값 색으로 채워나가는 함수
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
