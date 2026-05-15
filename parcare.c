#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char numar[20];
    int prioritate;
} Masina;

typedef struct {
    Masina* locuri;
    int dimensiune;
    int capacitate;
} HeapParcare;


HeapParcare* creeazaParcare(int cap) {

    HeapParcare* parcare = malloc(sizeof(HeapParcare));

    parcare->locuri = malloc(sizeof(Masina) * cap);
    parcare->dimensiune = 0;
    parcare->capacitate = cap;

    return parcare;
}

void schimbaMasini(Masina* a, Masina* b) {

    Masina aux = *a;
    *a = *b;
    *b = aux;
}

void urcaMasina(HeapParcare* parcare, int poz) {

    while (poz > 0) {

        int tata = (poz - 1) / 2;

        if (parcare->locuri[tata].prioritate <=
            parcare->locuri[poz].prioritate)
            break;

        schimbaMasini(
            &parcare->locuri[tata],
            &parcare->locuri[poz]
        );

        poz = tata;
    }
}


void coboaraMasina(HeapParcare* parcare, int poz) {

    while (1) {

        int stanga = 2 * poz + 1;
        int dreapta = 2 * poz + 2;
        int mic = poz;

        if (stanga < parcare->dimensiune &&
            parcare->locuri[stanga].prioritate <
            parcare->locuri[mic].prioritate) {

            mic = stanga;
        }

        if (dreapta < parcare->dimensiune &&
            parcare->locuri[dreapta].prioritate <
            parcare->locuri[mic].prioritate) {

            mic = dreapta;
        }

        if (mic == poz)
            break;

        schimbaMasini(
            &parcare->locuri[poz],
            &parcare->locuri[mic]
        );

        poz = mic;
    }
}



void adaugaMasina(
    HeapParcare* parcare,
    char numar[],
    int prioritate
) {

    if (parcare->dimensiune >= parcare->capacitate) {

        parcare->capacitate *= 2;

        parcare->locuri = realloc(
            parcare->locuri,
            sizeof(Masina) * parcare->capacitate
        );
    }

    strcpy(
        parcare->locuri[parcare->dimensiune].numar,
        numar
    );

    parcare->locuri[parcare->dimensiune].prioritate =
        prioritate;

    urcaMasina(parcare, parcare->dimensiune);

    parcare->dimensiune++;
}

Masina scoateUrgenta(HeapParcare* parcare) {

    Masina gol = { "NIMIC", -1 };

    if (parcare->dimensiune == 0)
        return gol;

    Masina urgent = parcare->locuri[0];

    parcare->dimensiune--;

    parcare->locuri[0] =
        parcare->locuri[parcare->dimensiune];

    coboaraMasina(parcare, 0);

    return urgent;
}


void afiseazaParcare(HeapParcare* parcare) {

    printf("\nMasini in parcare:\n");

    for (int i = 0; i < parcare->dimensiune; i++) {

        printf(
            "%s -> prioritate %d\n",
            parcare->locuri[i].numar,
            parcare->locuri[i].prioritate
        );
    }
}


int main() {

    HeapParcare* parcare = creeazaParcare(4);

    adaugaMasina(parcare, "B123XYZ", 5);
    adaugaMasina(parcare, "CJ99AAA", 2);

    adaugaMasina(parcare, "IF10BBB", 8);
    adaugaMasina(parcare, "TM77PPP", 1);

    afiseazaParcare(parcare);

    Masina iesire = scoateUrgenta(parcare);

    printf(
        "\nMasina scoasa prima: %s cu prioritate %d\n",
        iesire.numar,
        iesire.prioritate
    );

    afiseazaParcare(parcare);

    free(parcare->locuri);
    free(parcare);

    return 0;
}
