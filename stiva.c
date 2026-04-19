#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>

typedef struct Nod Nod;
typedef struct Stiva Stiva;
typedef struct Coada Coada;

struct Nod {
	int valoare;
	Nod* next;
};

struct Stiva {
	Nod* varf;
};

struct Coada {
	Nod* fata;
	Nod* spate;
};



Stiva initStiva() {
	Stiva s;
	s.varf = NULL;
	return s;
}



void inserareInStiva(Stiva* s, int val) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->valoare = val;
	nou->next = s->varf;
	s->varf = nou;
}



int extragereDinStiva(Stiva* s) {
	if (s->varf == NULL) return -1;

	Nod* temp = s->varf;
	int val = temp->valoare;
	s->varf = temp->next;
	free(temp);

	return val;
}



void afisareStiva(Nod* varf) {
	while (varf != NULL) {
		printf("%d ", varf->valoare);
		varf = varf->next;
	}
}



void dezalocareStiva(Stiva* s) {
	while (s->varf != NULL) {
		Nod* temp = s->varf;
		s->varf = s->varf->next;
		free(temp);
	}
}



Coada initCoada() {
	Coada c;
	c.fata = NULL;
	c.spate = NULL;
	return c;
}



void inserareInCoada(Coada* c, int val) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->valoare = val;
	nou->next = NULL;

	if (c->spate == NULL) {
		c->fata = nou;
		c->spate = nou;
	}
	else
	{
		c->spate->next = nou;
		c->spate = nou;
	}
}



int extragereDinCoada(Coada* c) {
	if (c->fata == NULL) return -1;

	Nod* temp = c->fata;
	int val = temp->valoare;
	c->fata = temp->next;

	if (c->fata == NULL) {
		c->spate = NULL;
	}

	free(temp);
	return val;
}



void afisareCoada(Nod* cap) {
	while (cap != NULL) {
		printf("%d ", cap->valoare);
		cap = cap->next;
	}
}



void dezalocareCoada(Coada* c) {
	while (c->fata != NULL) {
		Nod* temp = c->fata;
		c->fata = c->fata->next;
		free(temp);
	}
	c->spate = NULL;
}



int main() {

	Stiva s = initStiva();
	inserareInStiva(&s, 10);
	inserareInStiva(&s, 20);
	inserareInStiva(&s, 30);

	afisareStiva(s.varf);
	printf("\nExtras: %d\n", extragereDinStiva(&s));



	Coada c = initCoada();
	inserareInCoada(&c, 1);
	inserareInCoada(&c, 2);
	inserareInCoada(&c, 3);

	afisareCoada(c.fata);
	printf("\nExtras: %d\n", extragereDinCoada(&c));



	dezalocareStiva(&s);
	dezalocareCoada(&c);

	return 0;
}