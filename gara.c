#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRENURI 100

typedef struct {
    int id;
    char nume[50];
    int ora;
} Tren;

typedef struct NodSimplu {
    Tren tren;
    struct NodSimplu* next;
} NodSimplu;

typedef struct NodDublu {
    Tren tren;
    struct NodDublu* next;
    struct NodDublu* prev;
} NodDublu;
Tren gara[MAX_TRENURI];
int numar_trenuri = 0;
void adauga_tren_array(int id, const char* nume, int ora) {
    if (numar_trenuri >= MAX_TRENURI) return;
    gara[numar_trenuri].id = id;
    strcpy(gara[numar_trenuri].nume, nume);
    gara[numar_trenuri].ora = ora;
    numar_trenuri++;
}
void afiseaza_array() {
    for (int i = 0; i < numar_trenuri; i++) {
        printf("%d %s %d\n", gara[i].id, gara[i].nume, gara[i].ora);
    }
}
NodSimplu* adauga_simplu(NodSimplu* cap, Tren tren) {
    NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
    nou->tren = tren;
    nou->next = NULL;
    if (!cap) return nou;
    NodSimplu* temp = cap;
    while (temp->next) temp = temp->next;
    temp->next = nou;
    return cap;
}

void afiseaza_simplu(NodSimplu* cap) {
    NodSimplu* temp = cap;
    while (temp) {
        printf("%d %s %d\n", temp->tren.id, temp->tren.nume, temp->tren.ora);
        temp = temp->next;
    }
}

NodDublu* adauga_dublu(NodDublu* cap, Tren tren) {
    NodDublu* nou = (NodDublu*)malloc(sizeof(NodDublu));
    nou->tren = tren;
    nou->next = NULL;
    nou->prev = NULL;
    if (!cap) return nou;
    NodDublu* temp = cap;
    while (temp->next) temp = temp->next;
    temp->next = nou;
    nou->prev = temp;
    return cap;
}
void afiseaza_dublu(NodDublu* cap) {
    NodDublu* temp = cap;
    while (temp) {
        printf("%d %s %d\n", temp->tren.id, temp->tren.nume, temp->tren.ora);
        temp = temp->next;
    }
}

Tren creeaza_tren(int id, const char* nume, int ora) {
    Tren t;
    t.id = id;
    strcpy(t.nume, nume);
    t.ora = ora;
    return t;
}

int main() {
    adauga_tren_array(1, "Rapid", 10);
    adauga_tren_array(2, "InterCity", 12);
    afiseaza_array();

    NodSimplu* lista_simpla = NULL;
    lista_simpla = adauga_simplu(lista_simpla, creeaza_tren(3, "Regio", 14));
    lista_simpla = adauga_simplu(lista_simpla, creeaza_tren(4, "Marfar", 16));

    afiseaza_simplu(lista_simpla);
    NodDublu* lista_dubla = NULL;
    lista_dubla = adauga_dublu(lista_dubla, creeaza_tren(5, "Express", 18));
    lista_dubla = adauga_dublu(lista_dubla, creeaza_tren(6, "Local", 20));

    afiseaza_dublu(lista_dubla);

    return 0;
}