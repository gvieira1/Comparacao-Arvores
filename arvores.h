//-----------funções auxiliares---------------//
#define MAX_LEN 100

typedef struct funcionario {
        int codigo;
        char nome[MAX_LEN];
        int idade;
        char empresa[MAX_LEN];
        char departamento[MAX_LEN];
        float salario;
}Funcionario;

void shellsort(Funcionario *func, int tamanho);

Funcionario* alocarFuncionario(FILE* arquivo, int* tamanho);

void preencheOrdenado(FILE *arquivo, Funcionario *func, int tamanho);

//-----------funções arvore rubro negra---------------//

typedef struct NO *arvLLRB;

arvLLRB *cria_arvLLRB();

void liberar_arvLLRB(arvLLRB *raiz);

int vazia_arvLLRB(arvLLRB *raiz);

int altura_arvLLRB(arvLLRB *raiz);

int totalNO_arvLLRB(arvLLRB *raiz);

void libera_NO(struct NO *no);

void preOrdem_arvLLRB(arvLLRB *raiz);

void emOrdem_arvLLRB(arvLLRB *raiz);

void posOrdem_arvLLRB(arvLLRB *raiz);

int insere_arvLLRB(arvLLRB *raiz, Funcionario valor);

//-----------funções arvore AVL---------------//

typedef struct NOAVL *arvAVL;

arvAVL *cria_arvAVL();

void liberar_arvAVL(arvAVL *raiz);

void libera_NOAVL(struct NOAVL *no);

int vazia_arvAVL(arvAVL *raiz);

int altura_arvAVL(arvAVL *raiz);

int totalNO_arvAVL(arvAVL *raiz);

void preOrdem_arvAVL(arvAVL *raiz);

void emOrdem_arvAVL(arvAVL *raiz);

void posOrdem_arvAVL(arvAVL *raiz);

int insere_arvAVL(arvAVL *raiz, Funcionario valor);

void inserirArvRB(const char *nomeArquivo, arvLLRB* raiz);

void inserirArvAVL(const char *nomeArquivo, arvAVL* raiz);

void testaArvRB(arvLLRB* raiz);

void testaArvAVL(arvAVL* raiz);
