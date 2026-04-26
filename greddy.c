#include "algoritmos.h"
#include <string.h>

// --- Implementações dos Algoritmos ---

// Problema do Troco
void problema_do_troco(int moedas[], int n, int valor) {
    // Ordena moedas em ordem decrescente (bubble sort simples)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (moedas[j] > moedas[i]) {
                int temp = moedas[i];
                moedas[i] = moedas[j];
                moedas[j] = temp;
            }
        }
    }

    int soma = 0;
    printf("\n>>> Problema do Troco <<<\n");
    printf("Moedas selecionadas: ");
    for (int i = 0; i < n && soma < valor; i++) {
        while (soma + moedas[i] <= valor) {
            soma += moedas[i];
            printf("%d ", moedas[i]);
        }
    }
    if (soma == valor)
        printf("\nTroco completo! Total: %d\n", soma);
    else
        printf("\nNao foi possivel dar o troco exato. Valor alcancado: %d\n", soma);
}

// Mochila Fracionária
int comparar_itens(const void *a, const void *b) {
    float r1 = ((Item *)a)->ratio;
    float r2 = ((Item *)b)->ratio;
    return (r2 > r1) - (r2 < r1);
}

void mochila_fracionaria(Item itens[], int n, float capacidade) {
    // Recalcula o ratio para garantir consistência
    for (int i = 0; i < n; i++) {
        itens[i].ratio = itens[i].valor / itens[i].peso;
    }

    qsort(itens, n, sizeof(Item), comparar_itens);

    float valor_total = 0;
    float W = capacidade;
    printf("\n>>> Mochila Fracionaria <<<\n");
    for (int i = 0; i < n && W > 0; i++) {
        if (itens[i].peso <= W) {
            W -= itens[i].peso;
            valor_total += itens[i].valor;
            printf("Item %d: 100%% (Valor: %.2f)\n", itens[i].id, itens[i].valor);
        } else {
            float fracao = W / itens[i].peso;
            valor_total += itens[i].valor * fracao;
            printf("Item %d: %.2f%% (Valor proporcional: %.2f)\n",
                   itens[i].id, fracao * 100, itens[i].valor * fracao);
            W = 0;
        }
    }
    printf("Valor Total na Mochila: %.2f\n", valor_total);
}

// Salto do Sapo
void salto_do_sapo(int p[], int n, int delta) {
    printf("\n>>> Salto do Sapo <<<\n");

    if (n == 0) {
        printf("Nenhuma pedra disponivel.\n");
        return;
    }

    printf("Caminho: %d ", p[0]);

    int idx_atual = 0; // índice da pedra onde o sapo está

    while (idx_atual < n - 1) {
        // Procura a pedra mais distante dentro do alcance
        int melhor = -1;
        for (int i = idx_atual + 1; i < n; i++) {
            if (p[i] - p[idx_atual] <= delta) {
                melhor = i;
            } else {
                break; // array está ordenado, não adianta continuar
            }
        }

        if (melhor == -1) {
            printf("\nImpossivel completar o percurso! Salto muito grande a partir de %d.\n", p[idx_atual]);
            return;
        }

        idx_atual = melhor;
        printf("-> %d ", p[idx_atual]);
    }

    printf("\nPercurso completo!\n");
}

// Abastecimento de Veículo
void abastecimento_veiculo(int postos[], int n, int capacidade_tanque) {
    printf("\n>>> Abastecimento de Veiculo <<<\n");

    // Verifica se algum trecho consecutivo já é impossível
    for (int i = 1; i < n; i++) {
        if (postos[i] - postos[i - 1] > capacidade_tanque) {
            printf("Impossivel! Trecho entre %d e %d excede a capacidade do tanque.\n",
                   postos[i - 1], postos[i]);
            return;
        }
    }

    printf("Paradas nos postos: ");
    int ultima_parada = 0; // índice do posto onde está atualmente

    for (int i = 1; i < n - 1; i++) {
        // Se do posto atual não consegue chegar ao próximo após i, para em i
        if (postos[i + 1] - postos[ultima_parada] > capacidade_tanque) {
            printf("%d ", postos[i]);
            ultima_parada = i;
        }
    }

    printf("\nDestino final: %d\n", postos[n - 1]);
}

// Seleção de Atividades
int comparar_atividades(const void *a, const void *b) {
    return (((Atividade *)a)->fim - ((Atividade *)b)->fim);
}

void selecao_de_atividades(Atividade atividades[], int n) {
    if (n == 0) {
        printf("\n>>> Selecao de Atividades <<<\n");
        printf("Nenhuma atividade disponivel.\n");
        return;
    }

    qsort(atividades, n, sizeof(Atividade), comparar_atividades);

    printf("\n>>> Selecao de Atividades <<<\n");
    int j = 0;
    printf("Atividades selecionadas: (%d, %d) ", atividades[0].inicio, atividades[0].fim);
    for (int i = 1; i < n; i++) {
        if (atividades[i].inicio >= atividades[j].fim) {
            printf("- (%d, %d) ", atividades[i].inicio, atividades[i].fim);
            j = i;
        }
    }
    printf("\n");
}

// Algoritmo de Huffman
// Cria um novo nó da árvore de Huffman
static Node* novo_node(char ch, int freq) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->ch   = ch;
    n->freq = freq;
    n->esq  = n->dir = NULL;
    return n;
}

// Min-heap manual para os nós de Huffman
typedef struct {
    Node **dados;
    int tamanho;
    int capacidade;
} MinHeap;

static MinHeap* criar_heap(int capacidade) {
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->dados     = (Node **)malloc(capacidade * sizeof(Node *));
    h->tamanho   = 0;
    h->capacidade = capacidade;
    return h;
}

static void trocar_nodes(Node **a, Node **b) {
    Node *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify_baixo(MinHeap *h, int i) {
    int menor = i;
    int esq   = 2 * i + 1;
    int dir   = 2 * i + 2;
    if (esq < h->tamanho && h->dados[esq]->freq < h->dados[menor]->freq)
        menor = esq;
    if (dir < h->tamanho && h->dados[dir]->freq < h->dados[menor]->freq)
        menor = dir;
    if (menor != i) {
        trocar_nodes(&h->dados[i], &h->dados[menor]);
        heapify_baixo(h, menor);
    }
}

static void inserir_heap(MinHeap *h, Node *node) {
    h->dados[h->tamanho++] = node;
    int i = h->tamanho - 1;
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h->dados[pai]->freq > h->dados[i]->freq) {
            trocar_nodes(&h->dados[pai], &h->dados[i]);
            i = pai;
        } else {
            break;
        }
    }
}

static Node* extrair_min(MinHeap *h) {
    Node *min = h->dados[0];
    h->dados[0] = h->dados[--h->tamanho];
    heapify_baixo(h, 0);
    return min;
}

// Imprime os códigos de Huffman percorrendo a árvore
static void imprimir_codigos(Node *raiz, int codigo[], int topo) {
    if (raiz->esq) {
        codigo[topo] = 0;
        imprimir_codigos(raiz->esq, codigo, topo + 1);
    }
    if (raiz->dir) {
        codigo[topo] = 1;
        imprimir_codigos(raiz->dir, codigo, topo + 1);
    }
    // Nó folha: imprime o caractere e seu código
    if (!raiz->esq && !raiz->dir) {
        printf("  '%c' (freq %d): ", raiz->ch, raiz->freq);
        for (int i = 0; i < topo; i++)
            printf("%d", codigo[i]);
        printf("\n");
    }
}

// Libera a memória da árvore recursivamente
static void liberar_arvore(Node *raiz) {
    if (!raiz) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

void algoritmo_huffman(char caracteres[], int frequencias[], int n) {
    printf("\n>>> Algoritmo de Huffman <<<\n");

    if (n == 0) {
        printf("Nenhum caractere fornecido.\n");
        return;
    }

    printf("Frequencias lidas:\n");
    for (int i = 0; i < n; i++)
        printf("  %c: %d\n", caracteres[i], frequencias[i]);

    // Constrói a min-heap com um nó por caractere
    MinHeap *heap = criar_heap(n);
    for (int i = 0; i < n; i++)
        inserir_heap(heap, novo_node(caracteres[i], frequencias[i]));

    // Constrói a árvore de Huffman
    while (heap->tamanho > 1) {
        Node *esq = extrair_min(heap);
        Node *dir = extrair_min(heap);
        Node *pai = novo_node('\0', esq->freq + dir->freq);
        pai->esq  = esq;
        pai->dir  = dir;
        inserir_heap(heap, pai);
    }

    Node *raiz = extrair_min(heap);

    printf("Codigos de Huffman gerados:\n");
    int codigo[256];
    imprimir_codigos(raiz, codigo, 0);

    liberar_arvore(raiz);
    free(heap->dados);
    free(heap);
}