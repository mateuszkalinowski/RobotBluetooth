

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor1 = AFMS.getMotor(1); // LEWY PRZEDNI
Adafruit_DCMotor *motor2 = AFMS.getMotor(2); // LEWY TYLNI
Adafruit_DCMotor *motor3 = AFMS.getMotor(3); // PRAWY PRZEDNI
Adafruit_DCMotor *motor4 = AFMS.getMotor(4); // PRAWY TYLNI

Servo servo;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu ukladu na 0x27

char command[20];
int pointer = 0;

boolean driving = false;

unsigned long lastZero = 0;
boolean recordedZero = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4,INPUT);

 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  mySerial.begin(9600);
  mySerial.println("Hello, world?");

  AFMS.begin();  // create with the default frequency 1.6KHz
  servo.attach(9);
  servo.write(90);
}

void loop() {
  boolean val = digitalRead(4);
  Serial.println(val);
   if(val == 0 && driving) {
      if(recordedZero==false) {
        lastZero = millis();
        recordedZero = true;
      }
      else {
        unsigned long now = millis();
        if(now - lastZero > 1000) {
          stop();
          driving = false;
          recordedZero = false;
        }
      }
   }
  if(mySerial.available()) {
    char c = mySerial.read();
    if(c == '\n') {
      command[pointer] = '\0';
      Serial.write(command);
        if(strcmp(command,"CMD+STOP") == 0) {
          stop();
        }
        if(strcmp(command,"CMD+UP") == 0) {
          ride(100,true);
        }
        if(strcmp(command,"CMD+DOWN") == 0) {
          ride(100,false);
        }
        if(strcmp(command,"CMD+RIGHT") == 0) {
          rotate_right(100);
        }

        if(strcmp(command,"CMD+LEFT") == 0) {
          rotate_left(100);
        }

        if(strcmp(command,"CMD+UPRIGHT") == 0) {
          up_right(100);
        }

        if(strcmp(command,"CMD+UPLEFT") == 0) {
          up_left(100);
        }

        if(strcmp(command,"CMD+DOWNRIGHT") == 0) {
          down_right(100);
        }

        if(strcmp(command,"CMD+DOWNLEFT") == 0) {
          down_left(100);
        }
        
        pointer = 0;
    }
    else {
      command[pointer++] = c;
    }
  }  
}

  
