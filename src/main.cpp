#include <Arduino.h>
#include "Services/NetworkManager.h"
#include "Player/AudioPlayer.h"
#include "Server/RadioServer.h"


RadioServer* webServer;
AudioPlayer* player;

void setup()
{
    system_update_cpu_freq(SYS_CPU_160MHZ);
    Serial.begin(115200);

    NetworkManager::instance()
        ->connect("RadioBox", "secret");

    PlayList* playlist = new PlayList(&SPIFFS, "/playlist");
    player = new AudioPlayer(playlist);
    webServer = new RadioServer(player);

    webServer->start();
    player->play();
}

void loop()
{
    webServer->handler();
    player->handle();
}