#include <iostream>
#include <cstdlib>

void force_nexus_publish() {
    std::cout << "\033[1;33m[*] NEXUS: Sincronizando datos con el Portal Web...\033[0m\n";
    
    // Comando para construir el sitio ignorando advertencias de Python
    std::system("mkdocs build -d /sdcard/NEXUS_PROJECT/site");
    
    std::cout << "\033[1;32m[+] PORTAL ACTUALIZADO: Revisa http://127.0.0.1:8000\033[0m\n";
}
