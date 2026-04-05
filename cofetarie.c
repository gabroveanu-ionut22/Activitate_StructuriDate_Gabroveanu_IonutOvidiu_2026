#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Prajitura {
    char nume[50];
    float pret;
} Prajitura;

typedef struct Nod {
    Prajitura produs;
    struct Nod* urmator;
} Nod;



Nod* creare_nod(char* nume, float pret) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    strcpy(nou->produs.nume, nume);
    nou->produs.pret = pret;
    nou->urmator = NULL;
    return nou;
}



void adauga_final(Nod** cap, char* nume, float pret) {
    Nod* nou = creare_nod(nume, pret);

    if (*cap == NULL) {
        *cap = nou;
        return;
    }

    Nod* temp = *cap;
    while (temp->urmator != NULL) {
        temp = temp->urmator;
    }

    temp->urmator = nou;
}



void afisare_lista(Nod* cap) {
    Nod* temp = cap;

    while (temp != NULL) {
        printf("%s - %.2f lei\n", temp->produs.nume, temp->produs.pret);
        temp = temp->urmator;
    }
}



typedef struct Intrare {
    char cheie[50];
    Prajitura valoare;
    struct Intrare* urmator;
} Intrare;



typedef struct HashTable {
    int dimensiune;
    Intrare** bucket;
} HashTable;



unsigned int functie_hash(char* cheie, int dimensiune) {
    unsigned int hash = 0;

    for (int i = 0; cheie[i] != '\0'; i++) {
        hash = hash * 31 + cheie[i];
    }

    return hash % dimensiune;
}



HashTable* creare_tabela(int dimensiune) {
    HashTable* tabela = (HashTable*)malloc(sizeof(HashTable));
    tabela->dimensiune = dimensiune;

    tabela->bucket = (Intrare**)malloc(dimensiune * sizeof(Intrare*));

    for (int i = 0; i < dimensiune; i++) {
        tabela->bucket[i] = NULL;
    }

    return tabela;
}



void inserare(HashTable* tabela, char* cheie, char* nume, float pret) {
    unsigned int index = functie_hash(cheie, tabela->dimensiune);

    Intrare* nou = (Intrare*)malloc(sizeof(Intrare));
    strcpy(nou->cheie, cheie);
    strcpy(nou->valoare.nume, nume);
    nou->valoare.pret = pret;

    nou->urmator = tabela->bucket[index];
    tabela->bucket[index] = nou;
}



Prajitura* cautare(HashTable* tabela, char* cheie) {
    unsigned int index = functie_hash(cheie, tabela->dimensiune);

    Intrare* temp = tabela->bucket[index];

    while (temp != NULL) {
        if (strcmp(temp->cheie, cheie) == 0) {
            return &temp->valoare;
        }
        temp = temp->urmator;
    }

    return NULL;
}



int main() {
    Nod* lista = NULL;

    adauga_final(&lista, "ecler", 12.5);
    adauga_final(&lista, "amandina", 10.0);
    adauga_final(&lista, "savarina", 9.5);



    printf("Lista prajituri:\n");
    afisare_lista(lista);



    HashTable* tabela = creare_tabela(10);

    inserare(tabela, "p1", "ecler", 12.5);
    inserare(tabela, "p2", "amandina", 10.0);
    inserare(tabela, "p3", "savarina", 9.5);



    Prajitura* gasit = cautare(tabela, "p2");

    if (gasit != NULL) {
        printf("\nGasit: %s - %.2f lei\n", gasit->nume, gasit->pret);
    }
    else {
        printf("\nProdus inexistent\n");
    }



    return 0;
}