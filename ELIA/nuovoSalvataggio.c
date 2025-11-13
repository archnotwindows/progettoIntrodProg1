#include <stdio.h>
#include <stdlib.h>
#include "nuovoSalvataggio.h"

void nuovoSalvataggio(char* nomeFile){

    // variabili default
    int puntiVitaDef = 100; // punti vita di default 
    int moneteDef = 0;      // monete di default 
    int oggettiDef = 0;     // oggeti di default del personaggio
    int missioniCompletateDef = 0;   // missioni completate di default

    //creo un nuovo file
    FILE *salvataggio;

    salvataggio = fopen(nomeFile, "w");     // apro il file in modalità write
    
    if (salvataggio == NULL){
        exit(EXIT_FAILURE);
    } 

    //salvo cose di default dentro
    // data e ora del salvataggio, punti vita del personaggio, monete del personaggio, numero di oggetti, e missioni completate
    fprintf(salvataggio, "Data & ora: %s\n", nomeFile);
    fprintf(salvataggio, "punti_vita: %d\n", puntiVitaDef);
    fprintf(salvataggio, "monete: %d\n", moneteDef);
    fprintf(salvataggio, "oggetti: %d\n", oggettiDef);
    fprintf(salvataggio, "missioni_completate: %d\n", missioniCompletateDef);

    fclose(salvataggio);
}