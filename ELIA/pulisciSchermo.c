#include <stdlib.h>
#include "pulisciSchermo.h"

void pulisciSchermo(){
    #ifdef _WIN32
        system("cls");          // pulisce temrinale windows
    #elif __APPLE__
        system("clear");        // pulisce terminale macOS
    #else
        system("clear");        // pulisce terminale linux
    #endif
    
    return;
}