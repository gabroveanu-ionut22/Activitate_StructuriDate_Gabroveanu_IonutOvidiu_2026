#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct StructuraCarte {
	int cod;
	int nrPagini;
	float pret;
	char* titlu;
	char* autor;
	unsigned char categorie;
};
typedef struct StructuraCarte Carte;
struct Nod {
	Carte info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;
Carte initializareCarte(int cod, int nrPagini, float pret,
	const char* titlu, const char* autor,
	unsigned char categorie) {

	Carte c;
	c.cod = cod;
	c.nrPagini = nrPagini;
	c.pret = pret;
	c.categorie = categorie;

	c.titlu = (char*)malloc(sizeof(char) * (strlen(titlu) + 1));
	strcpy(c.titlu, titlu);

	c.autor = (char*)malloc(sizeof(char) * (strlen(autor) + 1));
	strcpy(c.autor, autor);

	return c;
}
void afisareCarte(Carte c) {
	printf("Cod: %d\n", c.cod);
	printf("Nr pagini: %d\n", c.nrPagini);
	printf("Pret: %.2f\n", c.pret);
	printf("Titlu: %s\n", c.titlu);
	printf("Autor: %s\n", c.autor);
	printf("Categorie: %c\n\n", c.categorie);
}
int maxim(int a, int b) {
	return a > b ? a : b;
}
int calculeazaInaltime(Nod* rad) {
	if (rad) {
		return 1 + maxim(calculeazaInaltime(rad->st),
			calculeazaInaltime(rad->dr));
	}
	return 0;
}

int calculeazaGradEchilibru(Nod* rad) {
	if (rad) {
		return calculeazaInaltime(rad->st)
			- calculeazaInaltime(rad->dr);
	}
	return 0;
}

void rotireDreapta(Nod** rad) {
	Nod* aux = (*rad)->st;
	(*rad)->st = aux->dr;
	aux->dr = (*rad);
	(*rad) = aux;
}
void rotireStanga(Nod** rad) {
	Nod* aux = (*rad)->dr;
	(*rad)->dr = aux->st;
	aux->st = (*rad);
	(*rad) = aux;
}
void inserareCarteInAVL(Nod** rad, Carte carteNoua) {
	if ((*rad) == NULL) {
		Nod* nodNou = (Nod*)malloc(sizeof(Nod));
		nodNou->info = carteNoua;
		nodNou->st = NULL;
		nodNou->dr = NULL;

		(*rad) = nodNou;
	}
	else {

		if (carteNoua.cod < (*rad)->info.cod) {
			inserareCarteInAVL(&((*rad)->st), carteNoua);
		}

		if (carteNoua.cod > (*rad)->info.cod) {
			inserareCarteInAVL(&((*rad)->dr), carteNoua);
		}
	}
	int gradEchilibru = calculeazaGradEchilibru((*rad));

	if (gradEchilibru == 2) {

		if (calculeazaGradEchilibru((*rad)->st) == -1) {
			rotireStanga(&((*rad)->st));
		}

		rotireDreapta(rad);
	}
	if (gradEchilibru == -2) {

		if (calculeazaGradEchilibru((*rad)->dr) == 1) {
			rotireDreapta(&((*rad)->dr));
		}

		rotireStanga(rad);
	}
}
void afisareInordine(Nod* rad) {
	if (rad) {
		afisareInordine(rad->st);
		afisareCarte(rad->info);
		afisareInordine(rad->dr);
	}
}
void afisarePreordine(Nod* rad) {
	if (rad) {

		afisareCarte(rad->info);

		afisarePreordine(rad->st);

		afisarePreordine(rad->dr);
	}
}
Carte cautaCarteDupaCod(Nod* rad, int cod) {
	Carte c;
	c.cod = -1;
	if (rad) {

		if (rad->info.cod == cod) {
			c = rad->info;
			c.titlu = (char*)malloc(sizeof(char) *
				(strlen(rad->info.titlu) + 1));
			strcpy(c.titlu, rad->info.titlu);
			c.autor = (char*)malloc(sizeof(char) *
				(strlen(rad->info.autor) + 1));
			strcpy(c.autor, rad->info.autor);
		}
		if (cod < rad->info.cod) {
			c = cautaCarteDupaCod(rad->st, cod);
		}
		if (cod > rad->info.cod) {
			c = cautaCarteDupaCod(rad->dr, cod);
		}
	}
	return c;
}

int determinaNumarNoduri(Nod* rad) {
	if (rad) {

		return determinaNumarNoduri(rad->st)
			+ determinaNumarNoduri(rad->dr)
			+ 1;
	}
	return 0;
}

float calculeazaPretTotalCarti(Nod* rad) {
	if (rad) {

		return rad->info.pret
			+ calculeazaPretTotalCarti(rad->st)
			+ calculeazaPretTotalCarti(rad->dr);
	}
	return 0;
}

float calculeazaPretCartiAutor(Nod* rad,
	const char* autor) {
	if (rad) {
		float suma = calculeazaPretCartiAutor(rad->st, autor)
			+ calculeazaPretCartiAutor(rad->dr, autor);

		if (strcmp(rad->info.autor, autor) == 0) {
			suma += rad->info.pret;
		}
		return suma;
	}

	return 0;
}

void dezalocareAVL(Nod** rad) {

	if ((*rad)) {

		dezalocareAVL(&((*rad)->st));

		dezalocareAVL(&((*rad)->dr));

		free((*rad)->info.titlu);

		free((*rad)->info.autor);

		free((*rad));

		(*rad) = NULL;
	}
}

int main() {

	Nod* rad = NULL;
	inserareCarteInAVL(&rad,
		initializareCarte(50, 300, 45.5,
			"Morometii", "Preda", 'R'));

	inserareCarteInAVL(&rad,
		initializareCarte(20, 250, 39.9,
			"Baltagul", "Sadoveanu", 'D'));

	inserareCarteInAVL(&rad,
		initializareCarte(70, 500, 70,
			"Ion", "Rebreanu", 'C'));

	inserareCarteInAVL(&rad,
		initializareCarte(10, 150, 29.5,
			"Enigma", "Calinescu", 'T'));

	inserareCarteInAVL(&rad,
		initializareCarte(90, 410, 66.6,
			"Ultima", "Petrescu", 'I'));

	printf("Afisare preordine:\n\n");

	afisarePreordine(rad);

	printf("Carte cautata:\n\n");

	Carte c = cautaCarteDupaCod(rad, 70);

	afisareCarte(c);

	free(c.titlu);
	free(c.autor);

	printf("Numar noduri: %d\n",
		determinaNumarNoduri(rad));

	printf("Inaltime arbore: %d\n",
		calculeazaInaltime(rad));
	printf("Pret total carti: %.2f\n",
		calculeazaPretTotalCarti(rad));

	printf("Pret carti autor Preda: %.2f\n",
		calculeazaPretCartiAutor(rad, "Preda"));


	dezalocareAVL(&rad);
	








	return 0;
}
