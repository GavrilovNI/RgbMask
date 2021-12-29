#pragma once

#include <WiFi.h>


class WifiManager
{
private:
    String lastWifiName;
    String lastWifiPassword;

public:
    
    void connect(String name, String password, unsigned long timeout = 5000)
    {
        lastWifiName = name;
        lastWifiPassword = password;

        WiFi.mode(WIFI_STA);
        WiFi.begin(name.c_str(), password.c_str());

        unsigned long beginTime = millis();
        unsigned long currTime, timePast;
        do
        {
            currTime = millis();
            timePast = currTime - beginTime;
            delay(100);
        }
        while(isConnected() == false && timePast < timeout);
    }

    void reconnect(unsigned long timeout = 5000) {
        connect(lastWifiName, lastWifiPassword, timeout);
    }

    bool setUpAccessPoint(String name, String password = "")
    {
        return WiFi.softAP(name.c_str(), password.c_str());
    }

    void disconnect()
    {
        WiFi.disconnect();
    }

    void stopAccesPoint()
    {
        WiFi.softAPdisconnect(true);
    }

    bool isConnected()
    {
        return WiFi.status() == WL_CONNECTED;
    }

    bool isAccessPoint()
    {
        return WiFi.getMode() & WIFI_MODE_AP;
    }

    IPAddress getAccessPointIp() {
        return WiFi.softAPIP();
    }

    IPAddress getLocalIp() {
        return WiFi.localIP();
    }
};
