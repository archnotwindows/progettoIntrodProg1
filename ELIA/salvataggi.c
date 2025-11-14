#include <stdio.h>
#include <stdlib.h>
#include "salvataggi.h"
#include "nuovoGioco.h"
#include <string.h>
#include <stdbool.h>
#include "pulisciSchermo.h"


void nuovoSalvataggio(char* nomeFile, char* data){
    // variabili default
    int puntiVitaDef = 20; // punti vita di default 
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
    fprintf(salvataggio, "%s, ", data);
    fprintf(salvataggio, "punti_vita: %d, ", puntiVitaDef);
    fprintf(salvataggio, "monete: %d, ", moneteDef);
    fprintf(salvataggio, "oggetti: %d, ", oggettiDef);
    fprintf(salvataggio, "missioni_completate: %d\n", missioniCompletateDef);

    fclose(salvataggio);
}



// gestione popen o _poper per caso windows o linux/macos
#ifdef _WIN32       // windows
    #define POPEN _popen   
    #define PCLOSE _pclose
    #define LIST_COMMAND "dir \b ..\\salvataggi\\"  // il singolo \ in C è un carattere speciale
                                                    // \b serve per mostrare solo i nomi dei file dentro una dir
    #define DIR_SEPARATOR "\\" // Separatore di cartella per Windows

#else       // sistemi unix-like
    #define POPEN popen
    #define PCLOSE pclose
    #define LIST_COMMAND "ls ../salvataggi/"
    #define DIR_SEPARATOR "/" // Separatore di cartella per Windows

#endif



void listaSalvataggi(){
    // listo una dir con ls/dir
    FILE *out;
    char riga[256];      // char per una riga
    int elenco = 1;     // serve per l'elenco da stampare successivamente

    pulisciSchermo();
    printf("\n--------- Salvataggi disponibili ---------\n");
    
    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ){
        exit(EXIT_FAILURE);
    }

    // leggo output riga per riga
    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0;      // sostituisco \n con \0
                
        char percorso_completo[512];
        sprintf(percorso_completo, "../salvataggi%s%s", DIR_SEPARATOR, riga);
        FILE *file_salvataggio = fopen(percorso_completo, "r");
        if (file_salvataggio == NULL) {
            printf("  %d) Errore - Impossibile leggere il file: %s\n", elenco, riga);
            elenco++;
            continue;
        }

        char bufferLettura[256];
        if (fgets(bufferLettura, sizeof(bufferLettura), file_salvataggio)) {
            // Abbiamo letto la prima riga
                
            // Puliamo la riga dal '\n' finale
            bufferLettura[strcspn(bufferLettura, "\n")] = 0;
                
            // 5. Stampa formattata
            printf("  %d. %s\n", elenco, bufferLettura);

            if (fgets(bufferLettura, sizeof(bufferLettura), file_salvataggio)) {
                bufferLettura[strcspn(bufferLettura, "\n")] = 0;
                printf("  %d. %s\n", elenco, bufferLettura);

            } 

            fclose(file_salvataggio); // Chiudiamo il file di salvataggio
            
            elenco++;
        }
    }

    if ( elenco == 1 ){     // il while non ha iterato => non ci sono salvataggi
        printf("Non ci sono salvataggi disponibili, crea una nuova partita.");
        nuovoGioco();
    }

    PCLOSE(out);

    return;
    
}
