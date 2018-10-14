#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <ESP8266WiFi.h>
#include <WiFiManager.h>

class NetworkManager
{
public:
    static NetworkManager* instance(void);
    void connect(char const *apName, char const *apPassword);

private:
    const char*   PING_HOST  = "google.com";
    const uint8_t PING_TRIES = 1;

    WiFiManager* wifiManager;
    bool hasInternet = false;

    NetworkManager();
};

#endif // NETWORK_MANAGER_H
