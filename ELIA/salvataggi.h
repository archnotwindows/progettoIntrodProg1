#ifndef SALVATAGGIO_H
#define SALVATAGGIO_H
#include <stdbool.h>    

void checkDirSalvataggi();
void nuovoSalvataggio(char* nomeFile, char* data);
int listaSalvataggi();
bool triggherTrucchi(char tasto);
void eliminaSalvataggio(int numeroDaEliminare);
void modificaSalvataggio(int numeroDaModificare);
    
#endif 