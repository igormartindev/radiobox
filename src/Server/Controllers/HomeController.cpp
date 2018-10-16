#include "HomeController.h"


HomeController::HomeController(ESP8266WebServer *server)
{
    this->server = server;
}

void HomeController::index(void)
{
    AudioPlayer *player = AudioPlayer::instance();
    PlayList *playlist = player->getPlaylist();

    String body;
    String trackList;

    for (uint8_t i = 0; i < playlist->getTracksCount(); i++) {
        trackList += (i+1 == playlist->getCurrentTrackPos()) ? "<tr class='active' style='font-weight:bold'>" : "<tr>";
        trackList +=
            "<td>";
        trackList += i + 1;
        trackList +=
            "</td>"
            "<td>";
        trackList += playlist->getTrack(i).c_str();
        trackList += " "
                "<form method='GET' action='/del' style='display:inline'>"
                    "<input type='hidden' name='id' value='";
        trackList += i;
        trackList +=
                    "'>"
                    "<button type='submit' class='close'><span>&times;</span></button>"
                "</form>";
        trackList +=
            "</td>"
        "</tr>";
    }

    body +=
    "<!doctype html> "
    "<html>"
        "<head>"
            "<title>RadioBox</title>"
            "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css'>"
            "<link rel='stylesheet' href='https://fonts.googleapis.com/icon?family=Material+Icons'>"
        "</head>"
        "<body>"
            "<div class='container'>"
                "<table class='table table-hover table-striped'>"
                    "<tr>"
                        "<td class='info'>#</td>"
                        "<td class='info'>Station url</td>"
                    "</tr>";
    body += trackList;
    body +=
                "</table>"
                "<form class='form-inline' method='GET' action='/add'>"
                    "<div class='form-group'>"
                        "<input type='url' class='form-control' name='url' required placeholder='http://radio.url/mp3'>"
                    "</div>"
                    "<input type='submit' class='btn btn-primary' style='margin-left: 10px' value='Add Station'>"
                "</form>"
            "</div>"
        "</body>"
    "</html>";

    server->send(200, "text/html", body);
}

void HomeController::addStation(void)
{
    String url = server->arg("url");
    AudioPlayer *player = AudioPlayer::instance();
    PlayList *playlist = player->getPlaylist();

    playlist->addTrack(url.c_str());

    server->sendHeader("Location", "/", true);
    server->send(302, "text/plain", "");
}

void HomeController::delStation(void)
{
    String stationId = server->arg("id");
    AudioPlayer *player = AudioPlayer::instance();
    PlayList *playlist = player->getPlaylist();

    playlist->removeTrack(stationId.toInt());

    server->sendHeader("Location", "/", true);
    server->send(302, "text/plain", "");
}