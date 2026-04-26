#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <stdio.h>
#include <stdlib.h>

// --- Estruturas ---

// Mochila Fracionaria
typedef struct {
    int id;
    float valor;
    float peso;
    float ratio;
} Item;

// Selecao de Atividades
typedef struct {
    int id;
    int inicio;
    int fim;
} Atividade;

// Algoritmo de Huffman
typedef struct Node {
    char ch;
    int freq;
    struct Node *esq, *dir;
} Node;

// --- Algoritmos ---

void problema_do_troco(int moedas[], int n, int valor);
void mochila_fracionaria(Item itens[], int n, float capacidade);
void salto_do_sapo(int p[], int n, int delta);
void abastecimento_veiculo(int postos[], int n, int capacidade_tanque);
void selecao_de_atividades(Atividade atividades[], int n);
void algoritmo_huffman(char caracteres[], int frequencias[], int n);

#endif