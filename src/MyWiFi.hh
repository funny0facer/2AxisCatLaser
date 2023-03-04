#pragma once
#ifndef _MYWIFI_HH_
#define _MYWIFI_HH_
#include <WiFi.h>
#include <WifiCredentials.hh>
//inside WifiCredentials.hh:
//#pragma once
//#ifndef _CREDENTIALS_HH_
//#define _CREDENTIALS_HH_
//static const char* ssid     = "TODO";
//static const char* password = "TODO";
//#endif



class MyWiFi{
    private:
    bool duringOperation;
    
    public:
    const int serverPort = 23; //Telnet
    WiFiServer server;
    WiFiClient client;
    void setup();
    void keepAlive();
};

#endif
