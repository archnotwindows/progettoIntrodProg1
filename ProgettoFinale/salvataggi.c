/**
 * @file salvataggi.c
 * @brief Implementazione del sistema di gestione file (I/O) e persistenza dati.
 * * Questo modulo gestisce la creazione, lettura, modifica ed eliminazione dei file
 * di salvataggio. Include anche la logica per la compatibilità tra Windows e Unix
 * e un sistema di riconoscimento pattern per l'attivazione della "Cheat Mode".
 */

#define _POSIX_C_SOURCE 200809L 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "salvataggi.h"
#include "systemclear.h" 
#include "giocatore.h"

/**
 * @brief Blocco di compatibilità Cross-Platform.
 * Definisce macro specifiche per i comandi di shell e le funzioni di sistema
 * a seconda che si stia compilando su Windows (_WIN32) o Unix/Linux/macOS.
 */
#ifdef _WIN32       
    #include <direct.h>
    #define POPEN _popen   /**< Apre una pipe di processo su Windows */
    #define PCLOSE _pclose /**< Chiude la pipe su Windows */
    #define LIST_COMMAND "dir /b salvataggi\\" /**< Comando CMD per listare file */
    #define DIR_SEPARATOR "\\" 
    #define MKDIR(p) _mkdir(p) /**< Funzione creazione cartella Windows */
#else       
    #include <unistd.h>
    #define POPEN popen    /**< Apre una pipe di processo su Unix */
    #define PCLOSE pclose  /**< Chiude la pipe su Unix */
    #define LIST_COMMAND "ls -1 salvataggi/"   /**< Comando Bash per listare file */
    #define DIR_SEPARATOR "/" 
    #define MKDIR(p) mkdir(p, 0700) /**< Funzione creazione cartella Unix (con permessi) */
#endif

/**
 * @brief Verifica l'esistenza della directory "salvataggi", creandola se necessario.
 * Utilizza la struct stat per controllare i metadati del filesystem.
 */
void checkDirSalvataggi(){
    struct stat st = {0};
    if (stat("salvataggi", &st) == -1) {
        MKDIR("salvataggi");
    }
}

/**
 * @brief Crea un nuovo file di salvataggio.
 * * Il nome del file viene generato automaticamente usando il timestamp corrente
 * (con il formato: GG-MM-AAAA_HH-MM-SS).
 * * Scrive i dati della struct Giocatore in formato testo semplice.
 * @param g Puntatore ai dati del giocatore da salvare.
 */
void nuovoSalvataggio(Giocatore *g){
    checkDirSalvataggi();   

    time_t tempoNow = time(NULL);
    struct tm *infoTempo = localtime(&tempoNow);
    char nomeFile[80];
    char percorsoFile[200];
    char data[80];
    
    /* Formatta il nome del file e la data leggibile */
    strftime(nomeFile, sizeof(nomeFile), "%d-%m-%Y_%H-%M-%S", infoTempo);
    sprintf(percorsoFile, "salvataggi/%s.txt", nomeFile);
    strftime(data, sizeof(data), "%d-%m-%Y %H-%M-%S", infoTempo);

    FILE *f = fopen(percorsoFile, "w");
    if (f == NULL){
        printf("Errore creazione file: %s\n", nomeFile);
        return;
    } 

    /* Serializzazione dati */
    fprintf(f, "%s\n", data); /* Riga 1: Data  */
    fprintf(f, "%d %d %d\n", g->vita, g->monete, g->attacco); /* Riga 2: Statistiche */
    fprintf(f, "%d %d %d %d\n", g->ha_spada, g->ha_armatura, g->ha_spada_eroe, g->ha_chiave); /* Riga 3: Inventario */
    fprintf(f, "%d %d %d\n", g->missione_palude_completata, g->missione_magione_completata, g->missione_grotta_completata); /* Riga 4: Quest */

    fclose(f);
    printf("Partita salvata in %s\n", nomeFile);
}

/**
 * @brief Carica i dati da un file specifico nella struct Giocatore.
 * Utilizza una pipe per ottenere la lista dei file e seleziona l'n-esimo file.
 * @param numeroSalvataggio Indice del file nella lista (1-based).
 * @param g Puntatore alla struct Giocatore da popolare.
 * @return 1 se il caricamento ha successo, 0 altrimenti.
 */
int caricaDatiSalvataggio(int numeroSalvataggio, Giocatore* g){
    FILE *out;
    char riga[256];      
    int contatore = 1;     
    
    /* Esegue il comando di sistema (ls o dir) e legge l'output */
    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ) return 0;

    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; /* Rimuove newline */
        if (strlen(riga) < 3) continue; /* Ignora file spuri/vuoti */

        if (contatore == numeroSalvataggio) {
            char percorso_completo[512];
            sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
            
            FILE *f = fopen(percorso_completo, "r");
            if (f == NULL) break;

            char dataBuff[100];
            fgets(dataBuff, sizeof(dataBuff), f); /* Salta intestazione data */
            
            /* Variabili temporanee per lettura */
            int h_spada, h_arm, h_s_eroe, h_chiave;
            int m_pal, m_mag, m_gro;

            /* Parsing dei dati */
            fscanf(f, "%d %d %d", &g->vita, &g->monete, &g->attacco);
            fscanf(f, "%d %d %d %d", &h_spada, &h_arm, &h_s_eroe, &h_chiave);
            fscanf(f, "%d %d %d", &m_pal, &m_mag, &m_gro);
            
            /* Assegnazione boolean (conversione int -> bool implicita) */
            g->ha_spada = h_spada; g->ha_armatura = h_arm;
            g->ha_spada_eroe = h_s_eroe; g->ha_chiave = h_chiave;
            g->missione_palude_completata = m_pal;
            g->missione_magione_completata = m_mag;
            g->missione_grotta_completata = m_gro;

            fclose(f);
            PCLOSE(out);
            return 1; 
        }
        contatore++;
    }
    PCLOSE(out);
    return 0; 
}

/**
 * @brief Stampa l'elenco dei file di salvataggio disponibili.
 * @return Il numero totale di salvataggi trovati.
 */
int listaSalvataggi(){
    FILE *out;
    char riga[256];      
    int elenco = 1;     

    puliscischermo();
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
        printf("  %d) %s\n", elenco, riga);
        elenco++;
    }
    PCLOSE(out);

    if ( elenco == 1 ){     
        printf("   (Nessun salvataggio trovato)\n");
        return 0;
    }
    return elenco-1;
}

/**
 * @brief Elimina un file di salvataggio dal disco.
 * @param numeroDaEliminare Indice del file da cancellare.
 */
void eliminaSalvataggio(int numeroDaEliminare){
    FILE *out;
    char riga[256];      
    int contatore = 1;     
    
    out = POPEN(LIST_COMMAND, "r");
    if (!out) return;

    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; 
        if (strlen(riga) < 3) continue;

        if (contatore == numeroDaEliminare) {
            char percorso[512];
            sprintf(percorso, "salvataggi%s%s", DIR_SEPARATOR, riga);
            
            /* Cancellazione effettiva */
            remove(percorso);
            printf("File eliminato.\n");
            break; 
        }
        contatore++;
    }
    PCLOSE(out);
    printf("Premi INVIO per continuare...");
    getchar(); 
}



/**
 * @brief Rilevatore di sequenze di tasti per attivare la "Cheat Mode".
 * * Sequenza segreta: "wwssadadba "
 * * @param tasto Il carattere appena inserito dall'utente.
 * @return true se la sequenza è stata completata, sennó false.
 */
bool triggherTrucchi(char tasto){
    static int c = 0; /**< Variabile statica: conserva il valore tra le chiamate della funzione */
    const char code[] = "wwssadadba "; 
    
    if (tasto == code[c]) {
        c++; /* Avanza nella sequenza */
        /* Se la sequenza è finita, resetta contatore e ritorna true */
        if (c == strlen(code)) { c = 0; return true; }
    } else {
        /* Reset parziale: se sbagli, controlla se il tasto premuto può essere l'inizio di una nuova sequenza */
        c = (tasto == 'w') ? 1 : 0;
    }
    return false;
}

/**
 * @brief Funzione di debug/cheating per modificare i salvataggi.
 * Permette di editare un file esistente alterando statistiche o flag di completamento.
 * @param numeroSalvataggio Indice del file da modificare.
 */
void modificaSalvataggio(int numeroSalvataggio) {
    FILE *out;
    char riga[256];      
    int contatore = 1;     
    
    out = POPEN(LIST_COMMAND, "r");
    if ( out == NULL ) return;

    while (fgets(riga, sizeof(riga), out) != NULL) {  
        riga[strcspn(riga, "\n")] = 0; 
        if (strlen(riga) < 3) continue;

        if (contatore == numeroSalvataggio) {
            char percorso_completo[512];
            sprintf(percorso_completo, "salvataggi%s%s", DIR_SEPARATOR, riga);
            
            /* --- FASE 1: Lettura Dati Attuali --- */
            FILE *f_in = fopen(percorso_completo, "r");
            if (f_in == NULL) break;

            Giocatore g;
            char dataBuff[100];
            fgets(dataBuff, sizeof(dataBuff), f_in); 
            dataBuff[strcspn(dataBuff, "\n")] = 0;   

            int h_spada, h_arm, h_s_eroe, h_chiave;
            int m_pal, m_mag, m_gro;

            fscanf(f_in, "%d %d %d", &g.vita, &g.monete, &g.attacco);
            fscanf(f_in, "%d %d %d %d", &h_spada, &h_arm, &h_s_eroe, &h_chiave);
            fscanf(f_in, "%d %d %d", &m_pal, &m_mag, &m_gro);
            fclose(f_in);

            /* --- FASE 2: Interfaccia di Modifica --- */
            puliscischermo();
            printf("--- MENU TRUCCHI (File: %s) ---\n", riga);
            printf("Attuali -> HP: %d | Monete: %d | Missioni: %d-%d-%d\n", 
                   g.vita, g.monete, m_pal, m_mag, m_gro);
            
            printf("1) Diventa Ricco e Immortale (HP=999, Monete=9999)\n");
            printf("2) Sblocca Missione Finale (Completa le 3 missioni precedenti\n");
            printf("3) Annulla\n");
            printf("Scegli: ");
            
            int scelta;
            char temp[10];
            fgets(temp, sizeof(temp), stdin);
            scelta = atoi(temp);

            bool modificato = false;
            if (scelta == 1) {
                g.vita = 999;
                g.monete = 9999;
                g.attacco = 50;
                printf("Trucchi applicati!\n");
                modificato = true;
            }
            else if (scelta == 2) {
                m_pal = 1; m_mag = 1; m_gro = 1; 
                printf("Missione finale sbloccata!\n");
                modificato = true;
            }

            /* --- FASE 3: Scrittura Dati Modificati --- */
            if (modificato) {
                FILE *f_out = fopen(percorso_completo, "w");
                if (f_out != NULL) {
                    fprintf(f_out, "%s\n", dataBuff); 
                    fprintf(f_out, "%d %d %d\n", g.vita, g.monete, g.attacco);
                    fprintf(f_out, "%d %d %d %d\n", h_spada, h_arm, h_s_eroe, h_chiave);
                    fprintf(f_out, "%d %d %d\n", m_pal, m_mag, m_gro);
                    fclose(f_out);
                }
            }
            
            printf("Premi INVIO...");
            getchar();
            break; 
        }
        contatore++;
    }
    PCLOSE(out);
}