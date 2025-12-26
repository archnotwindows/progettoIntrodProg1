#ifndef TABELLEMISSIONI_H
#define TABELLEMISSIONI_H

typedef enum {
    TIPO_COMBATTIMENTO,
    TIPO_TRAPPOLA,
    TIPO_VUOTA
} TipoStanza;

struct RigaDungeon {
    char* nome;
    TipoStanza tipo;
    int colpo_fatale;   // Difficoltà per colpire o evitare
    int danno;          // Danno in caso di fallimento
    int monete;         // Ricompensa
    int is_obiettivo;   // 1=Obiettivo principale, 2=Obiettivo secondario
};

extern struct RigaDungeon TabellaPalude[];
extern struct RigaDungeon TabellaMagione[];
extern struct RigaDungeon TabellaGrotta[];

#endif