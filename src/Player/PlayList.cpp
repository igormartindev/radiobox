#include "PlayList.h"


PlayList::PlayList(fs::FS* filesystem, const char* filePath)
{
    this->filesystem = filesystem;
    this->filePath = filePath;

    tracklist = new TrackList();

    if (!this->filesystem->begin()) {
        Serial.printf("Fail to init fileststem");
        return;
    }

    // TODO: Format fs if necessary

    load();
}

std::string PlayList::getTrack(uint8_t trackNo)
{
    if (trackNo >= tracklist->size()) {
        // TODO: Error
    }

    TrackList::iterator it = std::next(tracklist->begin(), trackNo);
    return *it;
}

std::string PlayList::getCurrentTrack()
{
    return getTrack(currentTrack);
}

void PlayList::addTrack(std::string url)
{
    if (!url.length()) {
        return;
    }

    if (tracklist->size() >= TRACKS_MAX) {
        return;
    }

    tracklist->push_back(url);
    save();
}

void PlayList::removeTrack(uint8_t trackNo)
{
    if (!tracklist->size()) {
        return;
    }

    TrackList::iterator it = std::next(tracklist->begin(), trackNo);
    tracklist->erase(it);
    save();
}

uint8_t PlayList::getTracksCount(void)
{
    return tracklist->size();
}

bool PlayList::hasTracks(void)
{
    return (bool)tracklist->size();
}

void PlayList::save(void)
{
    String line;

    fs::File playlistFile = filesystem->open(filePath, "w");
    if (!playlistFile) {
        Serial.println("Fail to open the playlist file");
    }

    for (auto it = tracklist->begin(); it != tracklist->end(); it++) {
        playlistFile.print((*it).c_str());
        playlistFile.print('\n');
    }

    playlistFile.close();
}

void PlayList::load(void)
{
    if (!filesystem->exists(filePath)) {
        Serial.println("Playlist file does not exists");
        return;
    }

    fs::File playlistFile = filesystem->open(filePath, "r");

    if (!playlistFile) {
        Serial.println("Fail to open playlist file");
        return;
    }

    tracklist->clear();
    while (playlistFile.available()) {
        if (tracklist->size() >= TRACKS_MAX) {
            break;
        }

        auto line = playlistFile.readStringUntil('\n');
        tracklist->push_back(std::string(line.c_str()));
    }

    playlistFile.close();
}