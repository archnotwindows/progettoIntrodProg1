/**
 * @file salvataggi.c
 * @brief Implementazione del sistema di gestione file dei salvataggi.
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

/**
 * @brief Verifica l'esistenza della directory "salvataggi", creandola se necessario.
 */
void checkDirSalvataggi(){
    struct stat st = {0};
    if (stat("salvataggi", &st) == -1) {
        MKDIR("salvataggi");
    }
}

void nuovoSalvataggio(Giocatore *g){
    checkDirSalvataggi();   

    time_t tempoNow = time(NULL);
    struct tm *infoTempo = localtime(&tempoNow);
    char nomeFile[80];
    char percorsoFile[200];
    char data[80];
    
    strftime(nomeFile, sizeof(nomeFile), "%d-%m-%Y_%H-%M-%S", infoTempo);
    sprintf(percorsoFile, "salvataggi/%s.txt", nomeFile);
    strftime(data, sizeof(data), "%d-%m-%Y %H-%M-%S", infoTempo);

    FILE *f = fopen(percorsoFile, "w");
    if (f == NULL){
        printf("Errore creazione file: %s\n", nomeFile);
        return;
    } 

    fprintf(f, "%s\n", data);
    fprintf(f, "%d %d %d\n", g->vita, g->monete, g->attacco);
    fprintf(f, "%d %d %d %d\n", g->ha_spada, g->ha_armatura, g->ha_spada_eroe, g->ha_chiave);
    fprintf(f, "%d %d %d\n", g->missione_palude_completata, g->missione_magione_completata, g->missione_grotta_completata);

    fclose(f);
    printf("Partita salvata in %s\n", nomeFile);
}

int caricaDatiSalvataggio(int numeroSalvataggio, Giocatore* g){
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
            
            FILE *f = fopen(percorso_completo, "r");
            if (f == NULL) break;

            char dataBuff[100];
            fgets(dataBuff, sizeof(dataBuff), f); 
            
            int h_spada, h_arm, h_s_eroe, h_chiave;
            int m_pal, m_mag, m_gro;

            fscanf(f, "%d %d %d", &g->vita, &g->monete, &g->attacco);
            fscanf(f, "%d %d %d %d", &h_spada, &h_arm, &h_s_eroe, &h_chiave);
            fscanf(f, "%d %d %d", &m_pal, &m_mag, &m_gro);
            
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

bool triggherTrucchi(char tasto){
    static int c = 0; 
    const char code[] = "wwssadadba "; 
    if (tasto == code[c]) {
        c++; 
        if (c == strlen(code)) { c = 0; return true; }
    } else {
        c = (tasto == 'w') ? 1 : 0;
    }
    return false;
}

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
            
            // 1. Carica i dati attuali
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

            // 2. Menu Modifica
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

            // 3. Salva le modifiche (Sovrascrive lo stesso file)
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