#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "salvataggi.h"
#include "pulisciSchermo.h"

// gestione popen o _poper per caso windows o linux/macos
#ifdef _WIN32       // windows
    #include <direct.h>
    #define POPEN _popen   
    #define PCLOSE _pclose
    #define LIST_COMMAND "dir /b salvataggi\\"
    #define DIR_SEPARATOR "\\" 
    #define MKDIR(p) _mkdir(p)

#else       // sistemi unix-like
    #include <unistd.h>
    #define POPEN popen
    #define PCLOSE pclose
    #define LIST_COMMAND "ls salvataggi/"
    #define DIR_SEPARATOR "/" 
    #define MKDIR(p) mkdir(p, 0700)
#endif

// Funzione helper locale per leggere input pulito (evita conflitti con nuovoGioco.c)
static int leggiIntLocale() {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; 
        return atoi(buffer);
    }
    return -1;
}

void checkDirSalvataggi(){
    char *path="salvataggi";
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        MKDIR(path);
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
        printf("Errore creazione file: %s\n", nomeFile);
        return;
    } 

    // Salvo seguendo il formato: Data, pv: X, monete: Y, oggetti: Z, missioni: W
    fprintf(salvataggio, "%s, ", data);
    fprintf(salvataggio, "punti_vita: %d, ", puntiVitaDef);
    fprintf(salvataggio, "monete: %d, ", moneteDef);
    fprintf(salvataggio, "oggetti: %d, ", oggettiDef);
    fprintf(salvataggio, "missioni_completate: %d\n", missioniCompletateDef);

    fclose(salvataggio);
    printf("Salvataggio completato: %s\n", nomeFile);
}

int listaSalvataggi(){
    // listo una dir con ls/dir
    FILE *out;
    char riga[256];      // char per una riga
    int elenco = 1;     // serve per l'elenco da stampare successivamente

    pulisciSchermo();
    printf("\n--------- Salvataggi disponibili ---------\n");
    
    checkDirSalvataggi();

    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ){
        printf("Errore comando lista directory.\n");
        return 0;
    }

    // leggo output riga per riga
    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0;      // sostituisco \n con \0
        
        if (strlen(riga) < 3) continue; // ignora . e .. o file vuoti

        char percorso_completo[512];
        sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
        FILE *file_salvataggio = fopen(percorso_completo, "r");
        if (file_salvataggio == NULL) {
            continue;
        }

        char bufferLettura[256];
        if (fgets(bufferLettura, sizeof(bufferLettura), file_salvataggio)) {
            // Puliamo la riga dal '\n' finale
            bufferLettura[strcspn(bufferLettura, "\n")] = 0;
            
            printf("  %d) %s\n", elenco, bufferLettura);
            
            fclose(file_salvataggio); 
            elenco++;
        }
    }
    PCLOSE(out);

    if ( elenco == 1 ){     // il while non ha iterato => non ci sono salvataggi
        printf("   (Nessun salvataggio trovato)\n");
        return 0;
    }

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
        if (strlen(riga) < 3) continue;

        if (contatore == numeroDaEliminare) {
            char percorso_completo[512];
            
            sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
            
            if (remove(percorso_completo) == 0) {
                printf("\n -> Salvataggio eliminato con successo.\n");
            } else {
                printf("\n -> Errore durante l'eliminazione.\n");
            }
            
            trovato = true;
            break; 
        }
        contatore++;
    }

    if (!trovato) {
        printf("\n -> Errore: Salvataggio numero %d non trovato.\n", numeroDaEliminare);
    }

    PCLOSE(out);
    
    printf("Premi invio per continuare...");
    getchar(); 
}

bool triggherTrucchi(char tasto){
    static int contatore = 0; // static salva il valore tra le chiamate
    const char codice[] = "wwssadadba "; 

    // 1. CONTROLLO SE IL TASTO E' GIUSTO
    if ( tasto == codice[contatore] ){
        contatore++; 

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

    // trovo il file 
    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ){
        printf("Errore sistema file.\n");
        return;
    }

    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; 
        if (strlen(riga) < 3) continue;

        if (contatore == numeroDaModificare) {
            // Ho trovato il file
            char percorso_completo[512];
            sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
            
            // Leggo i dati attuali
            FILE *file_lettura = fopen(percorso_completo, "r");
            if (file_lettura == NULL) {
                printf("Errore apertura file %s\n", riga);
                break;
            }

            char bufferLinea[512];
            char dataStr[100];
            int hp, monete, oggetti, missioni;

            if (fgets(bufferLinea, sizeof(bufferLinea), file_lettura) != NULL) {
                // Parsing della stringa: "DATA, punti_vita: %d, monete: %d, oggetti: %d, missioni_completate: %d"
                // %[^,] legge tutto fino alla prima virgola (la data)
                sscanf(bufferLinea, "%[^,], punti_vita: %d, monete: %d, oggetti: %d, missioni_completate: %d", 
                       dataStr, &hp, &monete, &oggetti, &missioni);
            }
            fclose(file_lettura);

            // 3. Menu Modifica (Trucchi)
            pulisciSchermo();
            printf("--- MODIFICA PARAMETRI (Cheat Mode) ---\n");
            printf("File: %s\n", riga);
            printf("Attuali -> HP: %d | Monete: %d | Missioni: %d\n\n", hp, monete, missioni);
            
            printf("1) Modifica Punti Vita\n");
            printf("2) Modifica Monete\n");
            printf("3) Sblocca Castello Finale (Missioni = 3)\n");
            printf("4) Annulla\n");
            printf("Scegli: ");
            
            int scelta = leggiIntLocale();
            bool modificato = false;

            if (scelta == 1) {
                printf("inserisci nuovi punti vita: ");
                hp = leggiIntLocale();
                modificato = true;
            } else if (scelta == 2) {
                printf("inserisci nuove monete: ");
                monete = leggiIntLocale();
                modificato = true;
            } else if (scelta == 3) {
                printf("missioni impostate a 3. Il Castello Finale è ora accessibile!\n");
                missioni = 3; // 3 missioni completate sbloccano il finale
                modificato = true;
            }

            // 4. Se ho modificato qualcosa, sovrascrivo il file
            if (modificato) {
                FILE *file_scrittura = fopen(percorso_completo, "w");
                if (file_scrittura != NULL) {
                    fprintf(file_scrittura, "%s, ", dataStr);
                    fprintf(file_scrittura, "punti_vita: %d, ", hp);
                    fprintf(file_scrittura, "monete: %d, ", monete);
                    fprintf(file_scrittura, "oggetti: %d, ", oggetti);
                    fprintf(file_scrittura, "missioni_completate: %d\n", missioni);
                    fclose(file_scrittura);
                    printf("Salvataggio modificato con successo!\n");
                } else {
                    printf("Errore nella scrittura del file.\n");
                }
            } else {
                printf("Nessuna modifica effettuata.\n");
            }

            trovato = true;
            break; 
        }
        contatore++;
    }
    PCLOSE(out);

    if (!trovato) {
        printf("Salvataggio non trovato.\n");
    }
}