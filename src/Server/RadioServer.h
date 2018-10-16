#ifndef RADIO_SERVER_H
#define RADIO_SERVER_H

#include <ESP8266WebServer.h>
#include "Controllers/HomeController.h"


class RadioServer
{
    private:
        ESP8266WebServer *server;
        HomeController *controller;
        ESP8266WebServer::THandlerFunction rootHandler;

    public:
        void start(int port = 80);
        void router(void);
        void handler(void);
};

#endif // RADIO_SERVER_H