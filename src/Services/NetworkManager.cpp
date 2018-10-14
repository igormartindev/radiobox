#include "NetworkManager.h"
#include <ESP8266Ping.h>


NetworkManager::NetworkManager()
{
    wifiManager = new WiFiManager();
}

NetworkManager* NetworkManager::instance(void)
{
    static NetworkManager instance;
    return &instance;
}

void NetworkManager::connect(char const *apName, char const *apPassword)
{
    wifiManager->autoConnect(apName, apPassword);

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println();
    Serial.printf("Ping %s: ", PING_HOST);

    hasInternet = Ping.ping(PING_HOST, PING_TRIES);

    Serial.println(hasInternet ? "Success" : "Fail");
    Serial.println();
}
