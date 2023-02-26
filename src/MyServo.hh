#pragma once
#ifndef _MYSERVO_HH_
#define _MYSERVO_HH_
#include <Servo.h>
#include <string>


class MyServo{
    

    public:
    static const uint32_t WAIT_TIME_ABS = 400;
    static const uint32_t WAIT_TIME_REL = 10;
    void setup(int pin, float home, String name, int minAngle = MIN_ANGLE, int maxAngle = MAX_ANGLE, int minPulseWidth = MIN_PULSE_WIDTH, int maxPulseWidth = MAX_PULSE_WIDTH);
    void moveAbs(float position);
    void moveRel(float increment);
    void moveAbsWithDelay(float position);
    void moveRelWithDelay(float increment);
    float getAngle() const;
    void initMove();


    private:
    static const bool SERIAL_PRINTLN = false;
    static const int MIN_ANGLE = 0;
    static const int MAX_ANGLE = 180;
    
    static const int MIN_PULSE_WIDTH = 544;     // the shortest pulse sent to a servo
    static const int MAX_PULSE_WIDTH = 2400;     // the longest pulse sent to a servo
    
    Servo servo;
    float angle, home, minAngle, maxAngle;
    String name;
    



};

#endif