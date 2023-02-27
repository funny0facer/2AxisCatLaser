#include "MyProgramController.hh"






void MyProgramController::G0(const float servoAPos, const float servoBPos,float override = 1.0,uint32_t interval=MyServo::WAIT_TIME_REL){
    float percentage = constrain(override,0.01,1.0);
    float distToTravelA = servoAPos - servoA.getAngle();
    float distToTravelB = servoBPos - servoB.getAngle();
    float TravelLength = max(abs(distToTravelA), abs(distToTravelB));
    float timeForTravel = TravelLength / (MAX_SPEED * percentage); //timeForTravel is 0.0 when servos are already at position
    float intInterval = (float)interval;
    //Serial.println("timeForTravel= " + String(timeForTravel));
    //Serial.println("intInterval= " + String(intInterval));
    if (timeForTravel > intInterval){ 
      distToTravelA = intInterval * distToTravelA / timeForTravel;
      distToTravelB = intInterval * distToTravelB / timeForTravel;
      //Serial.println("distToTravelA= " + String(distToTravelA));
      //Serial.println("distToTravelB= " + String(distToTravelB));
      while (timeForTravel > intInterval) {
        servoA.moveRel(distToTravelA);
        servoB.moveRel(distToTravelB);
        timeForTravel = timeForTravel - intInterval;
        delay(interval);
      }
    }
    servoA.moveAbs(servoAPos);
    servoB.moveAbs(servoBPos);
    delay(interval);
}

void MyProgramController::G00(const float servoAPos, const float servoBPos,uint32_t interval=MyServo::WAIT_TIME_ABS){
  servoA.moveAbs(servoAPos);
  servoB.moveAbs(servoBPos);
  delay(interval);
}

void MyProgramController::home(bool slow=true){
    laser.off();
    if (slow){
      G0(0.0, 0.0, 0.05);
    }else{
      G00(0.0,0.0);
    }
}

void MyProgramController::prog_checkInterval(){

  Serial.println("check Interval Setting");
  // 10 ms liefert ein sinnvolles Ergebnis
  // => default in G0 Funktion
  // => default in MyServo.WAIT_TIME_REL
  home();
  G0(90.0,0.0,1.0,1);
  G0(0.0,0.0,1.0,1);
  delay(2000);
  G0(90.0,0.0,1.0,2);
  G0(0.0,0.0,1.0,2);
  delay(2000);
  G0(90.0,0.0,1.0,4);
  G0(0.0,0.0,1.0,4);
  delay(2000);
  G0(90.0,0.0,1.0,8);
  G0(0.0,0.0,1.0,8);
  delay(2000);
  G0(90.0,0.0,1.0,10);
  G0(0.0,0.0,1.0,10);
  delay(2000);
  G0(90.0,0.0,1.0,20);
  G0(0.0,0.0,1.0,20);
  delay(2000);
  G0(90.0,0.0,1.0,50);
  G0(0.0,0.0,1.0,50);
  home();
  
}

void MyProgramController::prog_checkOverride(){
  Serial.println("check Overrides. 10%, 25%, 50%, 100%");
  home();
  G0(45.0,-75.0,0.1);
  G0(90.0,75.0,0.1);
  G0(0.0,0.0,0.1);
  delay(1000);
  G0(45.0,-75.0,0.25);
  G0(90.0,75.0,0.25);
  G0(0.0,0.0,0.25);
  delay(1000);
  G0(45.0,-75.0,0.5);
  G0(90.0,75.0,0.5);
  G0(0.0,0.0,0.5);
  delay(1000);
  G0(45.0,-75.0);
  G0(90.0,75.0);
  G0(0.0,0.0);
  
  home();
}



void MyProgramController::program(const int programnumber){
  uint32_t timeBetweenPositions = MyServo::WAIT_TIME_ABS;
  Serial.println("Program: " + String(programnumber));
  // servoA [40;80]
  // servoB [-15;15]
  
  switch (programnumber)
  {
  case 1:    
    home();
    delay(timeBetweenPositions);
    servoA.moveAbs(45.0);
    servoB.moveAbs(-90.0);
    laser.off();
    delay(timeBetweenPositions);
    servoA.moveAbs(90.0);
    servoB.moveAbs(0.0);
    laser.off();
    delay(timeBetweenPositions);
    servoA.moveAbs(45.0);
    servoB.moveAbs(90.0);
    laser.off();
    delay(timeBetweenPositions);
    servoA.moveAbs(0.0);
    servoB.moveAbs(0.0);
    laser.off();
    home();
    break;

  case 2:
    home();
    G0(90.0,0.0);
    G0(0.0,0.0);
    delay(2000);
    G0(0.0,90.0);
    G0(0.0,-90.0);
    G0(0.0, 0.0);    
    home();
    break;

  case 3: 
    home();
    G00(50,0,0.1);
    laser.on();
    for (int i=0;i<3;i++){
      G0(45,  5,  0.06);
      G0(40,  0,  0.06);
      G0(45,  -5, 0.06);
      G0(50,  0,  0.06);
    }    
    laser.off();
    delay(random(1,5)*1000);
    G0(60,0,0.1);
    laser.on();
    for (int i=0;i<4;i++){
      G0(55,  -5, 0.06);
      G0(50,  0,  0.06);
      G0(55,  5,  0.06);
      G0(60,  0,  0.06);
    }
    laser.off();
    delay(random(1,6)*1000);
    G0(70,0,0.1);
    laser.on();
    for (int i=0;i<5;i++){
      G0(65,  10, 0.08);
      G0(60,  0,  0.08);
      G0(65,  -10,0.08);
      G0(70,  0,  0.08);
    }
    home();
    break;

  case 4:
    home();
    G0(60,0, 0.10);
    laser.on();
    for (int i=0;i<6;i++){
      G0(60,  10, 0.08);
      G0(80,  5,  0.08);
      G0(70,  -5, 0.08);
      G0(60,  0,  0.08);
    }
    laser.off();
    delay(random(1,6)*1000);
    G0(60,0);
    laser.on();
    for (int i=0;i<5;i++){
      G0(80,  -5, 0.06);
      G0(70,  5,  0.06);
      G0(60,  10, 0.06);
      G0(60,  0,  0.06);
    }
    laser.off();
    home();
    break;

  case 5:
  home();
  G0(65,  0, 0.10);
  laser.on();
  for (int i=0;i<5;i++){
    G0(50,  15,  0.10);
    G0(80, -15,  0.10);
    G0(40,  10,  0.10);
    G0(65,   0,  0.10);
  }
  laser.off();
  delay(random(1,6)*1000);
  laser.on();
  for (int i=0;i<5;i++){
    G0(50,  15,  0.10);
    G0(80, -15,  0.10);
    G0(40,  10,  0.10);
    G0(65,   0,  0.10);
  }
  laser.off();
  home();
  break;

  case 6:
    home();
    G0(51.50,5.00,0.05);
    laser.on();
    for (int i=0; i<7;i++){
      G0(51.50,5.00,0.04);
      G0(52.28,4.92,0.04);
      G0(53.04,4.70,0.04);
      G0(53.75,4.33,0.04);
      G0(54.39,3.83,0.04);
      G0(54.95,3.21,0.04);
      G0(55.40,2.50,0.04);
      G0(55.73,1.71,0.04);
      G0(55.93,0.87,0.04);
      G0(56.00,0.00,0.04);
      G0(55.93,-0.87,0.04);
      G0(55.73,-1.71,0.04);
      G0(55.40,-2.50,0.04);
      G0(54.95,-3.21,0.04);
      G0(54.39,-3.83,0.04);
      G0(53.75,-4.33,0.04);
      G0(53.04,-4.70,0.04);
      G0(52.28,-4.92,0.04);
      G0(51.50,-5.00,0.04);
      G0(50.72,-4.92,0.04);
      G0(49.96,-4.70,0.04);
      G0(49.25,-4.33,0.04);
      G0(48.61,-3.83,0.04);
      G0(48.05,-3.21,0.04);
      G0(47.60,-2.50,0.04);
      G0(47.27,-1.71,0.04);
      G0(47.07,-0.87,0.04);
      G0(47.00,0.00,0.04);
      G0(47.07,0.87,0.04);
      G0(47.27,1.71,0.04);
      G0(47.60,2.50,0.04);
      G0(48.05,3.21,0.04);
      G0(48.61,3.83,0.04);
      G0(49.25,4.33,0.04);
      G0(49.96,4.70,0.04);
      G0(50.72,4.92,0.04);
      G0(51.50,5.00,0.04);
    }
    laser.off();
    home();
    break;
  




  case RANDOM_PROG_NUMBER: //250
    randomSeed(esp_timer_get_time());
    program(random(3,7));
    break;

  case 254:
    prog_checkOverride();
    break;
  
  case 255:
    prog_checkInterval();
    break;

  default:
    ;
    break;
  }

  Serial.println("Program end");
}

void MyProgramController::randProgram(){
    program(RANDOM_PROG_NUMBER);
}

