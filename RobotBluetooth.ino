#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "constants.h"

#define Trig 7 
#define Echo 6

SoftwareSerial mySerial(10, 11); // RX, TX
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor1 = AFMS.getMotor(1); // LEWY PRZEDNI
Adafruit_DCMotor *motor2 = AFMS.getMotor(2); // LEWY TYLNI
Adafruit_DCMotor *motor3 = AFMS.getMotor(3); // PRAWY PRZEDNI
Adafruit_DCMotor *motor4 = AFMS.getMotor(4); // PRAWY TYLNI

Servo servo;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Ustawienie adresu wyświetlacza na 0x27

char command[20]; //bufor na komendę
byte pointer = 0; //ilość dotychczas wczytanych znaków komendy

bool driving = false;
bool sendDistance = true;
byte currentMove = 0; //aktualny "typ" ruchu (lewo, prawo, przód...), patrz "contants.h"

boolean receivingCommand = false;

unsigned long lastTime = 0;

byte speed = 100;

int distance;
long return_time;

void setup() {
  randomSeed(analogRead(0));
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4,INPUT);

  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(13,OUTPUT);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  mySerial.begin(9600);
  delay(100);

  AFMS.begin();  
  servo.write(90);
  servo.attach(8);
  servo.write(90);
  servo.detach();
  
  lcd.begin(16,2); 
  lcd.clear();
  lcd.noBacklight();
  lcd.setCursor(0,0);
  lcd.print("RobotBluetoothv1");
}

void loop() {
  measure_distance();
  unsigned long now = millis();

  if (sendDistance == true) {
    if(now - lastTime > 2000) {
      lastTime = now;
      mySerial.print("MSG,DST");
      mySerial.print(distance);
    }
  }
  if(mySerial.available()) {
    char c = mySerial.read();
    if(c == '\n' && receivingCommand) {
     command[pointer] = '\0';
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Received command:");
     lcd.setCursor(0,1);
     lcd.print(command);

     Serial.println(command);
              
      if(strncmp(command+1,"MOV,",4) == 0) {
        if(strcmp(command+5,"STOP") == 0) {
          stop();
        }
        else if(strcmp(command+5,"UP") == 0) {
          ride(speed,true);
          currentMove = MOVE_UP;
        }
        else if(strcmp(command+5,"DOWN") == 0) {
          ride(speed,false);
          currentMove = MOVE_DOWN;            
        }
        else if(strcmp(command+5,"LEFT") == 0) {
          rotate_left(speed);
          currentMove = MOVE_LEFT;            
        }
        else if(strcmp(command+5,"RIGHT") == 0) {
          rotate_right(speed);
          currentMove = MOVE_RIGHT;            
        }
        else if(strcmp(command+5,"UPRIGHT") == 0) {
          up_right(speed);
          currentMove = MOVE_UPRIGHT;          
        }
        else if(strcmp(command+5,"UPLEFT") == 0) {
          up_left(speed);
          currentMove = MOVE_UPLEFT; 
        }
        else if(strcmp(command+5,"DOWNRIGHT") == 0) {
          down_right(speed);
          currentMove = MOVE_DOWNRIGHT;            
        }
        else if(strcmp(command+5,"DOWNLEFT") == 0) {
          down_left(speed);
          currentMove = MOVE_UPLEFT;
        }
      }
      
      if(strncmp(command+1,"SPD,",4) == 0) {
        int i = strlen(command);
        int numberLength = i - 5;
        int destinationSpeed = 0;
        int j = 0;
        for(i = strlen(command)-1; i >= strlen(command) - numberLength;i--) {
          int tmp = command[i] - '0';
          destinationSpeed = destinationSpeed + (tmp * pow(10,j++));  
        }
        speed = destinationSpeed;
        changeSpeed();
      }
      
      if(strncmp(command+1,"SND,",4) == 0) {
        if(strcmp(command+5,"1") == 0) {
          tone(13, 261, 200); 
          delay(200);
          tone(13, 220, 200); 
          delay(200);
          tone(13, 246, 300); 
        }
        else if(strcmp(command+5,"2") == 0) {
          tone(13, 2000, 100); 
        }
        else if(strcmp(command+5,"3") == 0) {
          tone(13, 3000, 100); 
        }
        else if(strcmp(command+5,"4") == 0) {
          tone(13, 4000, 100); 
        }
      }

      if(strncmp(command+1,"DST,",4) == 0) {
        int i = strlen(command);
        int numberLength = i - 5;
        int destinationDistanceSensorPosition = 0;
        int j = 0;
        for(i = strlen(command)-1; i >= strlen(command) - numberLength;i--) {
          int tmp = command[i] - '0';
          destinationDistanceSensorPosition = destinationDistanceSensorPosition + (tmp * pow(10,j++));  
        }
        servo.write(destinationDistanceSensorPosition);
      }
      if(strncmp(command+1,"DSB,",4) == 0) {
        if(strcmp(command+5,"ON") == 0) {
          lcd.backlight();
        }
        else if(strcmp(command+5,"OFF") == 0) {
          lcd.noBacklight();
        }
      }  
      if(strncmp(command+1,"DSN,",4) ==0) {
        if(strcmp(command+5,"TRUE") == 0) {
          sendDistance = true;
        }
        else if(strcmp(command+5,"FALSE") == 0) {
          sendDistance = false;
        }
      }
      pointer = 0;
      receivingCommand = false;
    }
    else {
      if(receivingCommand) {
        command[pointer++] = c;
      }
    }
    
    if(receivingCommand == false) {
      if(c == ';'||c == 'O') {
        receivingCommand = true;
        command[pointer++] = c;
      }
    }
    
    if(pointer == 7) {
      if(strncmp(command,"OK+LOST",7) == 0) {
       bluetooth_disconnected();
      }
      if(strncmp(command,"OK+CONN",7) == 0) {
       bluetooth_connected();
      }
    }
    
  }  
}




  
