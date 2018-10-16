#include <Arduino.h>
#include "Services/NetworkManager.h"
#include "Player/AudioPlayer.h"
#include "Server/RadioServer.h"


RadioServer* webServer;

void setup()
{
    system_update_cpu_freq(SYS_CPU_160MHZ);
    Serial.begin(115200);

    NetworkManager::instance()
        ->connect("RadioBox", "secret");

    PlayList* playlist = new PlayList(&SPIFFS, "/playlist");

    AudioPlayer::instance()
        ->init(playlist)
        ->play();

    webServer = new RadioServer();
    webServer->start();
}

void loop()
{
    AudioPlayer::instance()
        ->handle();

    webServer->handler();
}