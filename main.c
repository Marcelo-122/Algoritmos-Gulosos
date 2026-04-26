#include "algoritmos.h"
#include <string.h>

int main() {
    int opcao;
    
    printf("Escolha o algoritmo guloso para executar:\n");
    printf("1 - Problema do Troco\n");
    printf("2 - Mochila Fracionaria\n");
    printf("3 - Salto do Sapo\n");
    printf("4 - Abastecimento de Veiculo\n");
    printf("5 - Selecao de Atividades\n");
    printf("6 - Algoritmo de Huffman\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            int moedas[] = {25, 10, 5, 1}; // Ordenadas decrescente
            problema_do_troco(moedas, 4, 63);
            break;
        }
        case 2: {
            Item itens[] = {{1, 60, 10, 6}, {2, 100, 20, 5}, {3, 120, 30, 4}};
            mochila_fracionaria(itens, 3, 50);
            break;
        }
        case 3: {
            int pedras[] = {1, 2, 3, 5, 6, 7};
            salto_do_sapo(pedras, 6, 2);
            break;
        }
        case 4: {
            int postos[] = {0, 100, 250, 400, 550, 700};
            abastecimento_veiculo(postos, 6, 200);
            break;
        }
        case 5: {
            Atividade atividades[] = {{1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7}, {5, 3, 8}, {6, 5, 9}};
            selecao_de_atividades(atividades, 6);
            break;
        }
        case 6: {
            char chars[] = {'a', 'b', 'c', 'd'};
            int freqs[] = {45, 13, 12, 16};
            algoritmo_huffman(chars, freqs, 4);
            break;
        }
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
    }

    return 0;
}