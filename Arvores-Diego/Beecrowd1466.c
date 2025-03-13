/* QUESTÃO 1466 de ÁRVORES FEITA NO BEECROWD */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* DEFINIÇÃO DA ÁRVORE USANDO UMA ESTRUTURA */
struct arv {
    int nivel;
    int info;
    struct arv* dir;
    struct arv* esq;
};

/* CRIANDO UM TIPO DEFINIDO PARA ESSA ESTRUTURA E SEU PONTEIRO */
typedef struct arv Arv;
typedef struct arv* PArv;

/* FUNÇÃO QUE CRIA UMA ÁRVORE VAZIA */
PArv arvore_cria (void) {
    return NULL;
}

/* FUNÇÃO QUE ALOCA DINAMICAMENTE MEMÓRIA PARA UM NOVO NÓ*/
PArv aloca_arv (void) {
    PArv novo_no = (PArv) malloc (sizeof(Arv));
    return novo_no;
}

/* INSERINDO UM ELEMENTO NA ÁRVORE BINÁRIA DE BUSCA */
PArv arv_bdb_insere (PArv raiz, int c) {
    if (raiz == NULL) {
        PArv novo_no = aloca_arv();
        novo_no->info = c;
        novo_no->dir = arvore_cria();
        novo_no->esq = arvore_cria();
        return novo_no;
    } else if (c < raiz->info) /* ANDA NA ESQUERDA */
        raiz->esq = arv_bdb_insere(raiz->esq, c);
    else /* ANDA  NA DIREITA */
        raiz->dir = arv_bdb_insere(raiz->dir, c);
    return raiz;
}

/* DELETANDO A ÁRVORE TODA */
void arv_deleta (PArv raiz) {
    if (raiz != NULL) {
        arv_deleta(raiz->esq);
        arv_deleta(raiz->dir);
        free(raiz);
    }
}

/* FUNÇÃO QUE RETORNA A ALTURA DE UM ÁRVORE */
int arvore_altura (PArv raiz) {
    int D, E;
    if (raiz == NULL)
        return -1;
    E = arvore_altura(raiz->esq);
    D = arvore_altura(raiz->dir);
    if (E > D)
        return E+1;
    else
        return D+1;
}

/* FUNÇÃO QUE DEFINE OS NÍVEIS DE UMA ÁRVORE */
void define_niveis (PArv raiz, int nivel) {
    if (raiz!= NULL) {
        raiz->nivel = nivel;
        define_niveis(raiz->esq, nivel+1);
        define_niveis(raiz->dir, nivel+1);
    }
}

/* FUNÇÃO QUE IMPRIME A ÁRVORE DADO UM NIVEL */
void imprime_por_nivel (PArv raiz, int nivel, int *primeiro) {
    if (raiz != NULL) {
        if (raiz->nivel == nivel) {
            if (*primeiro) {
                printf("%d", raiz->info);
                *primeiro= 0;
            } else 
                printf(" %d", raiz->info);
        } 
        imprime_por_nivel(raiz->esq, nivel, primeiro);
        imprime_por_nivel(raiz->dir, nivel, primeiro);
    }
}

/* FUNÇÃO QUE IMPRIME A ÁRVORE POR NIVEIS */
void imprime_em_nivel (PArv raiz) {
    int h = arvore_altura(raiz);
    int primeiro = 1;
    for (int i = 0; i <= h; i++) {
        imprime_por_nivel(raiz, i, &primeiro);
    }
}

int main (void) {
    int qtd_testes;
    int qtd_nos;
    int valor;
    /* Capturando a quantidade de testes que serão feitos */
    scanf("%d", &qtd_testes);

    for (int j = 1; j <= qtd_testes; j++) {
    /* Capturando a quantidade de nós da arvore */
        scanf("%d", &qtd_nos);
        /* Criando uma nova raiz */
        PArv raiz = arvore_cria();

        for (int i = 1; i <= qtd_nos; i++) {
        /* Capturando os valores para a árvore */
            scanf("%d", &valor);
            raiz = arv_bdb_insere(raiz, valor);
        }
        define_niveis(raiz, 0);
        printf("Case %d:\n", j);
        imprime_em_nivel(raiz);
        printf("\n\n");
        arv_deleta(raiz);
    }

    return 0;
}

/* 	PEDIR AO PROFESSOR PARA EXPLICAR A BUSCA EM LARGURA (BUSCA POR NIVEIS)*/