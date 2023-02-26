#pragma once
#ifndef _MYPROGRAMCONTROLLER_HH_
#define _MYPROGRAMCONTROLLER_HH_
#include <MyServo.hh>
#include <MyWiFi.hh>
#include <MyLaser.hh>

class MyProgramController{

    public:
    static const int RANDOM_PROG_NUMBER = 250; 

    MyProgramController(MyServo &servoA, MyServo &servoB, Laser &laser): servoA(servoA),servoB(servoB),laser(laser){};
    void G0(const float servoAPos, const float servoBPos,float override,uint32_t interval);
    void G00(const float servoAPos, const float servoBPos, uint32_t interval);
    void home(bool slow);
    void prog_checkInterval();
    void prog_checkOverride();
    void randomWait();
    void program(const int programnumber);
    void randProgram();
    
    


private:
    const float MAX_SPEED = 0.3; // speed in °/ms
    MyServo &servoA;
    MyServo &servoB;
    Laser &laser;
};

#endif