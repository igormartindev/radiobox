#include "RadioServer.h"


void RadioServer::start(int port)
{
    server = new ESP8266WebServer(port);

    this->router();
    server->begin();

    Serial.println("Radio Server started.");
}

void RadioServer::router(void)
{
    controller = new HomeController(server);

    server->on("/", HTTP_GET, std::bind(&HomeController::index, controller));
    server->on("/add", HTTP_GET, std::bind(&HomeController::addStation, controller));
    server->on("/del", HTTP_GET, std::bind(&HomeController::delStation, controller));
}

void RadioServer::handler(void)
{
    server->handleClient();
}