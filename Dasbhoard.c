#include <iostream>
#include <cstdlib>

void sync_pwned_targets() {
    std::cout << "\033[1;33m[*] NEXUS: Sincronizando Bóveda Clandestina...\033[0m\n";
    
    // Comando táctico para extraer MACs y mandarlas al reporte
    const char* sync_cmd = "su -c \"grep -oE '([0-9a-fA-F]{2}:){5}[0-9a-fA-F]{2}' "
                           "/sdcard/.sys_com_google_v3_update/pwned.txt > "
                           "/sdcard/NEXUS_PROJECT/docs/current_targets.txt\"";
    
    if (std::system(sync_cmd) == 0) {
        std::cout << "\033[1;32m[+] Objetivos indexados correctamente.\033[0m\n";
    } else {
        std::cout << "\033[1;31m[!] Error de acceso a la Bóveda.\033[0m\n";
    }
}
