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
    int colpo_fatale;   // Se è trappola: 0 = danno fisso, -1 = danno 1d6
    int danno;          // Danno subito se si perde o si cade nella trappola
    int monete;         // Monete guadagnate
    int is_obiettivo;   // 1 se è il mostro obiettivo, 2 per obiettivi secondari (es. chiave)
};

// Array esterni per le tabelle
extern struct RigaDungeon TabellaPalude[];
extern struct RigaDungeon TabellaMagione[];
extern struct RigaDungeon TabellaGrotta[];

#endif