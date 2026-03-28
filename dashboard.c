#include <iostream>
#include <cstdlib>

void secure_extraction_sequence() {
    std::cout << "\033[1;35m[*] NEXUS: Iniciando Secuencia de Extracción Segura...\033[0m\n";
    
    // Ejecutar el empaquetado 7z
    std::system("/sdcard/NEXUS_PROJECT/bin/nexus_package.sh");
    
    std::cout << "\033[1;32m[+] Evidencia cifrada y lista para transporte.\033[0m\n";
    std::cout << "[?] ¿Deseas ejecutar LIMPIEZA FORENSE ahora? (s/n): ";
    
    char opt;
    std::cin >> opt;
    if (opt == 's' || opt == 'S') {
        std::system("/sdcard/NEXUS_PROJECT/bin/nexus_wipe.sh");
    }
}
