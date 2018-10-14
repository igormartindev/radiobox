#include "AudioPlayer.h"


AudioPlayer* AudioPlayer::instance(void)
{
    static AudioPlayer player;
    return &player;
}

AudioPlayer* AudioPlayer::init(PlayList* playlist)
{
    this->playlist = playlist;

    source = new AudioFileSourceICYStream();
    buffer = new AudioFileSourceBuffer(source, 2000);
    output = new AudioOutputI2SNoDAC();
    mp3Player = new AudioGeneratorMP3();

    Serial.println("Player is initialised.");

    return this;
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

void AudioPlayer::play()
{
    stop();

    if (!playlist->hasTracks()) {
        Serial.println("Playlist is empty");
        return;
    }

    source->open(playlist->getCurrentTrack().c_str());

    Serial.println("Start playing...");
    mp3Player->begin(buffer, output);
}

void AudioPlayer::stop()
{
    if (mp3Player->isRunning()) {
        mp3Player->stop();
    }
}