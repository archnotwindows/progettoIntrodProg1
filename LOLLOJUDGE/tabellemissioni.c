#include "tabellemissioni.h"

// Tabella 2: Palude Putrescente
struct RigaDungeon TabellaPalude[] = {
    {"Cane Selvaggio",      TIPO_COMBATTIMENTO, 2, 1, 0, 0},  // Dado 1
    {"Goblin",              TIPO_COMBATTIMENTO, 3, 2, 2, 0},  // Dado 2
    {"Scheletro",           TIPO_COMBATTIMENTO, 4, 2, 4, 0},  // Dado 3
    {"Orco",                TIPO_COMBATTIMENTO, 3, 4, 6, 0},  // Dado 4
    {"Acquitrino Velenoso", TIPO_TRAPPOLA,      0, -1, 0, 0}, // Dado 5 (Danno 1d6)
    {"Generale Orco",       TIPO_COMBATTIMENTO, 6, 3, 12, 1}  // Dado 6 (Obiettivo!)
};

// Tabella 3: Magione Infestata
struct RigaDungeon TabellaMagione[] = {
    {"Botola Buia",        TIPO_TRAPPOLA,       0, 3, 0, 0},  // Dado 1
    {"Pipistrello",        TIPO_COMBATTIMENTO,  2, 2, 1, 0},  // Dado 2
    {"Zombie",             TIPO_COMBATTIMENTO,  3, 2, 2, 0},  // Dado 3
    {"Fantasma",           TIPO_COMBATTIMENTO,  5, 2, 4, 0},  // Dado 4
    {"Vampiro Superiore",  TIPO_COMBATTIMENTO,  4, 4, 7, 1},  // Dado 5 (Obiettivo!)
    {"Demone Custode",     TIPO_COMBATTIMENTO,  4, 6, 10, 2}  // Dado 6 (Obiettivo + chiave!)
};

// Tabella 4: Grotta di Cristallo
struct RigaDungeon TabellaGrotta[] = {
    {"Stanza Vuota",       TIPO_VUOTA,          0, 0, 0, 0},   // Dado 1
    {"Cristalli Cadenti",  TIPO_TRAPPOLA,       0, 2, 0, 0},   // Dado 2
    {"Ponte Pericolante",  TIPO_TRAPPOLA,       0, 0, -3, 0},  // Dado 3 (perde monete)
    {"Forziere Misterioso",TIPO_TRAPPOLA,       0, -2, 10, 0}, // Dado 4 (speciale)
    {"Rupe Scoscesa",      TIPO_TRAPPOLA,       0, -1, 0, 0},  // Dado 5 (Danno 1d6)
    {"Drago Antico",       TIPO_COMBATTIMENTO,  5, 10, 12, 1}  // Dado 6 (Obiettivo!)
};