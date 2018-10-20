#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H

#include <SD.h>
#include <AudioFileSourceICYStream.h>
#include <AudioFileSourceBuffer.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2SNoDAC.h>

#include "PlayList.h"


class AudioPlayer
{
public:
    explicit AudioPlayer(PlayList* playlist);
    void play(const char* uri);
    void play();
    void play(uint8_t trackNo);
    void stop();
    void handle();
    PlayList* getPlaylist();

private:
    static const uint16_t BUFFER_SIZE = 2000;

    AudioGeneratorMP3* mp3Player;
    AudioFileSourceICYStream* source;
    AudioFileSourceBuffer* buffer;
    AudioOutputI2SNoDAC* output;
    PlayList* playlist;

    AudioPlayer(AudioPlayer const&) = delete;
    AudioPlayer& operator= (AudioPlayer const&) = delete;
};

#endif // AUDIO_PLAYER_H