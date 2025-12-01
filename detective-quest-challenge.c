#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TAMANHO_HASH 10

/**
 * Estrutura que representa uma sala (nó) da mansão
 * Cada sala possui um nome e dois ponteiros para salas adjacentes
 */
typedef struct Sala {
    char nome[50];         
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
 * Estrutura para um nó da lista encadeada na tabela hash
 * Associa uma pista a um suspeito
 */
typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode* proximo;
} HashNode;

/**
 * Estrutura da tabela hash
 * Armazena associações entre pistas e suspeitos
 */
typedef struct {
    HashNode* tabela[TAMANHO_HASH];
} TabelaHash;

/**
 * Função: funcaoHash
 * Objetivo: Calcular o índice hash para uma string
 * Parâmetros: chave - string a ser hasheada
 * Retorno: índice na tabela hash
 */
int funcaoHash(const char* chave) {
    int hash = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        hash += chave[i];
    }
    return hash % TAMANHO_HASH;
}

/**
 * Função: criarTabelaHash
 * Objetivo: Inicializar uma nova tabela hash vazia
 * Retorno: ponteiro para a tabela hash criada
 */
TabelaHash* criarTabelaHash() {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (tabela == NULL) {
        printf("Erro ao alocar memoria para tabela hash!\n");
        exit(1);
    }
    
    for (int i = 0; i < TAMANHO_HASH; i++) {
        tabela->tabela[i] = NULL;
    }
    
    return tabela;
}

/**
 * Função: inserirNaHash
 * Objetivo: Inserir uma associação pista-suspeito na tabela hash
 * Parâmetros:
 *   - tabela: ponteiro para a tabela hash
 *   - pista: string com a pista
 *   - suspeito: string com o nome do suspeito
 * Retorno: void
 */
void inserirNaHash(TabelaHash* tabela, const char* pista, const char* suspeito) {
    int indice = funcaoHash(pista);
    
    HashNode* novoNo = (HashNode*)malloc(sizeof(HashNode));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para hash node!\n");
        exit(1);
    }
    
    strcpy(novoNo->pista, pista);
    strcpy(novoNo->suspeito, suspeito);
    novoNo->proximo = tabela->tabela[indice];
    tabela->tabela[indice] = novoNo;
}

/**
 * Função: encontrarSuspeito
 * Objetivo: Buscar o suspeito associado a uma pista na tabela hash
 * Parâmetros:
 *   - tabela: ponteiro para a tabela hash
 *   - pista: string com a pista a ser buscada
 * Retorno: string com o nome do suspeito ou NULL se não encontrado
 */
char* encontrarSuspeito(TabelaHash* tabela, const char* pista) {
    int indice = funcaoHash(pista);
    HashNode* atual = tabela->tabela[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->pista, pista) == 0) {
            return atual->suspeito;
        }
        atual = atual->proximo;
    }
    
    return NULL;
}

/**
 * Função: criarSala
 * Objetivo: Criar dinamicamente uma nova sala com nome
 * Parâmetros: nome - string com o nome do cômodo
 * Retorno: ponteiro para a nova sala criada
 */
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }
    
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * Função: obterPistaDaSala
 * Objetivo: Determinar a pista associada a uma sala específica
 * Parâmetros: nomeSala - string com o nome da sala
 * Retorno: string com a pista ou string vazia se não houver
 */
const char* obterPistaDaSala(const char* nomeSala) {
    // Mapeamento fixo de salas para pistas
    if (strcmp(nomeSala, "Hall de Entrada") == 0) {
        return "Pegadas molhadas no chão";
    } else if (strcmp(nomeSala, "Sala de Estar") == 0) {
        return "Livro aberto sobre a mesa";
    } else if (strcmp(nomeSala, "Biblioteca") == 0) {
        return "Estante com livro faltando";
    } else if (strcmp(nomeSala, "Cozinha") == 0) {
        return "Faca suja na pia";
    } else if (strcmp(nomeSala, "Escritório") == 0) {
        return "Carta rasgada na lixeira";
    } else if (strcmp(nomeSala, "Sala de Música") == 0) {
        return "Piano desafinado";
    } else if (strcmp(nomeSala, "Adega") == 0) {
        return "Garrafa de vinho vazia";
    } else if (strcmp(nomeSala, "Cofre Secreto") == 0) {
        return "Documento confidencial";
    } else if (strcmp(nomeSala, "Jardim de Inverno") == 0) {
        return "Flor exotica arrancada";
    }
    
    return "";
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
    
    int comparacao = strcmp(pista, raiz->pista);
    
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, pista);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, pista);
    }
    
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
    
    exibirPistas(raiz->esquerda);
    printf("  * %s\n", raiz->pista);
    exibirPistas(raiz->direita);
}

/**
 * Função: contarPistasPorSuspeito
 * Objetivo: Contar quantas pistas apontam para um determinado suspeito
 * Parâmetros:
 *   - raiz: ponteiro para a raiz da árvore de pistas
 *   - tabela: ponteiro para a tabela hash
 *   - suspeito: nome do suspeito a ser contado
 * Retorno: número de pistas que apontam para o suspeito
 */
int contarPistasPorSuspeito(PistaNode* raiz, TabelaHash* tabela, const char* suspeito) {
    if (raiz == NULL) {
        return 0;
    }
    
    int contador = 0;
    char* suspeitoEncontrado = encontrarSuspeito(tabela, raiz->pista);
    
    if (suspeitoEncontrado != NULL && strcmp(suspeitoEncontrado, suspeito) == 0) {
        contador = 1;
    }
    
    contador += contarPistasPorSuspeito(raiz->esquerda, tabela, suspeito);
    contador += contarPistasPorSuspeito(raiz->direita, tabela, suspeito);
    
    return contador;
}

/**
 * Função: explorarSalas
 * Objetivo: Permitir a navegação interativa pela mansão e coletar pistas
 * Parâmetros:
 *   - salaAtual: ponteiro para a sala onde o jogador está
 *   - pistasColetadas: ponteiro duplo para a árvore BST de pistas
 * Retorno: void
 */
void explorarSalas(Sala* salaAtual, PistaNode** pistasColetadas) {
    char opcao;
    
    while (salaAtual != NULL) {
        printf("\n----------------------------------------\n");
        printf("Voce esta no(a): %s\n", salaAtual->nome);
        printf("----------------------------------------\n");
        
        // Obtém a pista associada à sala
        const char* pista = obterPistaDaSala(salaAtual->nome);
        
        if (strlen(pista) > 0) {
            printf("\n[!] PISTA ENCONTRADA: %s\n", pista);
            *pistasColetadas = inserirPista(*pistasColetadas, pista);
            printf("[+] Pista adicionada à coleção!\n");
        } else {
            printf("\n[x] Nenhuma pista encontrada neste cômodo.\n");
        }
        
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\n-> Você chegou ao final deste caminho!\n");
            printf("-> Escolha [S] para sair e continuar a investigação.\n");
        }
        
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
        
        if (opcao == 'e' || opcao == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda;
            } else {
                printf("\n[!] Nao ha caminho a esquerda!\n");
            }
        } 
        else if (opcao == 'd' || opcao == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita;
            } else {
                printf("\n[!] Nao ha caminho a direita!\n");
            }
        } 
        else if (opcao == 's' || opcao == 'S') {
            printf("\n-> Encerrando exploração...\n");
            break;
        } 
        else {
            printf("\n[!] Opção inválida! Tente novamente.\n");
        }
    }
}

/**
 * Função: verificarSuspeitoFinal
 * Objetivo: Conduzir a fase final de acusação e verificar se há provas suficientes
 * Parâmetros:
 *   - pistasColetadas: ponteiro para a árvore de pistas
 *   - tabela: ponteiro para a tabela hash
 * Retorno: void
 */
void verificarSuspeitoFinal(PistaNode* pistasColetadas, TabelaHash* tabela) {
    char acusado[50];
    
    printf("\n----------------------------------------\n");
    printf("   Fase final: acusação\n");
    printf("----------------------------------------\n");
    printf("\nBaseado nas pistas coletadas, quem é o culpado?\n");
    printf("\nSuspeitos disponíveis:\n");
    printf("  - Mordomo\n");
    printf("  - Cozinheira\n");
    printf("  - Jardineiro\n");
    printf("  - Bibliotecário\n");
    printf("\nDigite o nome do suspeito: ");
    
    scanf(" %[^\n]", acusado);
    
    printf("\n----------------------------------------\n");
    printf("   VERIFICANDO EVIDENCIAS...\n");
    printf("----------------------------------------\n");
    
    int numPistas = contarPistasPorSuspeito(pistasColetadas, tabela, acusado);
    
    printf("\nNumero de pistas que apontam para %s: %d\n", acusado, numPistas);
    
    if (numPistas >= 2) {
        printf("\n*** CASO RESOLVIDO! ***\n");
        printf("Você reuniu evidências suficientes!\n");
        printf("O culpado é realmente: %s\n", acusado);
        printf("\nParabéns, detetive! A justiça foi feita!\n");
    } else {
        printf("\n*** EVIDÊNCIAS INSUFICIENTES ***\n");
        printf("Você não reuniu provas suficientes para acusar %s.\n", acusado);
        printf("São necessárias pelo menos 2 pistas apontando para o suspeito.\n");
        printf("\nO culpado escapou... Tente novamente!\n");
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
    
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
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
    
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}

/**
 * Função: liberarTabelaHash
 * Objetivo: Liberar toda a memória alocada pela tabela hash
 * Parâmetros: tabela - ponteiro para a tabela hash
 * Retorno: void
 */
void liberarTabelaHash(TabelaHash* tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        HashNode* atual = tabela->tabela[i];
        while (atual != NULL) {
            HashNode* temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(tabela);
}

/**
 * Função: main
 * Objetivo: Montar o mapa da mansão, tabela hash de suspeitos e iniciar o jogo
 * Retorno: 0 se executado com sucesso
 */
int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    printf("----------------------------------------\n");
    printf("   Bem-vindo ao detective quest!\n");
    printf("          Nível mestre\n");
    printf("----------------------------------------\n");
    printf("Explore a mansão, colete pistas e\n");
    printf("descubra quem e o culpado!\n\n");
    
    // Inicializa as estruturas de dados
    PistaNode* pistasColetadas = NULL;
    TabelaHash* tabelaSuspeitos = criarTabelaHash();
    
    // Popula a tabela hash com associações pista-suspeito
    inserirNaHash(tabelaSuspeitos, "Pegadas molhadas no chão", "Jardineiro");
    inserirNaHash(tabelaSuspeitos, "Livro aberto sobre a mesa", "Bibliotecário");
    inserirNaHash(tabelaSuspeitos, "Estante com livro faltando", "Bibliotecário");
    inserirNaHash(tabelaSuspeitos, "Faca suja na pia", "Cozinheira");
    inserirNaHash(tabelaSuspeitos, "Carta rasgada na lixeira", "Mordomo");
    inserirNaHash(tabelaSuspeitos, "Piano desafinado", "Mordomo");
    inserirNaHash(tabelaSuspeitos, "Garrafa de vinho vazia", "Cozinheira");
    inserirNaHash(tabelaSuspeitos, "Documento confidencial", "Mordomo");
    inserirNaHash(tabelaSuspeitos, "Flor exotica arrancada", "Jardineiro");
    
    // Cria o mapa da mansão
    Sala* hall = criarSala("Hall de Entrada");
    
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Biblioteca");
    
    hall->esquerda->esquerda = criarSala("Cozinha");
    hall->esquerda->direita = criarSala("Sala de Jantar");
    
    hall->direita->esquerda = criarSala("Escritório");
    hall->direita->direita = criarSala("Sala de Musica");
    
    hall->esquerda->esquerda->esquerda = criarSala("Despensa");
    hall->esquerda->esquerda->direita = criarSala("Adega");
    hall->direita->esquerda->esquerda = criarSala("Cofre Secreto");
    hall->direita->direita->direita = criarSala("Jardim de Inverno");
    
    // Inicia a exploração
    explorarSalas(hall, &pistasColetadas);
    
    // Exibe pistas coletadas
    printf("\n----------------------------------------\n");
    printf("   PISTAS COLETADAS\n");
    printf("----------------------------------------\n");
    
    if (pistasColetadas != NULL) {
        printf("\nVoce coletou as seguintes pistas:\n\n");
        exibirPistas(pistasColetadas);
    } else {
        printf("\nNenhuma pista foi coletada.\n");
    }
    
    // Fase de acusação
    if (pistasColetadas != NULL) {
        verificarSuspeitoFinal(pistasColetadas, tabelaSuspeitos);
    }
    
    // Libera memória
    liberarArvore(hall);
    liberarPistas(pistasColetadas);
    liberarTabelaHash(tabelaSuspeitos);
    
    printf("\n----------------------------------------\n");
    printf("Obrigado por jogar Detective Quest!\n");
    printf("----------------------------------------\n");
    
    return 0;
}