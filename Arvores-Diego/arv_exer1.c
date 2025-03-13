/* TREINANDO OS ALGORITMOS PARA PERCORRER ÁRVORES - EXERCÍCIOS DO SLIDE 1 - PROF. DIEGO ROCHA */
#include <stdio.h>
#include <stdlib.h>

/* DEFINIÇÃO DA ÁRVORE USAR UMA ESTRUTURA */
struct arv
{
    char info;
    int nivel;
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

/* INSERINDO UM NÓ NA ÁRVORES - USANDO O ALGORITMO: PRÉ ORDEM */
PArv arvore_insere(char caractere, PArv no_esquerda, PArv no_direita)
{
    PArv novo_no = aloca_arv();
    novo_no->info = caractere;
    novo_no->esq = no_esquerda;
    novo_no->dir = no_direita;
    return novo_no;
}

/* IMPRIMINDO OS NÓS DE UMA SUB-ÁRVOERES - USANDO O ALGORITMO: PRÉ ORDEM */
void arvore_imprime(PArv Sub_A)
{
    if (Sub_A != NULL)
    {
        printf("%c ", Sub_A->info);
        arvore_imprime(Sub_A->esq);
        arvore_imprime(Sub_A->dir);
    }
}

/* QUESTÃO 1 - FUNÇÃO QUE DELETA UMA SUB-ÁRVORE */
void arvore_deleta(PArv Sub_A)
{
    if (Sub_A != NULL)
    {
        arvore_deleta(Sub_A->esq);
        arvore_deleta(Sub_A->dir);
        free(Sub_A);
    }
}

/* FUNÇÃO PARA A QUESTÃO 2 - DEFINE OS NIVEIS DE CADA NÓ DA ÁRVORE */
void define_niveis(PArv raiz, int nivel)
{
    if (raiz != NULL)
    {
        raiz->nivel = nivel;
        define_niveis(raiz->esq, nivel + 1);
        define_niveis(raiz->dir, nivel + 1);
    }
}

/* FUNÇÃO PARA A QUESTÃO 2 (QUESTÃO 4) - IMPRIME OS NÍVEIS DE UMA SUB-ÁRVORE */
void niveis_imprime(PArv no)
{
    if (no != NULL)
    {
        printf("%c  - nível: %d\n", no->info, no->nivel);
        niveis_imprime(no->esq);
        niveis_imprime(no->dir);
    }
}

/* QUESTÃO 2 - FUNÇÃO QUE IMPRIME O NÍVEL DE UM DETERMINADO NÓ, CASO ESTE ESTEJA NA ÁRVORE */
void arvore_busca(PArv raiz, char c)
{
    if (raiz != NULL)
    {
        if (raiz->info == c)
        {
            int nivel_no = raiz->nivel;
            printf("%c está no nivel %d\n", c, nivel_no);
        }
        arvore_busca(raiz->esq, c);
        arvore_busca(raiz->dir, c);
    }
}

/* QUESTÃO 3 - FUNÇÃO QUE INDICA A ALTURA/PROFUNDIADE DE UMA ÁRVORE */ /* PEDIR PARA O PROFESSOR EXPLICAR */
int arvore_altura(PArv raiz)
{
    int D, E;
    if (raiz == NULL)
        return -1;
    E = arvore_altura(raiz->esq);
    D = arvore_altura(raiz->dir);
    if (E > D)
        return E + 1;
    else
        return D + 1;
}

/* QUESTÃO 5 - FUNÇÃO QUE IMPRIME OS ELEMENTOS DE UM DETERMIANDO NIVEL */
void imprime_por_nivel(PArv raiz, int nivel)
{
    if (raiz != NULL)
    {
        if (raiz->nivel == nivel)
            printf("%c ", raiz->info);
        imprime_por_nivel(raiz->esq, nivel);
        imprime_por_nivel(raiz->dir, nivel);
    }
}

/* IMPLEMENTANDO A QUESTÃO 5 EM UMA FUNÇÃO QUE IMPRIME A ÁRVORE POR NIVEIS */
void imprime_escadinha(PArv raiz)
{
    int h = arvore_altura(raiz);
    for (int i = 0; i <= h; i++)
    {
        imprime_por_nivel(raiz, i);
        printf("-> Nivel %d\n", i);
    }
}

int main(void)
{
    /* Criando a minha árvore (igual a do caderno) */
    PArv no1 = arvore_insere('G', arvore_cria(), arvore_cria());
    PArv no2 = arvore_insere('H', arvore_cria(), arvore_cria());
    PArv no3 = arvore_insere('F', no1, no2);
    PArv no4 = arvore_insere('B', no3, arvore_cria());
    PArv no5 = arvore_insere('I', arvore_cria(), arvore_cria());
    PArv no6 = arvore_insere('J', arvore_cria(), arvore_cria());
    PArv no7 = arvore_insere('D', arvore_cria(), arvore_cria());
    PArv no8 = arvore_insere('E', no5, no6);
    PArv no9 = arvore_insere('C', no7, no8);
    PArv raiz = arvore_insere('A', no4, no9);

    /* QUESTÃO 4 - Definindo e imprimindo a árvove com os níveis */
    define_niveis(raiz, 0);
    /*niveis_imprime(raiz);*/

    /* QUESTÃO 2 - Procurando um determinado caractere na árvore */
    int c = 'B';
    arvore_busca(raiz, c);

    /* QUESTÃO 3 - Determinando a altura da árvore */
    int h;
    h = arvore_altura(raiz);
    printf("A árvore possui %d niveis\n", h);

    /* QUESTÃO 5 - Imprimindo os nós de um determinado nível */
    int nivel;
    nivel = 3;
    if (nivel <= h)
    {
        printf("Nós do nível %d: ", nivel);
        imprime_por_nivel(raiz, nivel);
        printf("\n");
    }
    else
        printf("Índice fora do esperado\n");

    /*Imprimindo como se fosse a função 'tree' no linux */
    imprime_escadinha(raiz);

    /* QUESTÃO 1 - Deletando toda a árvore */
    arvore_deleta(raiz);

    return 0;
}