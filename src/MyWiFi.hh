#pragma once
#ifndef _MYWIFI_HH_
#define _MYWIFI_HH_
#include <WiFi.h>
#include <WifiCredentials.hh>
//inside WifiCredentials.hh:
//static const char* ssid     = "TODO: SSID";
//static const char* password = "TODO: PASSWORD";


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
