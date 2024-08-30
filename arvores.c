#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "arvores.h"

#define MAX_LEN 100
#define RED 1
#define BLACK 0

void shellsort(Funcionario *func, int tamanho) {
    int i, j, intervalo;
    Funcionario auxiliar;

    // Calcula o intervalo inicial
    intervalo = 1;
    while (intervalo < tamanho / 3) {
        intervalo = 3 * intervalo + 1;
    }

    while (intervalo > 0) {
        // Atualiza o valor do intervalo
        for (i = intervalo; i < tamanho; i++) {
            auxiliar = func[i];
            j = i;

            // Efetua comparações entre elementos com distância do intervalo
            while (j >= intervalo && func[j - intervalo].codigo > auxiliar.codigo) {
                func[j] = func[j - intervalo];
                j -= intervalo;
            }
            func[j] = auxiliar;
        }
        intervalo = (intervalo - 1) / 3;
    }
}

Funcionario* alocarFuncionario(FILE *arquivo, int *tamanho){
    //conta a qtd de linhas para a alocação de memória
    char linha[MAX_LEN];
    while(fgets(linha, MAX_LEN, arquivo) != NULL){
        (*tamanho)++;
    }
    rewind(arquivo);
    //aloca memória para a struct funcionário
    Funcionario *func = (Funcionario*) malloc(*tamanho * sizeof(Funcionario));
    if (func == NULL){
        printf("Erro de alocação!\n");
        return NULL;
    }else{
        printf("Memória alocada!\n");
        return func;
    }
}

void preencheOrdenado(FILE *arquivo, Funcionario *func, int tamanho){
    //preenche o arquivo ordenado
    for (int j = 0; j < tamanho; j++) {
        fprintf(arquivo, " %d; %s; %d; %s; %s; %.2f\n",
                func[j].codigo, func[j].nome, func[j].idade, func[j].empresa, func[j].departamento, func[j].salario);
    }
}

// Função para ler dados do CSV e preencher a árvore Rubro-Negra
void inserirArvRB(const char *nomeArquivo, arvLLRB* raiz) {

    struct timeval Tempo_antes, Tempo_depois;
    double deltaT;
    srand(time(NULL));
    printf("\n\n");

    //A partir daqui ele vai contabilizar o tempo
    gettimeofday(&Tempo_antes, NULL);

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro na abertura do arquivo");
        exit(1);
    }

    char linha[MAX_LEN];
    Funcionario func;
    int y = 0;

    while (fgets(linha, MAX_LEN, arquivo) != NULL) {
        func.codigo = atoi(strtok(linha, ";"));
        strcpy(func.nome, strtok(NULL, ";"));
        func.idade = atoi(strtok(NULL, ";"));
        strcpy(func.empresa, strtok(NULL, ";"));
        strcpy(func.departamento, strtok(NULL, ";"));
        func.salario = atof(strtok(NULL, ";"));

        insere_arvLLRB(raiz, func);
        y++;
    }
    gettimeofday(&Tempo_depois, NULL);
    deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec / 1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec / 1000000.0);
    //Aqui ele para de contabilizar o tempo

    printf("Número de nós preenchidos: %d\n", y);
    printf("Tempo para execucao dos comandos: %f segundos \n", deltaT);
    fclose(arquivo);
}

// Função para ler dados do CSV e preencher a árvore AVL
void inserirArvAVL(const char *nomeArquivo, arvAVL* raiz) {

    struct timeval Tempo_antes, Tempo_depois;
    double deltaT;
    srand(time(NULL));
    printf("\n\n");

    //A partir daqui ele vai contabilizar o tempo
    gettimeofday(&Tempo_antes, NULL);

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro na abertura do arquivo");
        exit(1);
    }

    char linha[MAX_LEN];
    Funcionario func;
    int y = 0;

    while (fgets(linha, MAX_LEN, arquivo) != NULL) {
        func.codigo = atoi(strtok(linha, ";"));
        strcpy(func.nome, strtok(NULL, ";"));
        func.idade = atoi(strtok(NULL, ";"));
        strcpy(func.empresa, strtok(NULL, ";"));
        strcpy(func.departamento, strtok(NULL, ";"));
        func.salario = atof(strtok(NULL, ";"));

        insere_arvAVL(raiz, func);
        y++;
    }
    gettimeofday(&Tempo_depois, NULL);
    deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec / 1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec / 1000000.0);
    //Aqui ele para de contabilizar o tempo

    printf("Número de nós preenchidos na AVL: %d\n", y);
    printf("Tempo para execucao dos comandos: %f segundos \n", deltaT);
    fclose(arquivo);
}

void testaArvRB(arvLLRB* raiz){
    int x;
    if(vazia_arvLLRB(raiz)){
        printf("\nA Arvore Rubro Negra está vazia.\n");
    }else{
        printf("\nA Arvore Rubro Negra possui elementos.\n");
    }

    x = altura_arvLLRB(raiz);
    printf("Altura da arvore: %d\n", x);

    x = totalNO_arvLLRB(raiz);
    printf("Total de nos na arvore: %d\n", x);

    liberar_arvLLRB(raiz);
}

void testaArvAVL(arvAVL* raiz){
    int x;
    if(vazia_arvAVL(raiz)){
        printf("\nA Arvore AVL está vazia.\n");
    }else{
        printf("\nA Arvore AVL possui elementos.\n");
    }

    x = altura_arvAVL(raiz);
    printf("Altura da Arvore AVL : %d\n", x);

    x = totalNO_arvAVL(raiz);
    printf("Total de nós na Arvore AVL: %d\n", x);

    liberar_arvAVL(raiz);
}

//-----------funções arvore rubro negra---------------//
struct NO {
    Funcionario info;
    struct NO *esq;
    struct NO *dir;
    int cor;
};

struct NO *rotacionaEsquerda(struct NO *A){
    struct NO *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

struct NO *rotacionaDireita(struct NO *A){
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
}

arvLLRB *cria_arvLLRB(){
    arvLLRB *raiz = (arvLLRB*) malloc(sizeof(arvLLRB));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

void libera_NO(struct NO *no){
    if(no == NULL){
        return;
    }
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void liberar_arvLLRB(arvLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}

int vazia_arvLLRB(arvLLRB *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}

int altura_arvLLRB(arvLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_arvLLRB(&((*raiz)->esq));
    int alt_dir = altura_arvLLRB(&((*raiz)->dir));
    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    }else{
        return(alt_dir + 1);
    }
}

int totalNO_arvLLRB(arvLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = totalNO_arvLLRB(&((*raiz)->esq));
    int alt_dir = totalNO_arvLLRB(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

void preOrdem_arvLLRB(arvLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        printf("%d\n", (*raiz)->info.codigo);
        preOrdem_arvLLRB(&((*raiz)->esq));
        preOrdem_arvLLRB(&((*raiz)->dir));
    }
}

void emOrdem_arvLLRB(arvLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        emOrdem_arvLLRB(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info.codigo);
        emOrdem_arvLLRB(&((*raiz)->dir));
    }
}

void posOrdem_arvLLRB(arvLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        posOrdem_arvLLRB(&((*raiz)->esq));
        posOrdem_arvLLRB(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info.codigo);
    }
}

int cor(struct NO *H){
    if(H == NULL){
        return BLACK;
    }else{
        return H->cor;
    }
}

void trocaCor(struct NO *H){
    H->cor = !H->cor;
    if(H->esq != NULL){
        H->esq->cor = !H->esq->cor;
    }
    if(H->dir != NULL){
        H->dir->cor = !H->dir->cor;
    }
}

struct NO *insereNO(struct NO *H, Funcionario valor, int *resp){
    if(H == NULL){
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }
        novo->info= valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
     };
     if(valor.codigo == H->info.codigo){
        *resp = 0;
     }else{
        if(valor.codigo < H->info.codigo){
            H->esq = insereNO(H->esq, valor, resp);
        }else{
            H->dir = insereNO(H->dir, valor, resp);
        }
     }
     if(cor(H->dir) == RED && cor(H->esq) == BLACK){
        H = rotacionaEsquerda(H);
     }
     if(cor(H->esq) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
     }
     if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
     }
     return H;
};

int insere_arvLLRB(arvLLRB *raiz, Funcionario valor){
    int resp;
    *raiz = insereNO(*raiz, valor, &resp);
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }
    return resp;
}

struct NO *move2EsqRED(struct NO *H){
    trocaCor(H);
    if(cor(H->dir->esq) == RED){
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}

struct NO *move2DirRED(struct NO *H){
    trocaCor(H);
    if(cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

struct NO *balancear(struct NO *H){
    if(cor(H->dir) == RED){
        H = rotacionaEsquerda(H);
    }
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
}

//-----------funções arvore AVL---------------//

struct NOAVL{
    Funcionario info;
    int alt;
    struct NOAVL *esq;
    struct NOAVL *dir;
};

// Calcula altura de um nó
int alt_NOAVL(struct NOAVL *NOAVL){
    if (NOAVL == NULL){
        return -1;
    }else{
        return NOAVL->alt;
    }
}

// Devolve o maior entre dois valores
int maior(int x, int y){
    return (x > y) ? x : y;
}

// Calcula o Fator de balanceamento de um nó
int fatorBalanceamento_NOAVL(struct NOAVL *NOAVL){
    return abs(alt_NOAVL(NOAVL->esq) - alt_NOAVL(NOAVL->dir));
}

void rotacaoLL(arvAVL *A){
    struct NOAVL *B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->alt = maior(alt_NOAVL((*A)->esq), alt_NOAVL((*A)->dir)) + 1;
    B->alt = maior(alt_NOAVL(B->esq), (*A)->alt) + 1;
    *A = B;
}

void rotacaoRR(arvAVL *A){
    struct NOAVL *B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->alt = maior(alt_NOAVL((*A)->esq), alt_NOAVL((*A)->dir)) + 1;
    B->alt = maior(alt_NOAVL(B->dir), (*A)->alt) + 1;
    *A = B;
}

void rotacaoLR(arvAVL *A){
    rotacaoRR(&(*A)->esq);
    rotacaoLL(A);
}

void rotacaoRL(arvAVL *A){
    rotacaoLL(&(*A)->dir);
    rotacaoRR(A);
}

arvAVL *cria_arvAVL(){
    arvAVL *raiz = (arvAVL*) malloc(sizeof(arvAVL));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz;
}

void liberar_arvAVL(arvAVL *raiz){
    if (raiz == NULL)
    {
        return;
    }
    libera_NOAVL(*raiz);
    free(raiz);
}

void libera_NOAVL(struct NOAVL *NOAVL){
    if (NOAVL == NULL)
    {
        return;
    }
    libera_NOAVL(NOAVL->esq);
    libera_NOAVL(NOAVL->dir);
    free(NOAVL);
}

int vazia_arvAVL(arvAVL *raiz){
    return (raiz == NULL || *raiz == NULL);
}

int altura_arvAVL(arvAVL *raiz){
    if (raiz == NULL || *raiz == NULL){
        return 0;
    }
    return alt_NOAVL(*raiz);
}

int totalNO_arvAVL(arvAVL *raiz){
    if (raiz == NULL || *raiz == NULL){
        return 0;
    }
    return totalNO_arvAVL(&((*raiz)->esq)) + totalNO_arvAVL(&((*raiz)->dir)) + 1;
}

void preOrdem_arvAVL(arvAVL *raiz){
    if (raiz == NULL || *raiz == NULL){
        return;
    }
    printf("%d\n", (*raiz)->info.codigo);
    preOrdem_arvAVL(&((*raiz)->esq));
    preOrdem_arvAVL(&((*raiz)->dir));
}

void emOrdem_arvAVL(arvAVL *raiz){
    if (raiz == NULL || *raiz == NULL){
        return;
    }
    emOrdem_arvAVL(&((*raiz)->esq));
    printf("%d\n", (*raiz)->info.codigo);
    emOrdem_arvAVL(&((*raiz)->dir));
}

void posOrdem_arvAVL(arvAVL *raiz){
    if (raiz == NULL || *raiz == NULL){
        return;
    }
    posOrdem_arvAVL(&((*raiz)->esq));
    posOrdem_arvAVL(&((*raiz)->dir));
    printf("%d\n", (*raiz)->info.codigo);
}

int insere_arvAVL(arvAVL *raiz, Funcionario valor){
    int res; // Armazena resposta de sucesso retorno das funções
    if (*raiz == NULL){
        // Árvore vazia ou chegou no nó folha
        struct NOAVL *novo = (struct NOAVL*) malloc(sizeof(struct NOAVL));
        if (novo == NULL){
            return 0;
        }
        novo->info = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NOAVL *atual = *raiz;
    if (valor.codigo < atual->info.codigo){
        if ((res = insere_arvAVL(&(atual->esq), valor)) == 1){
            if (fatorBalanceamento_NOAVL(atual) >= 2){
                if (valor.codigo < (*raiz)->esq->info.codigo){
                    rotacaoLL(raiz);
                }
                else{
                    rotacaoLR(raiz);
                }
            }
        }
    }
    else if (valor.codigo > atual->info.codigo){
        if ((res = insere_arvAVL(&(atual->dir), valor)) == 1){
            if (fatorBalanceamento_NOAVL(atual) >= 2){
                if ((*raiz)->dir->info.codigo < valor.codigo){
                    rotacaoRR(raiz);
                }
                else{
                    rotacaoRL(raiz);
                }
            }
        }
    }
    else{
        printf("Elemento %d já existe. Inserção duplicada!\n", valor.codigo);
        return 0;
    }
    // Atualiza a altura do nó atual
    atual->alt = maior(alt_NOAVL(atual->esq), alt_NOAVL(atual->dir)) + 1;
    return res;
}
