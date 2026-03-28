#include <iostream>
#include <cstdlib>
#include <string>

void auto_attack_logic(std::string bssid, int signal, int channel) {
    // Umbral de ataque: -50dBm (Muy cerca)
    if (signal > -50) {
        std::cout << "\033[1;31m[!] OBJETIVO EN RANGO ÓPTIMO (" << signal << "dBm). LANZANDO ATAQUE...\033[0m\n";
        
        // Llamar al script de ataque pasando BSSID y Canal
        std::string cmd = "/sdcard/NEXUS_PROJECT/bin/nexus_attack.sh " + bssid + " " + std::to_string(channel);
        std::system(cmd.c_str());
        
        // Alerta táctica en el Moto G05
        std::system("cmd vibration flash");
    } else {
        std::cout << "[*] Señal insuficiente (" << signal << "dBm). Manteniendo sigilo.\n";
    }
}
