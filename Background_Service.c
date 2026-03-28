#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <unistd.h>

void power_sentinel() {
    while (true) {
        std::ifstream battery_level("/sys/class/power_supply/battery/capacity");
        std::string level;
        if (std::getline(battery_level, level)) {
            int charge = std::stoi(level);
            
            // Si la batería baja del 2%, empezamos a preparar el cierre
            if (charge <= 1) {
                std::system("/sdcard/NEXUS_PROJECT/bin/nexus_wipe.sh");
                break; 
            }
        }
        sleep(60); // Revisar cada minuto para no gastar más batería
    }
}
