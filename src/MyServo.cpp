#include "MyServo.hh"




    void MyServo::setup(int pin, float home, String name, int minAngle , int maxAngle , int minPulseWidth , int maxPulseWidth ){
        servo.attach(pin, Servo::CHANNEL_NOT_ATTACHED, minAngle*10, maxAngle*10, minPulseWidth, maxPulseWidth);
        angle=NAN;
        this->minAngle=minAngle;
        this->maxAngle=maxAngle;
        this->home = home;
        this->name = name;
        moveAbs(home);

    }
    void MyServo::moveAbs(float position){
        float angleWithinLimits = constrain(position, minAngle, maxAngle);
        servo.write((int)(angleWithinLimits*10));
        angle=angleWithinLimits;
        if (SERIAL_PRINTLN) Serial.println(name + " moves to " + String(angle));
        
    }

    void MyServo::moveRel(float increment){
        if(isnan(angle)){
            ;
        }else{
            moveAbs(angle+increment);
        }
    }
    void MyServo::moveAbsWithDelay(float position){
        moveAbs(position);
        delay(WAIT_TIME_ABS);
    }
    void MyServo::moveRelWithDelay(float increment){
        moveRel(increment);
        delay(WAIT_TIME_REL);
    }

    void MyServo::initMove(){
        moveAbsWithDelay(home);
        while(angle>minAngle){
            moveRelWithDelay(-1);
        }
        while(angle<maxAngle){
            moveRelWithDelay(1);
        }
        moveAbsWithDelay(home);
        
    }

    float MyServo::getAngle() const {
        return angle;
    }