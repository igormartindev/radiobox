#ifndef HOME_CONTROLLER_H
#define HOME_CONTROLLER_H

#include <ESP8266WebServer.h>
#include "../../Player/AudioPlayer.h"


class HomeController
{
public:
    HomeController(ESP8266WebServer* server, AudioPlayer* player);
    void index(void);
    void addStation(void);
    void delStation(void);
    void playStation(void);

private:
    ESP8266WebServer* server;
    AudioPlayer* player;

    HomeController(HomeController const&);
    HomeController& operator= (HomeController const&);
};

#endif // HOME_CONTROLLER_H