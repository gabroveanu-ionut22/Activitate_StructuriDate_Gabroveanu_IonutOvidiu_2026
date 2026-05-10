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

/* 

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
    while (temp->next)
        temp = temp->next;

    temp->next = nou;
    return cap;
}

void afiseaza_simplu(NodSimplu* cap) {
    NodSimplu* temp = cap;

    while (temp) {
        printf("%d %s %d\n",
               temp->tren.id,
               temp->tren.nume,
               temp->tren.ora);

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

    while (temp->next)
        temp = temp->next;

    temp->next = nou;
    nou->prev = temp;

    return cap;
}

void afiseaza_dublu(NodDublu* cap) {
    NodDublu* temp = cap;

    while (temp) {
        printf("%d %s %d\n",
               temp->tren.id,
               temp->tren.nume,
               temp->tren.ora);

        temp = temp->next;
    }
}
*/


Tren creeaza_tren(int id, const char* nume, int ora) {
    Tren t;
    t.id = id;
    strcpy(t.nume, nume);
    t.ora = ora;
    return t;
}


typedef struct StackNode {
    Tren tren;
    struct StackNode* next;
} StackNode;

void push(StackNode** top, Tren tren) {
    StackNode* nou = (StackNode*)malloc(sizeof(StackNode));

    nou->tren = tren;
    nou->next = *top;

    *top = nou;
}

void pop(StackNode** top) {
    if (*top == NULL) {
        printf("Stack gol!\n");
        return;
    }

    StackNode* temp = *top;

    printf("Scos din stack: %s\n", temp->tren.nume);

    *top = (*top)->next;

    free(temp);
}

void afiseaza_stack(StackNode* top) {
    printf("\nSTACK:\n");

    while (top) {
        printf("%d %s %d\n",
            top->tren.id,
            top->tren.nume,
            top->tren.ora);

        top = top->next;
    }
}

typedef struct QueueNode {
    Tren tren;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void enqueue(Queue* q, Tren tren) {
    QueueNode* nou = (QueueNode*)malloc(sizeof(QueueNode));

    nou->tren = tren;
    nou->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = nou;
        return;
    }

    q->rear->next = nou;
    q->rear = nou;
}

void dequeue(Queue* q) {
    if (q->front == NULL) {
        printf("Queue goala!\n");
        return;
    }

    QueueNode* temp = q->front;

    printf("Scos din queue: %s\n", temp->tren.nume);

    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
}

void afiseaza_queue(Queue* q) {
    printf("\nQUEUE:\n");

    QueueNode* temp = q->front;

    while (temp) {
        printf("%d %s %d\n",
            temp->tren.id,
            temp->tren.nume,
            temp->tren.ora);

        temp = temp->next;
    }
}


int main() {


    StackNode* stack = NULL;

    push(&stack, creeaza_tren(1, "Rapid", 10));
    push(&stack, creeaza_tren(2, "InterCity", 12));
    push(&stack, creeaza_tren(3, "Regio", 14));

    afiseaza_stack(stack);

    pop(&stack);

    afiseaza_stack(stack);

    Queue q;
    q.front = NULL;
    q.rear = NULL;

    enqueue(&q, creeaza_tren(4, "Express", 16));
    enqueue(&q, creeaza_tren(5, "Local", 18));
    enqueue(&q, creeaza_tren(6, "Marfar", 20));

    afiseaza_queue(&q);

    dequeue(&q);

    afiseaza_queue(&q);

    return 0;
}

