#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>
#include "arvores.h"
#define MAX_LEN 100

int main() {

    int i = 0, tamanho = 0, CTRLmenu = 1;
    char linha[MAX_LEN];

    //abre o arquivo desordenado
    FILE *planilha;
    planilha = fopen("massaDados.csv", "r");
    if (planilha == NULL) {
        printf("Erro na abertura!\n");
        system("pause");
        exit(1);
    }

    //aloca mem�ria para a struct funcion�rio
    Funcionario *func = alocarFuncionario(planilha, &tamanho);
    if (func == NULL) {
        fclose(planilha);
        return 1;
    }

    //percorre o arquivo inserindo as informa��es na struct
    while (fgets(linha, MAX_LEN, planilha) != NULL) {
        func[i].codigo = atoi(strtok(linha, ";"));
        strcpy(func[i].nome, strtok(NULL, ";"));
        func[i].idade = atoi(strtok(NULL, ";"));
        strcpy(func[i].empresa, strtok(NULL, ";"));
        strcpy(func[i].departamento, strtok(NULL, ";"));
        func[i].salario = atof(strtok(NULL, ";"));
        i++;
    }
    printf("n�mero de structs preenchidas: %d\n", i);
    fclose(planilha);

    //ordena os dados com o shellsort
    shellsort(func, tamanho);

    //cria novo arquivo para receber os dados ordenados
    FILE *planilhaOrdenada;
    planilhaOrdenada = fopen("massaDadosOrdenada.csv", "w");
    if (planilhaOrdenada == NULL) {
        printf("Erro na abertura do segundo arquivo!\n");
        system("pause");
        exit(1);
    }

    //preenche o arquivo novo com os dados ordenados
    preencheOrdenado(planilhaOrdenada, func, tamanho);
    //habilita a acentua��o para o menu sem alterar o float do preenchimento da planilha
    setlocale(LC_ALL, "portuguese");
    fclose(planilhaOrdenada);
    free(func);

    arvAVL *ponto;
    arvLLRB *raiz;

    while(CTRLmenu != 0){
        system("cls");
        printf("\tEscolha a �rvore que deseja preencheer: \n\n");
        printf("\t1 - �rvore AVL com dados ordenados\n\t2 - �rvore AVL com dados desordenados\n\t3 - �rvore Rubro-Negra com dados ordenados\n\t4 - �rvore Rubro-Negra com dados desordenados\n\t0 - Sair\n");

        scanf("%d", &CTRLmenu);
        system("cls");

        switch (CTRLmenu){
            case 1:
                printf("\t�rvore AVL com dados ordenados");
                ponto = cria_arvAVL();
                inserirArvAVL("massaDadosOrdenada.csv", ponto);
                testaArvAVL(ponto);
                printf("\nDigite qualquer tecla para voltar: ");
                getchar();
                getchar();
                break;

            case 2:
                printf("\t�rvore AVL com dados desordenados");
                ponto = cria_arvAVL();
                inserirArvAVL("massaDados.csv", ponto);
                testaArvAVL(ponto);
                printf("\nDigite qualquer tecla para voltar: ");
                getchar();
                getchar();
                break;

            case 3:
                printf("\t�rvore Rubro-Negra com dados ordenados");
                raiz = cria_arvLLRB();
                inserirArvRB("massaDadosOrdenada.csv", raiz);
                testaArvRB(raiz);
                printf("\nDigite qualquer tecla para voltar: ");
                getchar();
                getchar();
                break;

            case 4:
                printf("\t�rvore Rubro-Negra com dados desordenados");
                raiz = cria_arvLLRB();
                inserirArvRB("massaDados.csv", raiz);
                testaArvRB(raiz);
                printf("\nDigite qualquer tecla para voltar: ");
                getchar();
                getchar();
                break;
        }
    }
    return 0;
}


