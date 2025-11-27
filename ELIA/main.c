#include <stdio.h>
#include <stdlib.h>
#include "nuovoGioco.h"
#include "pulisciSchermo.h"
#include <stdbool.h>

/*
+ - - - - - - - - - - - - - - - - - - - - - - - - - +
|                  [nome gioco]                     |
| nuova partita                                     |
| carica salvataggio                                |
+ - - - - - - - - - - - - - - - - - - - - - - - - - +
scegli un'opzione:

*/

int main(void) {
    pulisciSchermo();
    nuovoGioco();
    return 0;
}