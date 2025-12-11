#include "systemclear.h"
#include <stdlib.h>

void puliscischermo(){
    #ifdef _WIN32
        system("cls");
    #elif __APPLE__
        system("clear");
    #else
        system("clear");
    #endif
}