#include <stdio.h>
#include <stdlib.h>

/*
    Struttura che rappresenta il giocatore.
    Contiene le statistiche principali che verranno usate nel gioco.
*/
struct Giocatore
{
    int punti_vita;          // Vita attuale del giocatore
    int monete;              // Monete possedute
    int oggetti;             // Numero di oggetti
    int missioniCompletate;  // Missioni completate
};

/*
    Funzione che genera una mossa casuale per il Signore Oscuro.
    Ritorna un valore tra 1 e 3:
    1 = Scudo
    2 = Magia
    3 = Spada
*/
int mossarandom()
{
    int x;
    x = rand() % 3;
    return x + 1;
}

/*
    Funzione che gestisce il combattimento finale.
    Il combattimento funziona come sasso-carta-forbici.
    Vince chi arriva prima a 3 round vinti (best of 5).

    Parametro:
    g -> struct Giocatore (passata per valore)

    Ritorna:
    1 se il giocatore vince
    0 se il giocatore perde
*/
int CombattimentoFinale(struct Giocatore g)
{
    // Array di stringhe con i nomi delle mosse
    char* scelta[3] = {"Scudo","Magia","Spada"};

    int risultato = 0;
    int vittorie_g = 0;  // Round vinti dal giocatore
    int vittorie_s = 0;  // Round vinti dal Signore Oscuro

    int round;
    round = 1;

    // Ciclo dei round (massimo 5)
    while (round <= 5)
    {
        int scelta_g; // Mossa del giocatore
        int scelta_s; // Mossa del Signore Oscuro

        printf("\nRound %d\n", round);
        printf("1. Scudo\n2. Magia\n3. Spada\n");
        printf("Scegli: ");
        scanf("%d", &scelta_g);

        // Controllo input valido
        while (scelta_g < 1 || scelta_g > 3)
        {
            printf("No, rifai: ");
            scanf("%d", &scelta_g);
        }

        // Generazione mossa del Signore Oscuro
        scelta_s = mossarandom();

        // Stampa delle mosse scelte
        printf("Tu -> %s\n", scelta[scelta_g - 1]);
        printf("Signore Oscuro -> %s\n", scelta[scelta_s - 1]);

        // Caso di pareggio
        if (scelta_g == scelta_s)
        {
            printf("Pareggio\n");
            round++;
            continue;
        }

        // Controllo delle combinazioni vincenti del giocatore
        if (
            (scelta_g == 1 && scelta_s == 3) ||  // Scudo batte Spada
            (scelta_g == 2 && scelta_s == 1) ||  // Magia batte Scudo
            (scelta_g == 3 && scelta_s == 2)     // Spada batte Magia
           )
        {
            vittorie_g++;
            printf("Round vinto\n");
        }
        else
        {
            vittorie_s++;
            printf("Round perso\n");
        }

        round++;
    }

    // Determinazione del risultato finale
    if (vittorie_g > vittorie_s)
    {
        risultato = 1;
    }

    return risultato;
}

/*
    Funzione ricorsiva che calcola l'n-esimo numero
    della sequenza di Padovan.

    Definizione:
    P(0) = P(1) = P(2) = 1
    P(n) = P(n-2) + P(n-3)
*/
int Padovan(int n)
{
    int padovannum = 0;

    if (n == 0 || n == 1 || n == 2)
    {
        padovannum = 1;
    }
    else
    {
        // Chiamate ricorsive
        padovannum = Padovan(n - 2) + Padovan(n - 3);
    }

    return padovannum;
}

/*
    Funzione principale del programma.
    Inizializza il giocatore, avvia il combattimento finale
    e stampa il risultato.
*/
int main()
{
    struct Giocatore rando;

    // Inizializzazione delle statistiche del giocatore
    rando.punti_vita = 100;
    rando.missioniCompletate = 10;
    rando.monete = 256;

    int risultato;

    // Avvio del combattimento finale
    risultato = CombattimentoFinale(rando);

    // Stampa esito combattimento
    if (risultato == 1)
        printf("\nHAI VINTO\n");
    else
        printf("\nSEI MORTO\n");

    // Test della funzione Padovan
    int padovannum = Padovan(10);
    printf("\nPadovan(10) = %d\n", padovannum);

    return 0;
}
