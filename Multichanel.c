#include <iostream>
#include <cstdlib>
#include <unistd.h>

void start_multichannel_sweep() {
    std::cout << "\033[1;35m[*] NEXUS: Iniciando Barredora Táctica (Canales 1-13)...\033[0m\n";
    
    int channels[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    
    for (int ch : channels) {
        std::cout << "[>] Saltando al Canal " << ch << "..." << std::flush;
        
        // 1. Cambiar de canal mediante comando de sistema (requiere root)
        std::string cmd_ch = "su -c 'iw dev wlan0 set channel " + std::to_string(ch) + "'";
        std::system(cmd_ch.c_str());
        
        // 2. Escaneo rápido de 3 segundos en ese canal
        std::string scan_cmd = "su -c 'iw dev wlan0 scan | grep -E \"SSID|signal|WPS\" > /tmp/scan_results.txt'";
        std::system(scan_cmd.c_str());
        
        // 3. Alimentar el reporte de MkDocs con lo encontrado
        std::system("/sdcard/NEXUS_PROJECT/bin/nexus_feeder.sh /tmp/scan_results.txt");
        
        std::cout << " [OK]\r";
        sleep(2);
    }
    std::cout << "\n\033[1;32m[+] Barrido completo. Reporte actualizado.\033[0m\n";
}
