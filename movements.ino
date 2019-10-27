void rotate_right(int speed){
  driving = true;
  motor1->setSpeed(speed);
  motor2->setSpeed(speed);
  motor3->setSpeed(speed);
  motor4->setSpeed(speed);
  
  motor1->run(FORWARD);
  motor2->run(FORWARD);
  motor3->run(BACKWARD);
  motor4->run(BACKWARD);
  
}

void rotate_left(int speed){
  driving = true;
  motor1->setSpeed(speed);
  motor2->setSpeed(speed);
  motor3->setSpeed(speed);
  motor4->setSpeed(speed);
  
  motor3->run(FORWARD);
  motor4->run(FORWARD);

  motor1->run(BACKWARD);
  motor2->run(BACKWARD);
  
}

void up_left(int speed){
  driving = true;
  motor3->setSpeed(speed);
  motor4->setSpeed(speed);
  motor3->run(FORWARD);
  motor4->run(FORWARD);

  motor1->run(RELEASE);
  motor2->run(RELEASE);
  
}

void down_left(int speed){
  driving = true;
  motor3->setSpeed(speed);
  motor4->setSpeed(speed);
  motor3->run(BACKWARD);
  motor4->run(BACKWARD);

  motor1->run(RELEASE);
  motor2->run(RELEASE);
  
}

void up_right(int speed){
  driving = true;
  motor1->setSpeed(speed);
  motor2->setSpeed(speed);
  motor1->run(FORWARD);
  motor2->run(FORWARD);

  motor3->run(RELEASE);
  motor4->run(RELEASE);
  
}

void down_right(int speed){
  driving = true;
  motor1->setSpeed(speed);
  motor2->setSpeed(speed);
  motor1->run(BACKWARD);
  motor2->run(BACKWARD);

  motor3->run(RELEASE);
  motor4->run(RELEASE);
  
}
void ride(int speed, bool direction){
  driving = true;
    motor1->setSpeed(speed); 
    motor2->setSpeed(speed);  
    motor3->setSpeed(speed);
    motor4->setSpeed(speed);

    if(direction == true) {
      motor1->run(FORWARD);
      motor2->run(FORWARD);
      motor3->run(FORWARD);
      motor4->run(FORWARD);
    }
    else {
      motor1->run(BACKWARD);
      motor2->run(BACKWARD);
      motor3->run(BACKWARD);
      motor4->run(BACKWARD);
    }
}

void stop() {
  driving = false;
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
}
