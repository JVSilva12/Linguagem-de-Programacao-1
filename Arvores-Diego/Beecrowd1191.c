/* QUESTÃO 1191 DE ÁRVORES FEITA NO BEECROWD - PROF. DIEGO ROCHA */
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

/* IMPRIMINDO A ÁRVORE USANDO O ALGORITMO PÓS ORDEM */
void arv_imprime_pos_ordem(PArv raiz) {
    if (raiz != NULL) {
        arv_imprime_pos_ordem(raiz->esq);
        arv_imprime_pos_ordem(raiz->dir);
        printf("%c", raiz->info);
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
/* FUNÇÃO QUE RETORNA O INDICE DE UM NÓ VETOR EM ORDEM */
int idx_no (char no, char* em_ordem) {
    for (int i = 0; em_ordem[i] != '\0'; i++)
        if (em_ordem[i] == no)
            return i;
}

/* FUNÇÃO QUE RETORNA -1 SE O CARACTERE ESTÁ A ESQUERDA E +1 SE ESTÁ A DIREITA DE UM NÓ*/
int esq_dir (char no_centro, char no, char* em_ordem) {
    int idx = idx_no(no_centro, em_ordem);
    for (int i = 0; i <= idx; i++)
        if (em_ordem[i] == no)
            return -1; //está a esquerda do nó passado como centro
    return +1; //está a direita do nó passado como centro
}

/* FUNÇÃO QUE INSERE UM VALOR NA ÁRVORE COM BASE NAS STRINGS */
PArv arv_insere (PArv raiz, char caractere, char* em_ordem) {
    if (raiz == NULL) {
        PArv novo_no = aloca_arv();
        novo_no->info = caractere;
        novo_no->dir = arvore_cria();
        novo_no->esq = arvore_cria();
        return novo_no;
    } else if (esq_dir(raiz->info, caractere, em_ordem) == -1) /* ANDA NA ESQUERDA */
        raiz->esq = arv_insere(raiz->esq, caractere, em_ordem);
    else /* ANDA  NA DIREITA */
        raiz->dir = arv_insere(raiz->dir, caractere, em_ordem);
    return raiz;
}

int main (void) {
    
    /* Strigns que irão gaurdar as ordens dos percuros em uma árvore binária (em e pré ordem) */
    char pre_ordem[27];
    char em_ordem[27];
    
    /* O while a seguir utiliza a estratégia EOF mas de uma maneira diferente, pois fgets retorna NULL e não EOF*/
    while (scanf("%s %s", pre_ordem, em_ordem) != EOF) {
        /* Criando a árvore e inserindo nela utilizando a função insere */
        PArv raiz = arvore_cria();
        for (int i = 0; pre_ordem[i] != '\0' && pre_ordem[i] != '\n'; i++)
        raiz = arv_insere(raiz, pre_ordem[i], em_ordem);

        /* Imprimindo a árvore usando o algoritmo pós ordem */
        arv_imprime_pos_ordem(raiz);
        printf("\n");
        arv_deleta(raiz);
    }
    return 0;
}