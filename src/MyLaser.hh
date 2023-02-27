#ifndef _MYLASER_H_
#define _MYLASER_H_
#include <Arduino.h>
class Laser{
    

    public:
    void setup(int OutputPin);
    void on();
    void off();
    void onWithDelay();
    void offWithDelay();
    void setState(bool controlState);
    bool getState() const;
    bool toogleState();

    private:
    static const bool SERIAL_PRINTLN = false;
    static const uint32_t WAIT_TIME = 50;

    bool state;
    uint8_t pin;

};

#endif