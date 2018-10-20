#include "RadioServer.h"


RadioServer::RadioServer(AudioPlayer* player, uint8_t port)
{
    this->player = player;
    server = new ESP8266WebServer(port);
    router();
}

void RadioServer::start()
{
    server->begin();
    Serial.println("Radio Server started.");
}

void RadioServer::router(void)
{
    controller = new HomeController(server, player);

    server->on("/", HTTP_GET, std::bind(&HomeController::index, controller));
    server->on("/add", HTTP_GET, std::bind(&HomeController::addStation, controller));
    server->on("/del", HTTP_GET, std::bind(&HomeController::delStation, controller));
    server->on("/play", HTTP_GET, std::bind(&HomeController::playStation, controller));
}

void RadioServer::handler(void)
{
    server->handleClient();
}