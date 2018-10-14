#include "main.h"


void setup()
{
    system_update_cpu_freq(SYS_CPU_160MHZ);
    Serial.begin(115200);

    NetworkManager::instance()
        ->connect("RadioBox", "secret");

    AudioPlayer::instance()
        ->init();

    AudioPlayer::instance()
        ->play("http://radio.test/mp3");
}

void loop()
{
    AudioPlayer::instance()
        ->handle();
}
