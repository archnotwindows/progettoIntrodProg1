
#include <stdio.h>

#include <stdlib.h>

void puliscischermo(){
    #ifdef _WIN32
        system("cls");          // pulisce temrinale windows
    #elif __APPLE__
        system("clear");        // pulisce terminale macOS
    #else
        system("clear");        // pulisce terminale linux
    #endif
    
    return;
}