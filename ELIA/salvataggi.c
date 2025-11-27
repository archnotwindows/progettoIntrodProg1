#include <stdio.h>
#include <stdlib.h>
#include "salvataggi.h"
#include "nuovoGioco.h"
#include <string.h>
#include <stdbool.h>
#include "pulisciSchermo.h"
#include <sys/types.h>
#include <sys/stat.h>

void checkDirSalvataggi(){
    char *path="salvataggi";
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        #ifdef _WIN32
            // _mkdir prende solo il percorso
            _mkdir(path);
        #else
            mkdir(path, 0700); 
        #endif
        //printf("Cartella 'salvataggi' creata.\n"); 
    }
}



void nuovoSalvataggio(char* nomeFile, char* data){

    checkDirSalvataggi();   

    // variabili default
    int puntiVitaDef = 20; // punti vita di default 
    int moneteDef = 0;      // monete di default 
    int oggettiDef = 0;     // oggeti di default del personaggio
    int missioniCompletateDef = 0;   // missioni completate di default
    

    //creo un nuovo file
    FILE *salvataggio;

    salvataggio = fopen(nomeFile, "w");     // apro il file in modalità write
    
    if (salvataggio == NULL){
        return;
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
    #define LIST_COMMAND "dir \b salvataggi\\"  // il singolo \ in C è un carattere speciale
                                                    // \b serve per mostrare solo i nomi dei file dentro una dir
    #define DIR_SEPARATOR "\\" // Separatore di cartella per Windows

#else       // sistemi unix-like
    #define POPEN popen
    #define PCLOSE pclose
    #define LIST_COMMAND "ls salvataggi/"
    #define DIR_SEPARATOR "/" // Separatore di cartella per Windows

#endif



int listaSalvataggi(){
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
        sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
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
        printf("Non ci sono salvataggi disponibili, crea una nuova partita.\n");
        nuovoGioco();
    }

    PCLOSE(out);

    return elenco-1;
    
}

void eliminaSalvataggio(int numeroDaEliminare){
    FILE *out;
    char riga[256];      
    int contatore = 1;     
    bool trovato = false;

    // ottenere i nomi dei file
    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ){
        printf("Errore nel sistema di file.\n");
        return;
    }

    // Scorro i file finché non trovo quello col numero giusto
    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; // tolgo \n finale
        
        if (contatore == numeroDaEliminare) {
            char percorso_completo[512];
            
            // Costruisco il percorso: salvataggi/nomefile.txt
            // NOTA: Assicurati che "salvataggi" sia coerente con le modifiche fatte prima (senza ../)
            sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
            
            // 3. Provo a cancellare il file
            if (remove(percorso_completo) == 0) {
                printf("\n -> Salvataggio eliminato con successo: %s\n", riga);
            } else {
                perror("\n -> Errore durante l'eliminazione");
            }
            
            trovato = true;
            break; // Esco dal while, lavoro finito
        }
        contatore++;
    }

    if (!trovato) {
        printf("\n -> Errore: Salvataggio numero %d non trovato.\n", numeroDaEliminare);
    }

    PCLOSE(out);
    
    printf("Premi invio per continuare...");
    getchar(); 
    getchar(); 
}

bool triggherTrucchi(char tasto){
    static int contatore = 0; // static salva il valore tra le chiamate
    const char codice[] = "wwssadadba "; 

    // 1. CONTROLLO SE IL TASTO E' GIUSTO
    if ( tasto == codice[contatore] ){
        contatore++; 
        //printf("(DEBUG: Tasto OK, contatore: %d)\n", contatore);

        // CONTROLLO VITTORIA (Solo se il tasto era giusto)
        if ( contatore == strlen(codice) ){
            contatore = 0;
            return true;  
        }
    }

    // GESTIONE ERRORE (Se il tasto era sbagliato)
    else {
        // Se ho sbagliato, ma ho premuto 'w' (l'inizio della sequenza),
        // ricomincio da 1 invece che da 0.
        if ( tasto == 'w' ){
            contatore = 1;
        }
        else{
            contatore = 0;
        }
    }
    
    return false;
}

void modificaSalvataggio(int numeroDaModificare){
    FILE *out;
    char riga[256];      
    int contatore = 1;     
    bool trovato = false;

    // ottenere i nomi dei file
    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ){
        printf("Errore nel sistema di file.\n");
        return;
    }

    // Scorro i file finché non trovo quello col numero giusto
    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; // tolgo \n finale
        
        if (contatore == numeroDaModificare) {
            char percorso_completo[512];
            
            // Costruisco il percorso: salvataggi/nomefile.txt
            // NOTA: Assicurati che "salvataggi" sia coerente con le modifiche fatte prima (senza ../)
            sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
            
            // 3. Provo a cancellare il file
            printf("%s", percorso_completo);
            if (system("nano %s", percorso_completo) == 0) {
                printf("\n -> Salvataggio eliminato con successo: %s\n", riga);
            } else {
                perror("\n -> Errore durante l'eliminazione");
            }
            
            trovato = true;
            break; // Esco dal while, lavoro finito
        }
        contatore++;
    }

    if (!trovato) {
        printf("\n -> Errore: Salvataggio numero %d non trovato.\n", numeroDaEliminare);
    }

    PCLOSE(out);
    
    printf("Premi invio per continuare...");
    getchar(); 
    getchar(); 
}
