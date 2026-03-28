#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

void proximity_security_daemon() {
    std::cout << "\033[1;31m[!] MONITOR DE PROXIMIDAD ARMADO.\033[0m\n";
    
    // Ruta estándar del sensor en la mayoría de dispositivos Motorola
    std::string sensor_path = "/sys/class/sensors/proximity_sensor/status"; 
    
    while (true) {
        std::ifstream sensor_file(sensor_path);
        std::string status;
        
        if (std::getline(sensor_file, status)) {
            // '0' suele significar objeto lejano (snatch detectado)
            if (status == "0") { 
                std::cout << "\033[1;41m[!!!] ALERTA DE ARREBATO: EJECUTANDO WIPE...\033[0m\n";
                std::system("/sdcard/NEXUS_PROJECT/bin/nexus_wipe.sh");
                break;
            }
        }
        usleep(500000); // Monitoreo cada 0.5 segundos
    }
}
