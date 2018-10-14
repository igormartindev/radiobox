#ifndef AUDIO_PLAYER_H
#define AUDIO_PLAYER_H


#include <SD.h>
#include <AudioFileSourceICYStream.h>
#include <AudioFileSourceBuffer.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2SNoDAC.h>


class AudioPlayer
{
public:
    static AudioPlayer* instance();

    void init();
    void play(const char* uri);
    void stop();
    void handle();

private:
    AudioGeneratorMP3* mp3Player;
    AudioFileSourceICYStream* source;
    AudioFileSourceBuffer* buffer;
    AudioOutputI2SNoDAC* output;

    AudioPlayer() {};
};

#endif // AUDIO_PLAYER_H