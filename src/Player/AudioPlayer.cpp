#include "AudioPlayer.h"


AudioPlayer::AudioPlayer(PlayList* playlist)
{
    this->playlist = playlist;
    source = new AudioFileSourceICYStream();
    buffer = new AudioFileSourceBuffer(source, BUFFER_SIZE);
    output = new AudioOutputI2SNoDAC();
    mp3Player = new AudioGeneratorMP3();

    Serial.println("Player is initialised.");
}

void AudioPlayer::handle(void)
{
    if (mp3Player->isRunning()) {
        if (!mp3Player->loop()) {
            Serial.println("Player stopped!");
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

void AudioPlayer::play(uint8_t trackNo)
{
    stop();

    if (!playlist->hasTracks()) {
        Serial.println("Playlist is empty");
        return;
    }

    if (!playlist->setCurrentTrackPos(trackNo)) {
        Serial.println("Track No is not exists...");
        return;
    }

    source->open(playlist->getTrack(trackNo).c_str());

    Serial.println("Start playing...");
    mp3Player->begin(buffer, output);
}

void AudioPlayer::stop()
{
    if (mp3Player->isRunning()) {
        mp3Player->stop();
    }
}

PlayList* AudioPlayer::getPlaylist()
{
    return playlist;
}