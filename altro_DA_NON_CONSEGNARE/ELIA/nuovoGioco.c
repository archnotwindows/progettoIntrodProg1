#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pulisciSchermo.h"
#include "nuovoGioco.h"
#include "salvataggi.h"

int leggiIntero() {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; 
        return atoi(buffer);
    }
    return -1;
}

void stampaMenu(bool trucchiAttivi){
    pulisciSchermo();
    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
    if ( trucchiAttivi ){
        printf("|    La Fuga dal while(1)      [+]trucchi attivi    |\n");
    } else {
        printf("|            La Fuga dal while(1)                   |\n");
    }
    printf("| 1) Nuova partita                                  |\n");
    printf("| 2) Carica salvataggio                             |\n");  
    printf("| 3) Esci                                           |\n");
    printf("+ - - - - - - - - - - - - - - - - - - - - - - - - - +\n");
}

void nuovoGioco(){
    char action[100];
    bool trucchiAttivi = false; 
    bool uscita = false;

    // Variabili del giocatore (in futuro andranno in una struct o passate al modulo Villaggio)
    int giocatoreHP = 20;
    int giocatoreMonete = 0;
    int giocatoreOggetti = 0;
    int giocatoreMissioni = 0;

    while ( !uscita ){
        stampaMenu(trucchiAttivi);
        printf("Scegli un'opzione: ");    

        if (fgets(action, sizeof(action), stdin) == NULL) continue; 
        
        if (triggherTrucchi(action[0]) == true) {
            trucchiAttivi = true;
            printf("\n!!! TRUCCHI SBLOCCATI !!!\nPremi Invio...");
            getchar();
            continue;
        }

        int intAction = atoi(action);
            
        if ( intAction == 1 ) {
            // Nuova partita
            time_t tempoNow = time(NULL);
            struct tm *infoTempo = localtime(&tempoNow);
            char nomeFile[80];
            char percorsoFile[200];
            char data[80];
            
            // Uso trattini per compatibilità Windows
            strftime(nomeFile, sizeof(nomeFile), "%d-%m-%Y_%H-%M-%S", infoTempo);
            sprintf(percorsoFile, "salvataggi/%s.txt", nomeFile);
            strftime(data, sizeof(data), "%d-%m-%Y %H-%M-%S", infoTempo);

            nuovoSalvataggio(percorsoFile, data);
            
            printf("Partita creata! Ora dovresti andare al Villaggio...\n");
            printf("Premi Invio per tornare al menu...");
            getchar();
        }

        else if ( intAction == 2 ){
            int elenco = listaSalvataggi();
            if (elenco == 0) {
                printf("Premi Invio...");
                getchar();
                continue;
            }

            printf("Scegli un salvataggio da caricare [1-%d]: ", elenco);
            int nSalvataggio = leggiIntero();

            if ( nSalvataggio <= elenco && nSalvataggio > 0 ){
                int azione;
                printf("\n--- Gestione Salvataggio %d ---\n", nSalvataggio);
                printf("1) Carica Salvataggio\n2) Elimina salvataggio\n");
                
                if ( trucchiAttivi ) printf("3) Modifica salvataggio (Cheat)\n");
                
                printf("Scegli azione: ");
                azione = leggiIntero();
                                
                if ( azione == 1 ){
                    // CARICAMENTO EFFETTIVO (Risolto TODO)
                    if (caricaDatiSalvataggio(nSalvataggio, &giocatoreHP, &giocatoreMonete, &giocatoreOggetti, &giocatoreMissioni)) {
                        printf("\n--- PARTITA CARICATA ---\n");
                        printf("HP: %d | Monete: %d | Missioni: %d\n", giocatoreHP, giocatoreMonete, giocatoreMissioni);
                        printf("Benvenuto al Villaggio! (Logica villaggio da implementare qui)\n");
                    } else {
                        printf("Errore nel caricamento del file.\n");
                    }
                    printf("Premi Invio...");
                    getchar();
                } 
                else if ( azione == 2 ){
                    printf("Sicuro? (1=Si, 2=No): ");
                    if ( leggiIntero() == 1 ) eliminaSalvataggio(nSalvataggio);
                }
                else if ( trucchiAttivi && azione == 3){
                    modificaSalvataggio(nSalvataggio);
                    printf("Premi Invio...");
                    getchar();
                }
            }    
        }
        else if ( intAction == 3 ) uscita = true;
    }
}