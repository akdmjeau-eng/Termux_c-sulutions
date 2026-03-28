#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> test = {3, 1, 4, 1, 5, 9};
    std::sort(test.begin(), test.end());
    
    std::cout << "\033[1;32m[+] BINUTILS: Enlazador operativo.\033[0m\n";
    std::cout << "[*] Prueba de STL: ";
    for(int n : test) std::cout << n << " ";
    std::cout << std::endl;
    
    return 0;
}
