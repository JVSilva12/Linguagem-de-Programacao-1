/* QUESTÃO 1200 de ÁRVORES FEITA NO BEECROWD */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void arv_imprime_em_ordem(PArv raiz, int *primeiro) {
    if (raiz != NULL) {
        arv_imprime_em_ordem(raiz->esq, primeiro);
        if (*primeiro) {
            printf("%c", raiz->info);
            *primeiro = 0;
        } else
            printf(" %c", raiz->info);
        arv_imprime_em_ordem(raiz->dir, primeiro);
    }
}

/* IMPRIMINDO A ÁRVORE USANDO O ALGORITMO PRÉ ORDEM */
void arv_imprime_pre_ordem(PArv raiz, int *primeiro) {
    if (raiz != NULL) {
        if (*primeiro) {
            printf("%c", raiz->info);
            *primeiro = 0;
        } else
            printf(" %c", raiz->info);
        arv_imprime_pre_ordem(raiz->esq, primeiro);
        arv_imprime_pre_ordem(raiz->dir, primeiro);
    }
}

/* IMPRIMINDO A ÁRVORE USANDO O ALGORITMO PÓS ORDEM */
void arv_imprime_pos_ordem(PArv raiz, int *primeiro) {
    if (raiz != NULL) {
        arv_imprime_pos_ordem(raiz->esq, primeiro);
        arv_imprime_pos_ordem(raiz->dir, primeiro);
        if (*primeiro) {
            printf("%c", raiz->info);
            *primeiro = 0;
        } else
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

int arvore_procura(PArv raiz, char c) {
    if (raiz == NULL)
        return 0;
    else if (raiz->info > c)
        return arvore_procura(raiz->esq, c);
    else if (raiz->info < c)
        return arvore_procura(raiz->dir, c);
    else
        return 1;
}


/* FUNÇÃO QUE RETORNA UM NÚMERO DE ACORDO COM A OPERAÇÃO DESEJADA */
int def_operacao (char* str) {
    if (strlen(str) < 3)
        return 0; /* TAMANHO MINIMO DE STRING NOA ATINGIDO */
    if (str[0] == 'I' && str[1] == ' ')
        return 1; /* Operação de Inserção na Árvore Binária de Pesquisa */
    else if (str[0] == 'P'  && str[1] == ' ')
        return 2; /* Operação de Busca na árvore */
    else if (str[0] == 'I' && str[1] == 'N')
        return 3; /* Operação de imprimir na ordem infixa */
    else if (str[0] == 'P' && str[1] == 'R')
        return 4; /* Operação de imprimir na ordem prefixa */
    else if (str[0] == 'P' && str[1] == 'O')
        return 5; /* Operação de imprimir na ordem posfixa */
    else 
        return 0; /* Parâmetro Errado passado */
}

int main (void) {
    char opcao[8];
    int primeiro;
    /* Criando a árvore binária de busca */
    PArv raiz = arvore_cria();
    while (fgets(opcao, sizeof(opcao), stdin) != NULL) {
    /* Mostrando as Opções a serem feitas*/
        switch (def_operacao(opcao)) {
            case 1:
            /* Inserindo o valores na árvore */
            raiz = arv_bdb_insere(raiz, opcao[2]);
            break;
            case 2:
            /* Procurando o valor na árvore */
            if (arvore_procura(raiz,opcao[2]))
                printf("%c existe\n", opcao[2]);
            else
                printf("%c nao existe\n", opcao[2]);
            break;
            case 3:
            primeiro = 1;
            arv_imprime_em_ordem(raiz, &primeiro);
            printf("\n");
            break;
            case  4:
            primeiro = 1;
            arv_imprime_pre_ordem(raiz, &primeiro); 
            printf("\n");
            break;
            case 5:
            primeiro = 1;
            arv_imprime_pos_ordem(raiz, &primeiro);
            printf("\n");
            break;
        }
    }
        /* Apagando a árvore */
        arv_deleta(raiz);

    return 0;
}

/* 	ESTÁGIO: Presentation error */