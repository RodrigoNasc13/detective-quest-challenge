#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/**
 * Estrutura que representa uma sala (nó) da mansão
 * Cada sala possui um nome, uma pista opcional e dois ponteiros para salas adjacentes
 */
typedef struct Sala {
    char nome[50];         
    char pista[100];       
    struct Sala* esquerda; 
    struct Sala* direita;  
} Sala;

/**
 * Estrutura que representa um nó da árvore BST de pistas
 * Armazena as pistas coletadas de forma ordenada alfabeticamente
 */
typedef struct PistaNode {
    char pista[100];            
    struct PistaNode* esquerda; 
    struct PistaNode* direita;  
} PistaNode;

/**
 * Função: criarSala
 * Objetivo: Criar dinamicamente uma nova sala com nome e pista opcional
 * Parâmetros: 
 *   - nome: string com o nome do cômodo
 *   - pista: string com a pista (ou "" se não houver)
 * Retorno: ponteiro para a nova sala criada
 */
Sala* criarSala(const char* nome, const char* pista) {
    // Aloca memória dinamicamente para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    
    // Copia o nome e a pista para a sala
    strcpy(novaSala->nome, nome);
    strcpy(novaSala->pista, pista);
    
    // Inicializa os ponteiros como NULL (sem caminhos)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * Função: inserirPista
 * Objetivo: Inserir uma pista na árvore BST de forma ordenada
 * Parâmetros:
 *   - raiz: ponteiro para a raiz da árvore de pistas
 *   - pista: string com o conteúdo da pista a ser inserida
 * Retorno: ponteiro para a nova raiz da árvore
 */
PistaNode* inserirPista(PistaNode* raiz, const char* pista) {
    // Caso base: se a árvore está vazia, cria um novo nó
    if (raiz == NULL) {
        PistaNode* novaPista = (PistaNode*)malloc(sizeof(PistaNode));
        
        if (novaPista == NULL) {
            printf("Erro ao alocar memoria para pista!\n");
            exit(1);
        }
        
        strcpy(novaPista->pista, pista);
        novaPista->esquerda = NULL;
        novaPista->direita = NULL;
        
        return novaPista;
    }
    
    // Insere recursivamente na subárvore apropriada
    int comparacao = strcmp(pista, raiz->pista);
    
    if (comparacao < 0) {
        // Pista menor: insere à esquerda
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (comparacao > 0) {
        // Pista maior: insere à direita
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    // Se comparacao == 0, a pista já existe (não inserimos duplicatas)
    
    return raiz;
}

/**
 * Função: exibirPistas
 * Objetivo: Exibir todas as pistas em ordem alfabética (percurso in-order)
 * Parâmetros: raiz - ponteiro para a raiz da árvore de pistas
 * Retorno: void
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Percurso in-order: esquerda -> raiz -> direita
    exibirPistas(raiz->esquerda);
    printf("  * %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

/**
 * Função: explorarSalasComPistas
 * Objetivo: Permitir a navegação interativa pela mansão e coletar pistas
 * Parâmetros:
 *   - salaAtual: ponteiro para a sala onde o jogador está
 *   - pistasColetadas: ponteiro duplo para a árvore BST de pistas
 * Retorno: void
 */
void explorarSalasComPistas(Sala* salaAtual, PistaNode** pistasColetadas) {
    char opcao;
    
    // Continua explorando enquanto houver salas
    while (salaAtual != NULL) {
        // Exibe a sala atual
        printf("\n----------------------------------------\n");
        printf("Voce esta no(a): %s\n", salaAtual->nome);
        printf("----------------------------------------\n");
        
        // Verifica se há pista nesta sala
        if (strlen(salaAtual->pista) > 0) {
            printf("\n[!] PISTA ENCONTRADA: %s\n", salaAtual->pista);
            *pistasColetadas = inserirPista(*pistasColetadas, salaAtual->pista);
            printf("[+] Pista adicionada a colecao!\n");
        } else {
            printf("\n[x] Nenhuma pista encontrada neste comodo.\n");
        }
        
        // Verifica se é um nó-folha (sem caminhos)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\nVoce chegou ao final deste caminho!\n");
            printf("Nao ha mais caminhos a seguir.\n");
            printf("Escolha [S] para sair e ver suas pistas.\n");
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
            printf("\nEncerrando exploracao...\n");
            break;
        } 
        else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    }
}

/**
 * Função: liberarArvore
 * Objetivo: Liberar toda a memória alocada pela árvore de salas
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
 * Função: liberarPistas
 * Objetivo: Liberar toda a memória alocada pela árvore BST de pistas
 * Parâmetros: raiz - ponteiro para a raiz da árvore de pistas
 * Retorno: void
 */
void liberarPistas(PistaNode* raiz) {
    if (raiz == NULL) {
        return;
    }
    
    // Libera recursivamente as subárvores
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    
    // Libera o nó atual
    free(raiz);
}

/**
 * Função: main
 * Objetivo: Montar o mapa da mansão com pistas e iniciar a exploração
 * Retorno: 0 se executado com sucesso
 */
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    printf("----------------------------------------\n");
    printf("   BEM-VINDO AO DETECTIVE QUEST!\n");
    printf("      NIVEL AVENTUREIRO\n");
    printf("----------------------------------------\n");
    printf("Explore a mansão misteriosa, colete\n");
    printf("pistas e descubra o culpado!\n\n");
    
    // Inicializa a árvore BST de pistas coletadas
    PistaNode* pistasColetadas = NULL;
    
    // Criando o mapa da mansão como uma árvore binária com pistas
    // Nível 0 (raiz) - Hall de entrada
    Sala* hall = criarSala("Hall de Entrada", "Pegadas molhadas no chao");
    
    // Nível 1
    hall->esquerda = criarSala("Sala de Estar", "Livro aberto sobre a mesa");
    hall->direita = criarSala("Biblioteca", "Estante com livro faltando");
    
    // Nível 2 - Esquerda do Hall
    hall->esquerda->esquerda = criarSala("Cozinha", "Faca suja na pia");
    hall->esquerda->direita = criarSala("Sala de Jantar", "");
    
    // Nível 2 - Direita do Hall
    hall->direita->esquerda = criarSala("Escritorio", "Carta rasgada na lixeira");
    hall->direita->direita = criarSala("Sala de Musica", "Piano desafinado");
    
    // Nível 3 - Folhas da árvore
    hall->esquerda->esquerda->esquerda = criarSala("Despensa", "");
    hall->esquerda->esquerda->direita = criarSala("Adega", "Garrafa de vinho vazia");
    hall->direita->esquerda->esquerda = criarSala("Cofre Secreto", "Documento confidencial");
    hall->direita->direita->direita = criarSala("Jardim de Inverno", "Flor exotica arrancada");
    
    // Inicia a exploração da mansão com coleta de pistas
    explorarSalasComPistas(hall, &pistasColetadas);
    
    // Exibe todas as pistas coletadas em ordem alfabética
    printf("\n----------------------------------------\n");
    printf("   PISTAS COLETADAS\n");
    printf("----------------------------------------\n");
    
    if (pistasColetadas != NULL) {
        printf("Voce coletou as seguintes pistas:\n\n");
        exibirPistas(pistasColetadas);
        printf("\nAnalise as pistas e descubra o culpado!\n");
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }
    
    // Libera a memória alocada
    liberarArvore(hall);
    liberarPistas(pistasColetadas);
    
    printf("\n----------------------------------------\n");
    printf("Obrigado por jogar Detective Quest!\n");
    printf("----------------------------------------\n");
    
    return 0;
}