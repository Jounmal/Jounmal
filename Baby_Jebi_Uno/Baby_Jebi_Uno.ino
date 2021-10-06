// [라이브러리]
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <dht11.h>
#include <Wire.h>

// [전선 번호]
#define DHT11pin 2
#define TXD 5
#define RXD 6
#define C5  523
#define Ob_Sen 12

// [DC모터]
#define dcA1A 9
#define dcA1B 3
#define dcB1A 11
#define dcB1B 10

int mspd = 250;
char command;
int piezo = 7;

bool sw = false;
float temp = 50;
float humi = 99;
int pie;

// [구조체 선언]
dht11 DT11;
LiquidCrystal_I2C lcd(0x27,16,2);
SoftwareSerial BTSerial(TXD, RXD);

// [BTSerial] 
char data=0;

// [piezo]
int notes[] = { C5,C5,C5,C5 };
int len[] = { 2,2,2,2 }; 

void playmusic(){
  for(int i=0;i<4;i++){
    tone(piezo,notes[i],1000/len[i]);
    delay(1000/len[i]*1.3);
  }
}

void setup() {
  // [Serialbegin]
  Serial.begin(9600);
  Serial.println("start");
  
  // [1cd 준비]
  lcd.init();
  lcd.backlight();
  
  // [BTSerial]
  BTSerial.begin(9600);

  // [DC 모터]
  analogWrite(dcA1A, 0);
  analogWrite(dcA1B, 0);
  analogWrite(dcB1A, 0);
  analogWrite(dcB1B, 0);

  // [piezo]
  noTone(piezo);

  // [IR]
  pinMode(Ob_Sen, INPUT);
}

void loop() {
  if(digitalRead(Ob_Sen) == 1){
    playmusic();
    Stop();
    delay(1000);
  }
  Serial.println(pie);
  
   // [BTSerial]
   if (BTSerial.available()>0){
    char command= BTSerial.read();
    Serial.println(command);
//  }

  //if (Serial.available()>0){
  //  BTSerial.write(Serial.read());
   // command = Serial.read();
    //Serial.println(command);
    
    if( command == 'F') {
     forward();
    }

    if( command == 'B') {
     back();
    }

    if( command == 'L') {
     left();
    }

    if( command == 'R') {
     right();
    }

    if( command == 'S') {
     Stop();
    }

    if( command == 'O'){
      pie = 1;
    }

    if( command == 'X'){
      pie = 0;
    }
  }
  // [온습도 센서]
  int chk = DT11.read(DHT11pin);
  switch (chk)
  {
    case DHTLIB_OK:
    Serial.print("OK,\t");
    break;
    case DHTLIB_ERROR_CHECKSUM:
    Serial.println("Checksum error,\t");
    break;
    case DHTLIB_ERROR_TIMEOUT:
    Serial.println("Time out error,\t");
    break;
    default:
    Serial.println("Unknown error,\t");
    break;
  }
  
  float h = DT11.humidity;
  float t = DT11.temperature;

  // [SerialPrint]
  Serial.print("Humidity(%) : "); 
  Serial.println(h,2);  
  Serial.print("Temperature(%) : ");
  Serial.println(t,2);

  lcd.setCursor(0,0);
  lcd.print("Humid : ");
  lcd.print(h,2);
  lcd.print("%");
  if(h >= 80){
    lcd.setCursor(8,0);
    lcd.print("Danger  ");
    if(pie == 1){
      playmusic();
    }
  }
  lcd.setCursor(0,1);
  lcd.print("Temp : ");
  lcd.print(t,2);
  lcd.print("'C");
  if(t >= 30){
    lcd.setCursor(7,1);
    lcd.print("Danger   ");
    if(pie == 1){
      playmusic();
    }
  }

  String data = String(h) + "," + String(t);
  
  BTSerial.println(data);
  
  delay(1000);
  
}
   
void forward()  {
  analogWrite(dcA1A, 0);
  analogWrite(dcA1B, mspd);
  analogWrite(dcB1A, mspd);
  analogWrite(dcB1B, 0);
}

void back()  {
  analogWrite(dcA1A, mspd);
  analogWrite(dcA1B, 0);
  analogWrite(dcB1A, 0);
  analogWrite(dcB1B, mspd);
}

void left()  {
  analogWrite(dcA1A, mspd);
  analogWrite(dcA1B, 0);
  analogWrite(dcB1A, mspd);
  analogWrite(dcB1B, 0);
}

void right()  {
  analogWrite(dcA1A, 0);
  analogWrite(dcA1B, mspd);
  analogWrite(dcB1A, 0);
  analogWrite(dcB1B, mspd);
}

void Stop()  {
  analogWrite(dcA1A, 0);
  analogWrite(dcA1B, 0);
  analogWrite(dcB1A, 0);
  analogWrite(dcB1B, 0);
}
