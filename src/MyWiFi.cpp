#include "MyWiFi.hh"



void MyWiFi::setup(){
    // We start by connecting to a WiFi network
    server = WiFiServer(serverPort);
    Serial.print("WiFi: Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    keepAlive();
    Serial.println("WiFi: connected");
    Serial.print("WiFi: IP address: ");
    Serial.println(WiFi.localIP()); 
    Serial.println("");
    server.begin();
    duringOperation=true;
}
void MyWiFi::keepAlive(){
    uint wifiAttempts = 0;
    bool wasNotConnected=false;
    if ((WiFi.status() != WL_CONNECTED) && duringOperation){
        Serial.println("WiFi reconnect");
        server.end();
        wasNotConnected=true;
    }
    // attempt to connect to Wifi network:
    while(WiFi.status() != WL_CONNECTED) 
    {
        // Connect to WPA/WPA2 network.
        delay(500);
        Serial.print(".");
        wifiAttempts++;
        if (wifiAttempts > 10){
            Serial.println("WiFi: New attempt");
            WiFi.disconnect(true,false);
            delay(100);
            WiFi.begin(ssid, password);
            wifiAttempts=0;
        }
        
    }

    if (wasNotConnected && duringOperation){
        Serial.println("WiFi: Server connected again");
        server.begin();
    }
    
   
}
