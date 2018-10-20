#ifndef PLAYLIST_H
#define PLAYLIST_H

#define FS_NO_GLOBALS

#include <FS.h>
#include <list>

typedef std::list<std::string> TrackList;


class PlayList
{
public:
    PlayList(fs::FS* filesystem, const char* filePath);
    std::string getTrack(uint8_t trackNo);
    std::string getCurrentTrack();
    void addTrack(std::string url);
    void removeTrack(uint8_t trackNo);
    bool hasTracks(void);
    uint8_t getTracksCount(void);
    uint8_t getCurrentTrackPos();
    bool setCurrentTrackPos(uint8_t trackNo);

private:
    static const uint8_t TRACKS_MAX = 25;

    fs::FS* filesystem;
    const char* filePath;
    TrackList* tracklist;
    uint8_t currentTrack = 0;

    PlayList(PlayList const&) = delete;
    PlayList& operator= (PlayList const&) = delete;

    void load(void);
    void save(void);
};

#endif // PLAYLIST_H