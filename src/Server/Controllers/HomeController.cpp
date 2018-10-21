#include "HomeController.h"


HomeController::HomeController(ESP8266WebServer* server, AudioPlayer* player)
{
    this->server = server;
    this->player = player;
}

void HomeController::index(void)
{
    const char* body =
    "<!doctype html> "
    "<html>"
        "<head>"
            "<title>RadioBox</title>"
            "<link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css'>"
            "<link rel='stylesheet' href='https://fonts.googleapis.com/icon?family=Material+Icons'>"
            "<style>"
                ".current {font-weight: bold;}"
                "body {margin-bottom: 1em;}"
            "</style>"
            "<script type='text/javascript'>"
                "window.onload = function () {"
                    "var xhr = new XMLHttpRequest();"
                    "xhr.open('GET', '/list', false);"
                    "xhr.send();"
                    "if (xhr.status != 200) {"
                        "return;"
                    "}"
                    "var response = JSON.parse(xhr.responseText);"
                    "var list = response.list;"
                    "var current = response.current;"
                    "var htmlList = '';"
                    "for (var id in list) {"
                        "var track = list[id];"
                        "htmlList += '<tr data-id=\"' + track.id + '\"'"
                            "+ (current == track.id ? 'class=\"current\">' : '>')"
                            "+ '<td>' + (track.id + 1) + '</td>'"
                            "+ '<td>' + track.url + '</td>'"
                            "+ '<td><span class=\"material-icons close play\">'"
                                "+ (current == track.id ? 'pause' : 'play_arrow')"
                            "+ '</span></td>'"
                            "+ '<td><span class=\"close delete\">&times;</span></td>'"
                        "+ '</tr>';"
                    "}"
                    "document.getElementById('list').innerHTML = htmlList;"
                    "document.querySelectorAll('#list .play').forEach(function (element) {"
                        "element.addEventListener('click', play);"
                    "});"
                    "document.querySelectorAll('#list .delete').forEach(function (element) {"
                        "element.addEventListener('click', deleteTrack);"
                    "});"
                "};"
                "function play(event) {"
                    "var row = event.target.parentElement.parentElement;"
                    "var id = row.getAttribute('data-id');"
                    "window.location.replace('/play?id=' + id);"
                "}"
                "function deleteTrack(event) {"
                    "var row = event.target.parentElement.parentElement;"
                    "var id = row.getAttribute('data-id');"
                    "window.location.replace('/del?id=' + id);"
                "}"
            "</script>"
        "</head>"
        "<body>"
            "<div class='container'>"
                "<table class='table table-hover table-striped'>"
                    "<thead>"
                        "<tr class='btn-secondary'>"
                            "<th>#</th>"
                            "<th>Station url</th>"
                            "<th></th>"
                            "<th></th>"
                        "</tr>"
                    "</thead>"
                    "<tbody id='list'>"
                    "</tbody>"
                "</table>"
                "<form class='form-inline row' method='GET' action='/add'>"
                    "<div class='form-group col-sm-6'>"
                        "<input type='url' class='form-control col-sm-12' name='url' required placeholder='http://radio.url/station.mp3'>"
                    "</div>"
                    "<div class='form-group col-sm-3 col-lg-2'>"
                        "<input type='submit' class='btn btn-secondary col-sm-12' value='Add Station'>"
                    "</div>"
                "</form>"
            "</div>"
        "</body>"
    "</html>";

    player->stop();

    server->send(200, "text/html; charset=utf-8", body);
    server->client().stop();
    player->play();
}

void HomeController::list(void)
{
    String json;
    String trackList;
    PlayList *playlist = player->getPlaylist();

    player->stop();

    for (uint8_t i = 0; i < playlist->getTracksCount(); i++) {
        trackList +=
            "{"
                "\"id\":";
        trackList += i;
        trackList += ","
                "\"url\":\"";
        // TODO: Escape string
        trackList += playlist->getTrack(i).c_str();
        trackList += "\""
            "}";

        if (i + 1 < playlist->getTracksCount()) {
            trackList += ",";
        }
    }

    json =
        "{"
            "\"list\": [";
    json += trackList;
    json +=
            "],";
    json +=
            "\"current\": ";
    json += playlist->getCurrentTrackPos();
    json +=
        "}";

    server->send(200, "application/json", json);
    player->play();
}

void HomeController::addStation(void)
{
    String url = server->arg("url");
    PlayList *playlist = player->getPlaylist();

    player->stop();
    playlist->addTrack(url.c_str());

    server->sendHeader("Location", "/", true);
    server->send(302, "text/plain", "");
}

void HomeController::delStation(void)
{
    String stationId = server->arg("id");
    PlayList *playlist = player->getPlaylist();

    player->stop();
    playlist->removeTrack(stationId.toInt());

    server->sendHeader("Location", "/", true);
    server->send(302, "text/plain", "");
}

void HomeController::playStation(void)
{
    String stationId = server->arg("id");

    player->stop();

    server->sendHeader("Location", "/", true);
    server->send(302, "text/plain", "");

    player->play(stationId.toInt());
}