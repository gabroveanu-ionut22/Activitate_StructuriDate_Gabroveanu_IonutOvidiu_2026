#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodStiva {
    char combustibil[50];
    struct NodStiva* urmator;
} NodStiva;

NodStiva* push(NodStiva* varf, char* combustibil) {
    NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
    strcpy(nou->combustibil, combustibil);
    nou->urmator = varf;
    return nou;
}

NodStiva* pop(NodStiva* varf) {
    if (!varf) return NULL;
    NodStiva* temp = varf;
    varf = varf->urmator;
    free(temp);
    return varf;
}



typedef struct NodCoada {
    char masina[50];
    struct NodCoada* urmator;
} NodCoada;

typedef struct {
    NodCoada* fata;
    NodCoada* spate;
} Coada;

void initCoada(Coada* c) {
    c->fata = c->spate = NULL;
}

void enqueue(Coada* c, char* masina) {
    NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
    strcpy(nou->masina, masina);
    nou->urmator = NULL;
    if (!c->spate) {
        c->fata = c->spate = nou;
        return;
    }
    c->spate->urmator = nou;
    c->spate = nou;
}

void dequeue(Coada* c) {
    if (!c->fata) return;
    NodCoada* temp = c->fata;
    c->fata = c->fata->urmator;
    if (!c->fata) c->spate = NULL;
    free(temp);
}



#define DIM 10

typedef struct Intrare {
    char cheie[50];
    int cantitate;
    struct Intrare* urmator;
} Intrare;

Intrare* tabela[DIM];

int hash(char* cheie) {
    int suma = 0;
    for (int i = 0; cheie[i]; i++) suma += cheie[i];
    return suma % DIM;
}

void inserare(char* cheie, int cantitate) {
    int idx = hash(cheie);
    Intrare* nou = (Intrare*)malloc(sizeof(Intrare));
    strcpy(nou->cheie, cheie);
    nou->cantitate = cantitate;
    nou->urmator = tabela[idx];
    tabela[idx] = nou;
}

int cauta(char* cheie) {
    int idx = hash(cheie);
    Intrare* curent = tabela[idx];
    while (curent) {
        if (strcmp(curent->cheie, cheie) == 0)
            return curent->cantitate;
        curent = curent->urmator;
    }
    return -1;
}



typedef struct {
    int volum[100];
    int dimensiune;
} Heap;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void urcaHeap(Heap* h, int idx) {
    while (idx > 0) {
        int parinte = (idx - 1) / 2;
        if (h->volum[parinte] < h->volum[idx]) {
            swap(&h->volum[parinte], &h->volum[idx]);
            idx = parinte;
        }
        else break;
    }
}

void coboaraHeap(Heap* h, int idx) {
    int stanga = 2 * idx + 1;
    int dreapta = 2 * idx + 2;
    int mare = idx;

    if (stanga < h->dimensiune && h->volum[stanga] > h->volum[mare])
        mare = stanga;

    if (dreapta < h->dimensiune && h->volum[dreapta] > h->volum[mare])
        mare = dreapta;

    if (mare != idx) {
        swap(&h->volum[idx], &h->volum[mare]);
        coboaraHeap(h, mare);
    }
}

void inserareHeap(Heap* h, int valoare) {
    h->volum[h->dimensiune] = valoare;
    urcaHeap(h, h->dimensiune);
    h->dimensiune++;
}

int extrageMax(Heap* h) {
    if (h->dimensiune <= 0) return -1;
    int radacina = h->volum[0];
    h->volum[0] = h->volum[h->dimensiune - 1];
    h->dimensiune--;
    coboaraHeap(h, 0);
    return radacina;
}