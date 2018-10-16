#ifndef HOME_CONTROLLER_H
#define HOME_CONTROLLER_H

#include <ESP8266WebServer.h>
#include "../../Player/AudioPlayer.h"


class HomeController
{
    private:
        ESP8266WebServer *server;

    public:
        HomeController(ESP8266WebServer *server);
        void index(void);
        void addStation(void);
        void delStation(void);
};

#endif // HOME_CONTROLLER_H