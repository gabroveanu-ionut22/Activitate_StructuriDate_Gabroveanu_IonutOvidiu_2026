#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>

typedef struct Depozit Depozit;

struct Depozit {
	int id;
	float suprafata;
	int volum;
	char* denumire;
	char clasa;
};

struct Nod {
	Depozit info;
	struct Nod* next;
};



struct Depozit initializare(int id, float suprafata, int volum, char* denumire, char clasa) {
	struct Depozit temp;
	temp.id = id;
	temp.suprafata = suprafata;
	temp.volum = volum;
	temp.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
	strcpy(temp.denumire, denumire);
	temp.clasa = clasa;
	return temp;
}
Depozit copiaza(Depozit dep) {
	return initializare(dep.id, dep.suprafata, dep.volum, dep.denumire, dep.clasa);
}

void afisare(struct Depozit d) {
	printf("Depozitul cu id %d are suprafata %5.2f, volumul %d.El se numeste %s si este de clasa %c \n",
		d.id, d.suprafata, d.volum, d.denumire, d.clasa);
};

void afisareVector(struct Depozit* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

struct Depozit* copiazaPrimeleNElemente(struct Depozit* vector, int nrElemente, int nrElementeCopiate) {
	if (nrElementeCopiate < nrElemente) {
		struct Depozit* vectorNou = malloc(sizeof(Depozit)*nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++) {
			vectorNou[i] = copiaza(vector[i]);
		}
		return vectorNou;
	}
	else return NULL;
}
void dezalocare(struct Depozit** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].denumire);
	}
	free(*vector);
	*nrElemente = 0;
	*vector = NULL;
}

int main() {
	int nrElemente = 3;
	Depozit* vector = malloc(sizeof(Depozit) * nrElemente);
	vector[0] = initializare(1, 32.6, 400, "Alfa", 'b');
	vector[1] = initializare(2, 20.1, 200, "Beta", 'b');
	vector[2] = initializare(3, 33.2, 330, "Gamma", 'c');

	printf("Vector initial\n");
	afisareVector(vector, 3);

	Depozit copie = copiaza(vector[0]);
	afisare(copie);

	//Testam primele elemente
	int nrCopiate = 2;
	Depozit* vectorNou = copiazaPrimeleNElemente(vector, nrElemente, nrCopiate);
	afisareVector(vectorNou, nrCopiate);

	dezalocare(&vectorNou, nrCopiate);
	dezalocare(&vector, &nrElemente);










	return 0;
}