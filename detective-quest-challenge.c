#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/**
 * Estrutura que representa uma sala (nó) da mansão
 * Cada sala possui um nome e dois ponteiros para salas adjacentes
 */
typedef struct Sala {
    char nome[50];           // Nome do cômodo
    struct Sala* esquerda;   // Caminho à esquerda
    struct Sala* direita;    // Caminho à direita
} Sala;

/**
 * Função: criarSala
 * Objetivo: Criar dinamicamente uma nova sala com o nome especificado
 * Parâmetros: nome - string com o nome do cômodo
 * Retorno: ponteiro para a nova sala criada
 */
Sala* criarSala(const char* nome) {
    // Aloca memória dinamicamente para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    
    // Copia o nome para a sala
    strcpy(novaSala->nome, nome);
    
    // Inicializa os ponteiros como NULL (sem caminhos)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * Função: explorarSalas
 * Objetivo: Permitir a navegação interativa do jogador pela mansão
 * Parâmetros: salaAtual - ponteiro para a sala onde o jogador está
 * Retorno: void
 */
void explorarSalas(Sala* salaAtual) {
    char opcao;
    
    // Continua explorando enquanto houver salas
    while (salaAtual != NULL) {
        // Exibe a sala atual
        printf("\n----------------------------------------\n");
        printf("Voce esta no(a): %s\n", salaAtual->nome);
        printf("----------------------------------------\n");
        
        // Verifica se é um nó-folha (sem caminhos)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\nVoce chegou ao final da exploracao!\n");
            printf("Nao ha mais caminhos a seguir.\n");
            break;
        }
        
        // Exibe as opções disponíveis
        printf("\nEscolha seu caminho:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  [E] - Ir para esquerda\n");
        }
        if (salaAtual->direita != NULL) {
            printf("  [D] - Ir para direita\n");
        }
        printf("  [S] - Sair da exploracao\n");
        printf("\nOpcao: ");
        
        scanf(" %c", &opcao);
        
        // Processa a escolha do jogador
        if (opcao == 'e' || opcao == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda;
            } else {
                printf("\nNao ha caminho a esquerda!\n");
            }
        } 
        else if (opcao == 'd' || opcao == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita;
            } else {
                printf("\nNao ha caminho a direita!\n");
            }
        } 
        else if (opcao == 's' || opcao == 'S') {
            printf("\nSaindo da exploracao...\n");
            break;
        } 
        else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    }
}

/**
 * Função: liberarArvore
 * Objetivo: Liberar toda a memória alocada pela árvore
 * Parâmetros: raiz - ponteiro para a raiz da árvore
 * Retorno: void
 */
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Libera recursivamente as subárvores
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    
    // Libera o nó atual
    free(raiz);
}

/**
 * Função: main
 * Objetivo: Montar o mapa da mansão e iniciar a exploração
 * Retorno: 0 se executado com sucesso
 */
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    printf("----------------------------------------\n");
    printf("   BEM-VINDO AO DETECTIVE QUEST!\n");
    printf("----------------------------------------\n");
    printf("Explore a mansão misteriosa e encontre\n");
    printf("pistas sobre o culpado!\n\n");
    
    // Criando o mapa da mansão como uma árvore binária
    // Nível 0 (raiz) - Hall de entrada
    Sala* hall = criarSala("Hall de Entrada");
    
    // Nível 1
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Biblioteca");
    
    // Nível 2 - Esquerda do Hall
    hall->esquerda->esquerda = criarSala("Cozinha");
    hall->esquerda->direita = criarSala("Sala de Jantar");
    
    // Nível 2 - Direita do Hall
    hall->direita->esquerda = criarSala("Escritorio");
    hall->direita->direita = criarSala("Sala de Musica");
    
    // Nível 3 - Folhas da árvore
    hall->esquerda->esquerda->esquerda = criarSala("Despensa");
    hall->esquerda->esquerda->direita = criarSala("Adega");
    hall->direita->esquerda->esquerda = criarSala("Cofre Secreto");
    hall->direita->direita->direita = criarSala("Jardim de Inverno");
    
    // Inicia a exploração da mansão
    explorarSalas(hall);
    
    // Libera a memória alocada
    liberarArvore(hall);
    
    printf("\n----------------------------------------\n");
    printf("Obrigado por jogar Detective Quest!\n");
    printf("----------------------------------------\n");
    
    return 0;
}