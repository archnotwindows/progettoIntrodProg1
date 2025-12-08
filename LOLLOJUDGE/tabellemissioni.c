#include "tabellemissioni.h"

// Tabella 2: Palude Putrescente [cite: 134]
struct RigaDungeon TabellaPalude[] = {
    {"Cane Selvaggio",      TIPO_COMBATTIMENTO, 2, 1, 0, 0}, // Dado 1
    {"Goblin",              TIPO_COMBATTIMENTO, 3, 2, 2, 0}, // Dado 2
    {"Scheletro",           TIPO_COMBATTIMENTO, 4, 2, 4, 0}, // Dado 3
    {"Orco",                TIPO_COMBATTIMENTO, 3, 4, 6, 0}, // Dado 4
    {"Acquitrino Velenoso", TIPO_TRAPPOLA,      0, -1, 0, 0},// Dado 5 (Danno -1 indica 1d6)
    {"Generale Orco",       TIPO_COMBATTIMENTO, 6, 3, 12, 1} // Dado 6 (Obiettivo!)
};

// Qui dovrai aggiungere TabellaMagione e TabellaGrotta seguendo lo stesso schema