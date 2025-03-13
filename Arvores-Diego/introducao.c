/* CRUD DE UMA ARVORE BINÁRIA - CRIAR, LER, ATUALIZAR/INSERIR E DELETAR */

#include <stdio.h>
#include <stdlib.h>

/* DEFINIÇÃO DA ÁRVORE USAR UMA ESTRUTURA */
struct arv
{
    char info;
    struct arv *dir;
    struct arv *esq;
};

/* CRIANDO UM TIPO DEFINIDO PARA ESSA ESTRUTURA E SEU PONTEIRO */
typedef struct arv Arv;
typedef struct arv *PArv;

/* FUNÇÃO QUE CRIA UMA ÁRVORE VAZIA */
PArv arvore_cria(void)
{
    return NULL;
}

/* FUNÇÃO QUE ALOCA DINAMICAMENTE MEMÓRIA PARA UM NOVO NÓ*/
PArv aloca_arv(void)
{
    PArv novo_no = (PArv)malloc(sizeof(Arv));
    return novo_no;
}

/* INSERINDO UM NÓ NA ÀRVORES - USANDO O ALGORITMO: PRÉ ORDEM */
PArv arvore_insere(char caractere, PArv no_esquerda, PArv no_direita)
{
    PArv novo_no = aloca_arv();
    novo_no->info = caractere;
    novo_no->esq = no_esquerda;
    novo_no->dir = no_direita;
    return novo_no;
}

/* IMPRIMINDO OS NÓS DE UMA ÁRVOERS - USANDO O ALGORITMO: PRÉ ORDEM */
void arvore_imprime(PArv nó)
{
    if (nó != NULL)
    {
        printf("%c ", nó->info);
        arvore_imprime(nó->esq);
        arvore_imprime(nó->dir);
    }
}

/* FUNÇÃO QUE DELETA A AŔVORE */
void arvore_deleta(PArv nó)
{
    if (nó != NULL)
    {
        arvore_deleta(nó->esq);
        arvore_deleta(nó->dir);
        free(nó);
    }
}

int main(void)
{
    /* Criando um novo nó para verificar a altura */
    PArv no1 = arvore_insere('A', arvore_cria(), arvore_cria());
    PArv no2 = arvore_insere('B', arvore_cria(), arvore_cria());
    PArv no3 = arvore_insere('C', arvore_cria(), arvore_cria());
    PArv no4 = arvore_insere('D', no1, no2);
    PArv raiz = arvore_insere('E', no3, no4);

    // PArv no = arvore_insere('E',
    //                         arvore_insere('C', arvore_cria(), arvore_cria()),
    //                         arvore_insere('D', arvore_insere('A', arvore_cria(), arvore_cria()),
    //                                       arvore_insere('B', arvore_cria(), arvore_cria())));

    /* Imprimindo a árvore */
    arvore_imprime(raiz);
    printf("\n");

    /* Deletando toda a árvore */
    arvore_deleta(raiz);

    return 0;
}