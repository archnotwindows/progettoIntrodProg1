#include <stdlib.h>
#include "systemclear.h"

void puliscischermo() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}