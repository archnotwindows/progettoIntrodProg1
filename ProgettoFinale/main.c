#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "nuovoGioco.h"
#include "systemclear.h"

int main(void) {
    srand(time(NULL)); 
    puliscischermo();
    
    
    nuovoGioco();
    
    return 0;
}