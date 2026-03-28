#include <iostream>
#include <cstdlib>

void monitor_iphone_connection() {
    std::cout << "\033[1;36m[*] NEXUS: Vigilando túnel de visualización...\033[0m\n";
    
    // Escaneamos los logs del servidor para ver si hay un GET desde otra IP
    while (true) {
        int check = std::system("netstat -tn | grep :8000 | grep ESTABLISHED > /dev/null");
        if (check == 0) {
            std::cout << "\033[1;32m[+] ¡CONEXIÓN ESTABLECIDA CON IPHONE! Portal Activo.\033[0m\n";
            std::system("cmd vibration flash"); // Alerta táctil
            break;
        }
    }
}
