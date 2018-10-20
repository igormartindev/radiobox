#ifndef RADIO_SERVER_H
#define RADIO_SERVER_H

#include <ESP8266WebServer.h>
#include "Controllers/HomeController.h"


class RadioServer
{
public:
    RadioServer(AudioPlayer* player, uint8_t port = 80);
    void start();
    void handler(void);

private:
    ESP8266WebServer* server;
    AudioPlayer* player;
    HomeController* controller;
    ESP8266WebServer::THandlerFunction rootHandler;

    void router(void);

    RadioServer(RadioServer const&) = delete;
    RadioServer& operator= (RadioServer const&) = delete;
};

#endif // RADIO_SERVER_H