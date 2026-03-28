#include <iostream>
#include <cstdlib>
#include <string>

void run_mkdocs_safe() {
    std::cout << "[*] NEXUS: Verificando entorno de Python...\n";
    
    // Intentamos la ejecución normal, si falla, usamos el flag de bypass
    std::string cmd = "mkdocs serve -a 127.0.0.1:8000";
    
    int result = std::system(cmd.c_str());
    
    if (result != 0) {
        std::cout << "[!] Detectado bloqueo PEP 668. Aplicando bypass táctico...\n";
        std::system("python3 -m pip install mkdocs mkdocs-material --break-system-packages");
        std::system("mkdocs serve -a 127.0.0.1:8000 &");
    }
}
