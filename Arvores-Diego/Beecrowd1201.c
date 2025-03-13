/* QUESTÃO 1201 de ÁRVORES FEITA NO BEECROWD */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 15


/* DEFINIÇÃO DA ÁRVORE USANDO UMA ESTRUTURA */
struct arv {
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

/* IMPRIMINDO A ÁRVORE USANDO O ALGORITMO EM ORDEM */
void arv_imprime_em_ordem(PArv raiz, int *flag) {
    if (raiz != NULL) {
        arv_imprime_em_ordem(raiz->esq, flag);
        if (*flag) {
            printf("%d", raiz->info);
            *flag = 0;
        } else
            printf(" %d", raiz->info);
        arv_imprime_em_ordem(raiz->dir, flag);
    }
}

/* IMPRIMINDO A ÁRVORE USANDO O ALGORITMO PRÉ ORDEM */
void arv_imprime_pre_ordem(PArv raiz, int *flag) {
    if (raiz != NULL) {
        if (*flag) {
            printf("%d", raiz->info);
            *flag = 0;
        } else
            printf(" %d", raiz->info);
        arv_imprime_pre_ordem(raiz->esq, flag);
        arv_imprime_pre_ordem(raiz->dir, flag);
    }
}

/* IMPRIMINDO A ÁRVORE USANDO O ALGORITMO PÓS ORDEM */
void arv_imprime_pos_ordem(PArv raiz, int *flag) {
    if (raiz != NULL) {
        arv_imprime_pos_ordem(raiz->esq, flag);
        arv_imprime_pos_ordem(raiz->dir, flag);
        if (*flag) {
            printf("%d", raiz->info);
            *flag = 0;
        } else
            printf(" %d", raiz->info);
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
/* PROCURANDO UM ELEMENTO NA ÁRVORE*/
int arvore_procura(PArv raiz, int c) {
    if (raiz == NULL)
        return 0;
    else if (raiz->info > c)
        return arvore_procura(raiz->esq, c);
    else if (raiz->info < c)
        return arvore_procura(raiz->dir, c);
    else
        return 1;
}

/* REMOVENDO UM ELEMENTO DA ÁRVORE */
PArv arvore_remove(PArv raiz, int elemento) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->info > elemento)
        raiz->esq = arvore_remove(raiz->esq, elemento);
    else if (raiz->info < elemento)
        raiz->dir = arvore_remove(raiz->dir, elemento);
    else  {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            raiz = NULL;
        }
    else if (raiz->esq == NULL) {
        PArv no_aux = raiz;
        raiz = raiz->dir;
        free(no_aux);
    } else if (raiz->dir == NULL){
         PArv no_aux = raiz;
        raiz = raiz->esq;
        free(no_aux);
    } else {
        PArv no_aux = raiz->esq;
        while (no_aux->dir != NULL) {
            no_aux = no_aux->dir;
        }
        raiz->info = no_aux->info;
        no_aux->info = elemento;
        raiz->esq = arvore_remove(raiz->esq, elemento);
        }
    }
    return raiz;
}

int main (void) {
    char opcao[MAX_SIZE];
    int elemento;
    int flag;
    /* Criando a árvore binária de busca */
    PArv raiz = arvore_cria();

     while (fgets(opcao, sizeof(opcao), stdin) != NULL) {

        opcao[strcspn(opcao, "\n")] = '\0';

        if (opcao[0] == 'I' && opcao[1] == ' ') {
          sscanf(opcao + 2, "%d", &elemento);
          raiz = arv_bdb_insere(raiz, elemento);

        } else if (opcao[0] == 'P' && opcao[1] == ' ') {
            sscanf(opcao + 2, "%d", &elemento);
            if (arvore_procura(raiz,elemento))
                printf("%d existe\n", elemento);
            else
                printf("%d nao existe\n", elemento);

        } else if (opcao[0] == 'R' && opcao[1] == ' ') {
            sscanf(opcao + 2, "%d", &elemento);
             raiz = arvore_remove(raiz, elemento);

        } else if (strcmp(opcao, "INFIXA") == 0) {
            flag = 1;
            arv_imprime_em_ordem(raiz, &flag);
            if (raiz)
                printf("\n");
        } else if (strcmp(opcao, "PREFIXA") == 0) {
            flag = 1;
            arv_imprime_pre_ordem(raiz, &flag); 
            if (raiz)
                printf("\n");
        } else if (strcmp(opcao, "POSFIXA") == 0) {
            flag = 1;
            arv_imprime_pos_ordem(raiz, &flag);
            if (raiz)
                printf("\n");
        }
    }
        /* Apagando a árvore */
        arv_deleta(raiz);

    return 0;
}