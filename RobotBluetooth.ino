

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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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
  if(mySerial.available()) {
    char c = mySerial.read();
    if(c == '\n') {
      command[pointer] = '\0';
        if(strcmp(command,"CMD+UP") == 0) {
          Serial.println("tak");
        }
        pointer = 0;
    }
    else {
      command[pointer++] = c;
    }
  }  
}

  
