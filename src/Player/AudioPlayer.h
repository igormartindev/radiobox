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
    static AudioPlayer* instance();

    AudioPlayer* init(PlayList* playlist);
    void play(const char* uri);
    void play();
    void stop();
    void handle();

private:
    AudioGeneratorMP3* mp3Player;
    AudioFileSourceICYStream* source;
    AudioFileSourceBuffer* buffer;
    AudioOutputI2SNoDAC* output;
    PlayList *playlist;

    AudioPlayer() {};
};

#endif // AUDIO_PLAYER_H