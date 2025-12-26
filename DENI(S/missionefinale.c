#include <stdio.h>
#include <stdlib.h>

struct Giocatore
{
    int punti_vita;
    int monete;
    int oggetti;
    int missioniCompletate;
};

int mossarandom()
{
    int x;
    x = rand() % 3;
    return x + 1;
}

int CombattimentoFinale(struct Giocatore g)
{
    char* scelta[3] = {"Scudo","Magia","Spada"};
    int risultato = 0;
    int vittorie_g = 0;
    int vittorie_s = 0;

    int round;
    round = 1;

    while (round <= 5)
    {
        int scelta_g;
        int scelta_s;

        printf("\nRound %d\n", round);
        printf("1. Scudo\n2. Magia\n3. Spada\n");
        printf("Scegli: ");
        scanf("%d", &scelta_g);

        while (scelta_g < 1 || scelta_g > 3)
        {
            printf("No, rifai: ");
            scanf("%d", &scelta_g);
        }

        scelta_s = mossarandom();

        printf("Tu -> %s\n", scelta[scelta_g - 1]);
        printf("Signore Oscuro -> %s\n", scelta[scelta_s - 1]);

        if (scelta_g == scelta_s)
        {
            printf("Pareggio\n");
            round++;
            continue;
        }

        if (
            (scelta_g == 1 && scelta_s == 3) ||
            (scelta_g == 2 && scelta_s == 1) ||
            (scelta_g == 3 && scelta_s == 2)
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


    }
    if (vittorie_g > vittorie_s)
    {
        risultato = 1;
    }
    

}


int Padovan(int n)
{
    int padovannum = 0;
        if (n == 0 || n == 1 || n == 2)
        {
           padovannum = 1;
        }
        else 
        {
            padovannum =  (n - 2) + (n - 3);
        }
        return padovannum;
        

    
}

int main()
{

    struct Giocatore rando;

    rando.punti_vita = 100;
    rando.missioniCompletate = 10;
    rando.monete = 256;
    int risultato;

    risultato = CombattimentoFinale(rando);

    if (risultato == 1)
        printf("\nHAI VINTO\n");
    else
        printf("\nSEI MORTO\n");


    int padovannum = Padovan(10);

    printf ("%d" ,padovannum );
}
 