/* QUESTÃO 1195 de ÁRVORES FEITA NO BEECROWD - PROF. DIEGO ROCHA */
#include <stdio.h>
#include <stdlib.h>

/* DEFINIÇÃO DA ÁRVORE USANDO UMA ESTRUTURA */
struct arv {
    char info;
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
PArv arv_bdb_insere (PArv raiz, char c) {
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

/* IMPRIMINDO A ÁRVORE USANDO O ALGORITMO EM ORDEM */
void arv_imprime_em_ordem(PArv raiz) {
    if (raiz != NULL) {
        arv_imprime_em_ordem(raiz->esq);
        printf(" %c", raiz->info);
        arv_imprime_em_ordem(raiz->dir);
    }
}

/* IMPRIMINDO A ÁRVORE USANDO O ALGORITMO PRÉ ORDEM */
void arv_imprime_pre_ordem(PArv raiz) {
    if (raiz != NULL) {
        printf(" %c", raiz->info);
        arv_imprime_pre_ordem(raiz->esq);
        arv_imprime_pre_ordem(raiz->dir);
    }
}

/* IMPRIMINDO A ÁRVORE USANDO O ALGORITMO PÓS ORDEM */
void arv_imprime_pos_ordem(PArv raiz) {
    if (raiz != NULL) {
        arv_imprime_pos_ordem(raiz->esq);
        arv_imprime_pos_ordem(raiz->dir);
        printf(" %c", raiz->info);
    }
}

/* DELETANDO A ÁRVORE TODA */
void arv_deleta (PArv raiz) {
    if (raiz != NULL) {
        arv_deleta(raiz->esq);
        arv_deleta(raiz->dir);
        free(raiz);
    }
}

int main (void) {
    int qtd_testes;
    int qtd_nos;
    char valor;

    /* Capturando a quantidade de testes que serão feitos */
    scanf("%d", &qtd_testes);

    for (int j = 1; j <= qtd_testes; j++) {
    /* Capturando a quantidade de nós da arvore */
        scanf("%d", &qtd_nos);
        /* Criando uma nova raiz */
        PArv raiz = arvore_cria();

        for (int i = 1; i <= qtd_nos; i++) {
        /* Capturando os valores para a árvore */
            scanf(" %c", &valor);
            raiz = arv_bdb_insere(raiz, valor);
        }
        /* Imprimindo a árvore criada no loop anterior */
        printf("Case %d:", j);
            printf("\nPre.:"); arv_imprime_pre_ordem(raiz);
            printf("\nIn..:"); arv_imprime_em_ordem(raiz);
            printf("\nPost:"); arv_imprime_pos_ordem(raiz);
            printf("\n\n");
            arv_deleta(raiz);
    }
    return 0;
}