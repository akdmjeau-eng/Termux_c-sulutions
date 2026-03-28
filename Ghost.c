#include <iostream>
#include <cstdlib>

void stealth_transition(bool in_pocket) {
    if (in_pocket) {
        std::cout << "\033[1;30m[!] Transición a MODO FANTASMA... [SIGILO ACTIVO]\033[0m\n";
        std::system("/sdcard/NEXUS_PROJECT/bin/nexus_ghost.sh");
        
        // El servidor MkDocs sigue en 0.0.0.0:8000 para tu iPhone 17
        std::cout << "[*] Espejo en iPhone: OPERATIVO.\n";
    } else {
        std::cout << "[*] Saliendo de Modo Fantasma. Restaurando Interfaz.\n";
        std::system("su -c 'settings put system screen_brightness 150'");
    }
}
