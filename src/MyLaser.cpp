#include "MyLaser.hh"

    

    void Laser::setup(int OutputPin){
        state=false;
        pin=OutputPin;
        pinMode(pin, OUTPUT);
        
    }

    void Laser::on(){
        digitalWrite(pin, HIGH);
        state=true;
        if (SERIAL_PRINTLN) Serial.println("Laser On");
    }
    void Laser::off(){
        digitalWrite(pin, LOW);
        state=false;
        if (SERIAL_PRINTLN) Serial.println("Laser Off");
    }

    void Laser::onWithDelay(){
        on();
        delay(WAIT_TIME);
    }
    void Laser::offWithDelay(){
        off();
        delay(WAIT_TIME);
    }

    void Laser::setState(bool controlState){
        if(controlState){
            on();
        }else{
            off();
        }
    }

    bool Laser::getState() const{
        return state;
    }

    bool Laser::toogleState(){
        if (state){
            off();
        }else{
            on();
        }
        return state;
    }
