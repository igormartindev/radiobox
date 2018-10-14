#include "AudioPlayer.h"


AudioPlayer* AudioPlayer::instance(void)
{
    static AudioPlayer player;
    return &player;
}

void AudioPlayer::init(void)
{
    source = new AudioFileSourceICYStream();
    buffer = new AudioFileSourceBuffer(source, 2000);
    output = new AudioOutputI2SNoDAC();
    mp3Player = new AudioGeneratorMP3();

    Serial.println("Player is initialised.");
}

void AudioPlayer::handle(void)
{
    if (mp3Player->isRunning()) {
        if (!mp3Player->loop()) {
            Serial.println("Stopped...");
            mp3Player->stop();
        }
    }
}

void AudioPlayer::play(const char* uri)
{
    stop();
    source->open(uri);

    Serial.println("Start playing...");
    mp3Player->begin(buffer, output);
}

void AudioPlayer::stop()
{
    if (mp3Player->isRunning()) {
        mp3Player->stop();
    }
}