# 2AxisCatLaser
to compile this, you need to have the platform.io extension in visual studio code.

add "src/WifiCredentials.hh" with your actual credentials. See "src/MyWiFi.hh" for a how to.

The ESP will connect to the Wifi and print the IP adress to the connected serial interface. Make sure you configure your router to give it the same IP address every time, so you do not have issues when reconnecting.

The ESP can receive telnet messages to be controlled remotely:
- loop
  - loop=0
  - loop=1 # repeats the selected program 
- prog
  - prog=250 # selects program 250 and runs it 
- posA
  - posA=10 # moves axis A to 10°
- posB
  - posB=5 # moves axis B to 5°
- Laser
  - Laser=0 # Laser off
  - Laser=1 # Laser on

```
└── src
    ├── Decode.cpp   #class to decode the telnet messages
    ├── Decode.hh
    ├── LICENSE
    ├── main.cpp
    ├── MyLaser.cpp  #class to control the laser
    ├── MyLaser.hh
    ├── MyProgramController.cpp  #Interpolation and various example moving programs
    ├── MyProgramController.hh
    ├── MyServo.cpp  #class to control the servos
    ├── MyServo.hh
    ├── MyWiFi.cpp  #class to manage the wifi
    ├── MyWiFi.hh
    └── WifiCredentials.hh 

```

Infos for printing it yourself can be found here: https://www.printables.com/model/415125

