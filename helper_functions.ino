void changeSpeed(){
  if(driving){
    if(currentMove == MOVE_UP) {
      ride(speed,true);
    }
    else if(currentMove == MOVE_DOWN) {
      ride(speed,false);
    }
    else if(currentMove == MOVE_RIGHT) {
      rotate_right(speed);
    }
    else if(currentMove == MOVE_LEFT) {
      rotate_left(speed);
    }
    else if(currentMove == MOVE_UPRIGHT) {
      up_right(speed);
    }
    else if(currentMove == MOVE_DOWNRIGHT) {
      down_right(speed);
    }
    else if(currentMove == MOVE_DOWNLEFT) {
      down_left(speed);
    }
    else if(currentMove == MOVE_UPLEFT) {
      up_left(speed);
    }
    
  }
}

void bluetooth_connected() {
    pointer = 0;
    receivingCommand = false;
    lcd.begin(16,2); 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bluetooth");
    lcd.setCursor(0,1);
    lcd.print("Connected");
    
    //DEFAULT STATE
    speed = 100;
    servo.write(90);
    sendDistance = true;
    lcd.backlight();
}

void bluetooth_disconnected() {
    pointer = 0;
    receivingCommand = false;
    lcd.begin(16,2); 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bluetooth");
    lcd.setCursor(0,1);
    lcd.print("Disconnected");
    if(driving)
      stop();
}
