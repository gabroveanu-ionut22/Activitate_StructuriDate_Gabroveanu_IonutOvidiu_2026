#define _CRT_SECURE_NO_WARNINGS
#include<malloc.h>
#include<stdio.h>
#include<string.h>

typedef struct NodHotel NodHotel;
typedef struct NodVecin NodVecin;
typedef struct Hotel Hotel;

typedef struct Nod Nod;
typedef struct Stiva Stiva;

struct Nod {
    int id;
    Nod* next;
    Nod* prev;
};

struct Stiva {
    Nod* prim;
    Nod* ultim;
};

struct Hotel {
    int id;
    char* denumire;
    int camereDisponibile;
};

struct NodHotel {
    Hotel info;
    NodHotel* next;
    NodVecin* vecini;
};

struct NodVecin {
    NodHotel* info;
    NodVecin* next;
};


void push(Stiva* s, int id) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->id = id;
    nou->next = s->prim;
    nou->prev = NULL;

    if (s->prim == NULL) {
        s->prim = s->ultim = nou;
    }
    else {
        s->prim->prev = nou;
        s->prim = nou;
    }
}


int pop(Stiva* s) {
    int id = -1;
    if (s->prim) {
        id = s->prim->id;
        Nod* aux = s->prim;
        s->prim = s->prim->next;
        if (s->prim == NULL) s->ultim = NULL;
        free(aux);
    }
    return id;
}


Hotel initHotel(int id, const char* denumire, int camere) {
    Hotel h;
    h.id = id;
    h.denumire = (char*)malloc(strlen(denumire) + 1);
    strcpy(h.denumire, denumire);
    h.camereDisponibile = camere;
    return h;
}


void insertHotel(NodHotel** cap, Hotel h) {
    NodHotel* nou = (NodHotel*)malloc(sizeof(NodHotel));
    nou->info = h;
    nou->next = NULL;
    nou->vecini = NULL;

    if (*cap) {
        NodHotel* aux = *cap;
        while (aux->next) aux = aux->next;
        aux->next = nou;
    }
    else {
        *cap = nou;
    }
}


void insertVecin(NodVecin** cap, NodHotel* info) {
    NodVecin* nou = (NodVecin*)malloc(sizeof(NodVecin));
    nou->info = info;
    nou->next = NULL;

    if (*cap) {
        NodVecin* aux = *cap;
        while (aux->next) aux = aux->next;
        aux->next = nou;
    }
    else {
        *cap = nou;
    }
}


NodHotel* cautareHotel(NodHotel* graf, int id) {
    while (graf && graf->info.id != id) graf = graf->next;
    return graf;
}


void adaugareRelatie(NodHotel* graf, int id1, int id2) {
    NodHotel* h1 = cautareHotel(graf, id1);
    NodHotel* h2 = cautareHotel(graf, id2);

    if (h1 && h2) {
        insertVecin(&h1->vecini, h2);
        insertVecin(&h2->vecini, h1);
    }
}


void afisareHotel(Hotel h) {
    printf("\n%d. Hotel %s are %d camere", h.id, h.denumire, h.camereDisponibile);
}


void afisareGraf(NodHotel* graf) {
    while (graf) {
        afisareHotel(graf->info);
        printf("\n vecini:");
        NodVecin* v = graf->vecini;
        while (v) {
            afisareHotel(v->info->info);
            v = v->next;
        }
        printf("\n");
        graf = graf->next;
    }
}


void DFS(NodHotel* graf, int start) {
    int* viz = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) viz[i] = 0;

    Stiva s;
    s.prim = s.ultim = NULL;

    push(&s, start);
    viz[start - 1] = 1;

    while (s.prim) {
        int id = pop(&s);
        NodHotel* curent = cautareHotel(graf, id);

        afisareHotel(curent->info);

        NodVecin* v = curent->vecini;
        while (v) {
            int nid = v->info->info.id;
            if (viz[nid - 1] == 0) {
                push(&s, nid);
                viz[nid - 1] = 1;
            }
            v = v->next;
        }
    }

    free(viz);
}


void main() {
    NodHotel* graf = NULL;


    insertHotel(&graf, initHotel(1, "Continental", 20));
    insertHotel(&graf, initHotel(2, "Ibis", 15));
    insertHotel(&graf, initHotel(3, "Radisson", 30));
    insertHotel(&graf, initHotel(4, "Marriott", 25));
    insertHotel(&graf, initHotel(5, "Hilton", 18));
    insertHotel(&graf, initHotel(6, "Novotel", 22));


    adaugareRelatie(graf, 1, 2);
    adaugareRelatie(graf, 1, 3);
    adaugareRelatie(graf, 2, 4);
    adaugareRelatie(graf, 3, 5);
    adaugareRelatie(graf, 4, 6);
    adaugareRelatie(graf, 5, 6);


    afisareGraf(graf);

    printf("\n DFS:");
    DFS(graf, 1);
}

