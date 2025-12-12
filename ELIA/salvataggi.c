/* IMPORTANTE: Questa define deve essere la PRIMA riga assoluta. */
#define _POSIX_C_SOURCE 200809L 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "salvataggi.h"
#include "pulisciSchermo.h"

// Configurazione multipiattaforma
#ifdef _WIN32       
    #include <direct.h>
    #define POPEN _popen   
    #define PCLOSE _pclose
    #define LIST_COMMAND "dir /b salvataggi\\"
    #define DIR_SEPARATOR "\\" 
    #define MKDIR(p) _mkdir(p)
#else       
    #include <unistd.h>
    #define POPEN popen
    #define PCLOSE pclose
    #define LIST_COMMAND "ls -1 salvataggi/" 
    #define DIR_SEPARATOR "/" 
    #define MKDIR(p) mkdir(p, 0700)
#endif

// Funzione helper locale per leggere input pulito
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

    int puntiVitaDef = 20; 
    int moneteDef = 0;      
    int oggettiDef = 0;     
    int missioniCompletateDef = 0;   
    
    FILE *salvataggio;
    salvataggio = fopen(nomeFile, "w");    
    
    if (salvataggio == NULL){
        printf("Errore creazione file: %s\n", nomeFile);
        return;
    } 

    fprintf(salvataggio, "%s, ", data);
    fprintf(salvataggio, "punti_vita: %d, ", puntiVitaDef);
    fprintf(salvataggio, "monete: %d, ", moneteDef);
    fprintf(salvataggio, "oggetti: %d, ", oggettiDef);
    fprintf(salvataggio, "missioni_completate: %d\n", missioniCompletateDef);

    fclose(salvataggio);
}

int listaSalvataggi(){
    FILE *out;
    char riga[256];      
    int elenco = 1;     

    pulisciSchermo();
    printf("\n--------- Salvataggi disponibili ---------\n");
    
    checkDirSalvataggi();

    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ){
        printf("Errore comando lista directory.\n");
        return 0;
    }

    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; 
        if (strlen(riga) < 3) continue; 

        char percorso_completo[512];
        memset(percorso_completo, 0, sizeof(percorso_completo));
        sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
        
        FILE *file_salvataggio = fopen(percorso_completo, "r");
        if (file_salvataggio == NULL) continue;

        char bufferLettura[256];
        if (fgets(bufferLettura, sizeof(bufferLettura), file_salvataggio)) {
            bufferLettura[strcspn(bufferLettura, "\n")] = 0;
            printf("  %d) %s\n", elenco, bufferLettura);
            elenco++;
        }
        fclose(file_salvataggio); 
    }
    PCLOSE(out);

    if ( elenco == 1 ){     
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

    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ){
        printf("Errore nel sistema di file.\n");
        return;
    }

    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; 
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
    PCLOSE(out);

    if (!trovato) printf("\n -> Errore: Salvataggio non trovato.\n");

    printf("Premi invio per continuare...");
    getchar(); 
}

bool triggherTrucchi(char tasto){
    static int contatore = 0; 
    const char codice[] = "wwssadadba"; 

    if ( tasto == codice[contatore] ){
        contatore++; 
        if ( contatore == strlen(codice) ){
            contatore = 0;
            return true;  
        }
    }
    else {
        if ( tasto == 'w' ) contatore = 1;
        else contatore = 0;
    }
    return false;
}

int caricaDatiSalvataggio(int numeroSalvataggio, int* hp, int* monete, int* oggetti, int* missioni){
    FILE *out;
    char riga[256];      
    int contatore = 1;     
    
    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ) return 0;

    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; 
        if (strlen(riga) < 3) continue;

        if (contatore == numeroSalvataggio) {
            char percorso_completo[512];
            sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
            
            FILE *file_lettura = fopen(percorso_completo, "r");
            if (file_lettura == NULL) break;

            char bufferLinea[512];
            char dataStr[100]; // Dummy per la data

            if (fgets(bufferLinea, sizeof(bufferLinea), file_lettura) != NULL) {
                sscanf(bufferLinea, "%[^,], punti_vita: %d, monete: %d, oggetti: %d, missioni_completate: %d", 
                       dataStr, hp, monete, oggetti, missioni);
            }
            fclose(file_lettura);
            PCLOSE(out);
            return 1; // Successo
        }
        contatore++;
    }
    PCLOSE(out);
    return 0; // Fallimento
}

void modificaSalvataggio(int numeroDaModificare){
    FILE *out;
    char riga[256];      
    int contatore = 1;     
    bool trovato = false;

    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ) return;

    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; 
        if (strlen(riga) < 3) continue;

        if (contatore == numeroDaModificare) {
            char percorso_completo[512];
            sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
            
            FILE *file_lettura = fopen(percorso_completo, "r");
            if (file_lettura == NULL) break;

            char bufferLinea[512];
            char dataStr[100];
            int hp, monete, oggetti, missioni;

            if (fgets(bufferLinea, sizeof(bufferLinea), file_lettura) != NULL) {
                sscanf(bufferLinea, "%[^,], punti_vita: %d, monete: %d, oggetti: %d, missioni_completate: %d", 
                       dataStr, &hp, &monete, &oggetti, &missioni);
            }
            fclose(file_lettura);

            pulisciSchermo();
            printf("--- MODIFICA PARAMETRI (Cheat Mode) ---\n");
            printf("File: %s\n", riga);
            printf("Attuali -> HP: %d | Monete: %d | Missioni: %d\n", hp, monete, missioni);
            
            printf("1) Modifica HP\n2) Modifica Monete\n3) Sblocca Finale\n4) Annulla\nScegli: ");
            int scelta = leggiIntLocale();
            bool modificato = false;

            if (scelta == 1) { printf("Nuovi HP: "); hp = leggiIntLocale(); modificato = true; }
            else if (scelta == 2) { printf("Nuove Monete: "); monete = leggiIntLocale(); modificato = true; }
            else if (scelta == 3) { printf("Finale Sbloccato.\n"); missioni = 3; modificato = true; }

            if (modificato) {
                FILE *file_scrittura = fopen(percorso_completo, "w");
                if (file_scrittura != NULL) {
                    fprintf(file_scrittura, "%s, ", dataStr);
                    fprintf(file_scrittura, "punti_vita: %d, ", hp);
                    fprintf(file_scrittura, "monete: %d, ", monete);
                    fprintf(file_scrittura, "oggetti: %d, ", oggetti);
                    fprintf(file_scrittura, "missioni_completate: %d\n", missioni);
                    fclose(file_scrittura);
                    printf("Salvataggio modificato!\n");
                }
            }
            trovato = true;
            break; 
        }
        contatore++;
    }
    PCLOSE(out);
    if (!trovato) printf("Salvataggio non trovato.\n");
}