#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIMENSIUNE 100

typedef struct NodStiva {
    char cafea[50];
    struct NodStiva* urmator;
} NodStiva;

typedef struct Stiva {
    NodStiva* varf;
} Stiva;

Stiva* creeazaStiva() {
    Stiva* s = (Stiva*)malloc(sizeof(Stiva));
    s->varf = NULL;
    return s;
}

void impinge(Stiva* s, char* cafea) {
    NodStiva* nod = (NodStiva*)malloc(sizeof(NodStiva));
    strcpy(nod->cafea, cafea);
    nod->urmator = s->varf;
    s->varf = nod;
}

char* scoate(Stiva* s) {
    if (s->varf == NULL) return NULL;
    NodStiva* temp = s->varf;
    s->varf = temp->urmator;
    char* cafea = (char*)malloc(50);
    strcpy(cafea, temp->cafea);
    free(temp);
    return cafea;
}



typedef struct Intrare {
    int cheie;
    char valoare[50];
    struct Intrare* urmator;
} Intrare;

typedef struct TabelaHash {
    Intrare* lista[DIMENSIUNE];
} TabelaHash;

int functieHash(int cheie) {
    return cheie % DIMENSIUNE;
}

TabelaHash* creeazaTabela() {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    for (int i = 0; i < DIMENSIUNE; i++) {
        tabela->lista[i] = NULL;
    }
    return tabela;
}

void insereaza(TabelaHash* tabela, int cheie, char* valoare) {
    int index = functieHash(cheie);
    Intrare* nou = (Intrare*)malloc(sizeof(Intrare));
    nou->cheie = cheie;
    strcpy(nou->valoare, valoare);
    nou->urmator = tabela->lista[index];
    tabela->lista[index] = nou;
}

char* cauta(TabelaHash* tabela, int cheie) {
    int index = functieHash(cheie);
    Intrare* curent = tabela->lista[index];
    while (curent) {
        if (curent->cheie == cheie) {
            return curent->valoare;
        }
        curent = curent->urmator;
    }
    return NULL;
}



int main() {
    Stiva* stivaCafea = creeazaStiva();
    impinge(stivaCafea, "Espresso");
    impinge(stivaCafea, "Latte");

    char* servit = scoate(stivaCafea);
    if (servit) {
        printf("Servit: %s\n", servit);
        free(servit);
    }

    TabelaHash* tabelaMeniu = creeazaTabela();
    insereaza(tabelaMeniu, 1, "Cappuccino");
    insereaza(tabelaMeniu, 2, "Americano");

    char* rezultat = cauta(tabelaMeniu, 1);
    if (rezultat) {
        printf("Gasit: %s\n", rezultat);
    }

    return 0;
}