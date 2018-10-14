#include "main.h"


void setup()
{
    system_update_cpu_freq(SYS_CPU_160MHZ);
    Serial.begin(115200);

    NetworkManager::instance()
        ->connect("RadioBox", "secret");
}

void loop()
{
    // Main loop
}
