#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- 1. STRUTTURE DATI ---

// Rappresenta il Giocatore [cite: 22, 169]
typedef struct {
    int vita;               // Max 20
    int monete;
    int ha_spada;           // 0 = No, 1 = Sì (+1 attacco)
    int missioni_completate;
} Giocatore;

// Tipi di stanza
typedef enum { TIPO_COMBATTIMENTO, TIPO_TRAPPOLA } TipoStanza;

// Rappresenta una riga della tabella della missione (es. Tabella 2)
typedef struct {
    char nome[50];
    TipoStanza tipo;        // Riutilizzo il typedef dei tipi di stanza
    int colpo_fatale;       // Quanto serve col dado per vincere
    int danno;              // Danno subito se si perde o trappola fissa
    int monete_vittoria;    // Monete guadagnate
    int is_obiettivo;       // 1 se è il "Generale Orco", 0 altrimenti
} RigaDungeon;

// --- 2. TABELLA DATI (Missione 1: Palude Putrescente)  ---
// Indici: 0=Cane, 1=Goblin, 2=Scheletro, 3=Orco, 4=Acquitrino, 5=Generale
const RigaDungeon TabellaPalude[6] = {
    {"Cane Selvaggio",      TIPO_COMBATTIMENTO, 2, 1, 1,  0},
    {"Goblin",              TIPO_COMBATTIMENTO, 3, 2, 2,  0},
    {"Scheletro",           TIPO_COMBATTIMENTO, 4, 2, 4,  0},
    {"Orco",                TIPO_COMBATTIMENTO, 3, 4, 6,  0},
    {"Acquitrino Velenoso", TIPO_TRAPPOLA,      0, -1, 0, 0}, // -1 indica danno casuale 1-6
    {"Generale Orco",       TIPO_COMBATTIMENTO, 6, 3, 12, 1}  // È l'obiettivo!
};

// --- 3. FUNZIONI DI UTILITÀ ---

// Lancia un dado che restituisce tra 1 e 6
int lanciaDado() {
    return rand() % 6 + 1;
}

// Funzione principale della Missione 1
void missionePaludePutrescente(Giocatore* g) {
    printf("\n=== MISSIONE AVVIATA: PALUDE PUTRESCENTE ===\n");
    printf("Obiettivo: Sconfiggi 3 Generali Orco. [cite: 72]\n");

    int generali_sconfitti = 0;
    const int OBIETTIVO = 3;
    const int MAX_STANZE = 10; // [cite: 102]

    // Ciclo delle stanze (massimo 10)
    for (int i = 1; i <= MAX_STANZE; i++) {
        
        // Controllo se il giocatore è morto
        if (g->vita <= 0) {
            printf("\nSei morto! Game Over.\n");
            return;
        }

        // Controllo vittoria anticipata
        if (generali_sconfitti >= OBIETTIVO) {
            printf("\n>>> VITTORIA! Hai sconfitto 3 Generali Orco! <<<\n");
            g->missioni_completate++;
            return;
        }

        printf("\n--- STANZA %d/%d (Generali sconfitti: %d/%d) ---\n", 
               i, MAX_STANZE, generali_sconfitti, OBIETTIVO);

        // --- LOGICA DI FORZATURA ---
        int indice_scelto;
        int stanze_rimanenti = MAX_STANZE - i + 1;
        int generali_mancanti = OBIETTIVO - generali_sconfitti;

        /* Se il numero di Generali che mi mancano è uguale al numero 
           di stanze rimaste, DEVO forzare l'uscita del Generale. */
        if (generali_mancanti >= stanze_rimanenti) {
            printf("(!) Senti una presenza oscura... Il destino forza l'incontro!\n");
            indice_scelto = 5; // Indice del Generale Orco nella tabella
        } else {
            // Altrimenti, generazione casuale (dado 1-6 -> indice 0-5)
            int tiro = lanciaDado();
            indice_scelto = tiro - 1; 
            printf("Tiro dado stanza: %d -> ", tiro);
        }

        RigaDungeon stanza = TabellaPalude[indice_scelto];
        printf("Incontri: %s\n", stanza.nome);

        // --- GESTIONE TRAPPOLA ---
        if (stanza.tipo == TIPO_TRAPPOLA) {
            int danno_subito = stanza.danno;
            // Caso speciale Acquitrino: danno 1-6 
            if (danno_subito == -1) {
                danno_subito = lanciaDado();
            }
            printf("TRAPPOLA! Subisci %d danni.\n", danno_subito);
            g->vita -= danno_subito;
            printf("Vita residua: %d\n", g->vita);
        } 
        
        // --- GESTIONE COMBATTIMENTO ---
        else if (stanza.tipo == TIPO_COMBATTIMENTO) {
            int nemico_vivo = 1;
            
            // Ciclo di combattimento 
            while (nemico_vivo && g->vita > 0) {
                printf("  [INVIO] per attaccare (Vita: %d)...", g->vita);
                while(getchar() != '\n'); // Pausa per input utente

                int dado = lanciaDado();
                int attacco_totale = dado;
                
                // Bonus Spada 
                if (g->ha_spada) {
                    attacco_totale += 1;
                    printf("  Roll: %d (+1 Spada) = %d ", dado, attacco_totale);
                } else {
                    printf("  Roll: %d ", dado);
                }

                // Gestione specifica: Generale Orco ha Colpo Fatale 5 se hai la spada 
                int soglia_vittoria = stanza.colpo_fatale;
                if (stanza.is_obiettivo && g->ha_spada) {
                    soglia_vittoria = 5; 
                }

                printf("vs Colpo Fatale: %d -> ", soglia_vittoria);

                if (attacco_totale > soglia_vittoria) { // Nota: PDF dice ">" 
                    printf("VINTO!\n");
                    printf("  Guadagni %d monete.\n", stanza.monete_vittoria);
                    g->monete += stanza.monete_vittoria;
                    nemico_vivo = 0;
                    
                    // Se era un obiettivo, incrementiamo il contatore
                    if (stanza.is_obiettivo) {
                        generali_sconfitti++;
                    }
                } else {
                    printf("PERSO.\n");
                    printf("  Il nemico contrattacca! Subisci %d danni.\n", stanza.danno);
                    g->vita -= stanza.danno;
                }
            }
        }
    }

    // Fine delle stanze
    if (g->vita > 0 && generali_sconfitti < OBIETTIVO) {
        printf("\nMissione fallita: Sei uscito dal dungeon senza sconfiggere abbastanza generali.\n");
    } else if (generali_sconfitti >= OBIETTIVO) {
         printf("\n>>> COMPLIMENTI! MISSIONE COMPLETATA! <<<\n");
    }
}

// --- 4. MAIN ---
int main() {
    srand(time(NULL)); // Inizializza il generatore casuale

    // Creiamo un giocatore 
    Giocatore eroe;
    eroe.vita = 20;       
    eroe.monete = 0;
    eroe.ha_spada = 0;    // Metti a 1 per testare col bonus spada
    eroe.missioni_completate = 0;

    // Avviamo la missione
    missionePaludePutrescente(&eroe);

    return 0;
}