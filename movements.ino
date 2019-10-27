void turn_right(int speed){
  motor1->setSpeed(speed);
  motor2->setSpeed(speed);
  motor1->run(FORWARD);
  motor2->run(FORWARD);

  motor3->run(RELEASE);
  motor4->run(RELEASE);
  
}

void turn_left(int speed){
  motor3->setSpeed(speed);
  motor4->setSpeed(speed);
  motor3->run(FORWARD);
  motor4->run(FORWARD);

  motor1->run(RELEASE);
  motor2->run(RELEASE);
  
}

void ride(int speed, bool direction,byte time){
    motor1->setSpeed(speed+5); 
    motor2->setSpeed(speed+5);  
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

    if(time>0) {
      delay(time);
      stop();
    }
}

void stop() {
  motor1->run(RELEASE);
  motor2->run(RELEASE);
  motor3->run(RELEASE);
  motor4->run(RELEASE);
}
