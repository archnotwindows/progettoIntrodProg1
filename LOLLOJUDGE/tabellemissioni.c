
struct RigaDungeon {
    char nome[30];      
    char tipo;          
    int colpo_fatale;   
    int danno_nemico;   
    int monete_vittoria;
};


struct RigaDungeon Palude[6] = {
    // Nome             Tipo  ColpoFatale Danno Monete
    {"Cane Selvaggio",  'C',      2,        1,    0}, // Dado 1 (indice 0)
    {"Goblin",          'C',      3,        2,    2}, // Dado 2 (indice 1)
    {"Scheletro",       'C',      4,        2,    4}, // Dado 3 (indice 2)
    {"Orco",            'C',      3,        4,    6}, // Dado 4 (indice 3)
    {"Acquitrino",      'T',      0,        0,    0}, // Dado 5 (Trappola speciale)
    {"Generale Orco",   'C',      6,        3,   12}  // Dado 6 (indice 5)
};