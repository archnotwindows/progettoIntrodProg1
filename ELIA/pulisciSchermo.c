#define _POSIX_C_SOURCE 200809L 
#include <stdlib.h>
#include "pulisciSchermo.h"

void pulisciSchermo(){
    int ignore; // Variabile per ignorare il return

    #ifdef _WIN32
        ignore = system("cls");
    #else
        ignore = system("clear");
    #endif

    (void)ignore; // annulla il warning "unused variable 'ignore'"
}