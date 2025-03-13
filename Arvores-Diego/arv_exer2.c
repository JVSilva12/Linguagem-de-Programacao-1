/*  
    ÁRVORES BINÁRIAS DE BUSCA BALANCEADAS (ÁRVORES AVL)  

    UMA ÁRVORE BINÁRIA ESTAR BALANCEADA SIGNIFICA QUE PARA CADA NÓ, A ALTURA DA SUB-ÁRVORE À DIREITA
    E DA SUB-ÁRVORE À ESQUERDA DIFEREM EM NO MÁXIMO 1, OU SEJA, O FATOR DE BALANCEAMENTO (FB) PODE
    ASSSUIR VALORES COMO: -1, 0 E 1.

*/

#include <stdio.h>
#include <stdlib.h>

/*  DEFINIÇÃO DA ÁRVORE USANDO UMA ESTRUTURA    */
struct arv {
    int FB;
    int info;
    struct arv* esq;
    struct arv* dir;
};

/*  CRIANDO UM TIPO DEFINIDO PARA ESSA ESTRUTURA E SEU PONTEIRO */
typedef struct arv Arv;
typedef struct arv* PArv;

/* FUNÇÃO QUE CRIA UMA ÁRVORE BINÁRIA DE BUSCA VAZIA */
PArv ArvoreCria (void){
    return NULL;
}

/*  FUNÇÃO QUE ALOCA MEMÓRIA DINAMICAMENTE PARA UM NOVO NÓ DE UMA ÁRVORE BINÁRIA    */
PArv ArvoreAloca (void) {
    PArv novo_no = (PArv) malloc (sizeof(Arv));
    return novo_no;
}

/*  FUNÇÃO QUE INSERE UM NOVO NÓ NA ÁRVORE BINÁRIA DE BUSCA */
PArv ArvoreInsere (PArv raiz, int elemento) {
    if (raiz == NULL) {
        PArv novo_no = ArvoreAloca();
        novo_no->info = elemento;
        novo_no->esq = ArvoreCria();
        novo_no->dir = ArvoreCria();
        return novo_no;
    } else if (raiz->info > elemento)
        raiz->esq = ArvoreInsere(raiz->esq, elemento);
    else
        raiz->dir = ArvoreInsere(raiz->dir, elemento);
    return raiz;
}

/*  FUNÇÃO QUE IMPRIME UMA ÁRVORE USANDO O ALGORITMO PRÉ-ORDEM  */
void ImprimePreOrdem (PArv raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->info);
        ImprimePreOrdem(raiz->esq);
        ImprimePreOrdem(raiz->dir);
    }
}

/*  FUNÇÃO QUE IMPRIME UMA ÁRVORE USANDO O ALGORITMO EM-ORDEM  */
void ImprimeEmOrdem (PArv raiz) {
    if (raiz != NULL) {
        ImprimeEmOrdem(raiz->esq);
        printf("%d ", raiz->info);
        ImprimeEmOrdem(raiz->dir);
    }
}

/*  FUNÇÃO QUE IMPRIME UMA ÁRVORE USANDO O ALGORITMO PÓS-ORDEM  */
void ImprimePosOrdem (PArv raiz) {
    if (raiz != NULL) {
        ImprimePosOrdem(raiz->esq);
        ImprimePosOrdem(raiz->dir);
        printf("%d ", raiz->info);
    }
}


/* FUNÇÃO QUE DELETA UMA ÁRVORE */
void ArvoreDeleta(PArv raiz) {
    if (raiz != NULL) {
        ArvoreDeleta(raiz->esq);
        ArvoreDeleta(raiz->dir);
        free(raiz);
    }
}

/* FUNÇÃO QUE CALCULA A ALTURA DE UM DETERMINADO NÓ */
int ArvoreAltura (PArv no) {
    int esquerda, direita;
    if (no == NULL)
        return -1;
    esquerda = ArvoreAltura(no->esq);
    direita = ArvoreAltura(no->dir);
    if (esquerda > direita)
        return esquerda + 1;
    else
        return direita + 1;   
}

/* FUNÇÃO PARA CALCULAR O FATOR DE BALANCEAMENTO DE UM NÓ */
int FatorDeBalanceamento (PArv no) {
    if (no == NULL) // Nó nulo
        return -1;
    else if (no->esq == NULL && no->dir == NULL) // Folha
        return 0;
    else { // Nó que possui filho(s)
    int altura_esq, altura_dir;
    int FB;
    altura_esq = ArvoreAltura(no->esq);
    altura_dir = ArvoreAltura(no->dir);
    FB = altura_dir - altura_esq;
    return FB;
    }
}

/*  FUNÇÃO QUE ATRIBUI O FATOR DE BALANCEAMENTO À CADA NÓ   */
PArv ArvoreAtribuiFB (PArv raiz) {
    if (raiz != NULL) {
        raiz->FB = FatorDeBalanceamento(raiz);
        ArvoreAtribuiFB(raiz->esq);
        ArvoreAtribuiFB(raiz->dir);
    }
}

/*  FUNÇÃO QUE IMPRIME UM NÓ E SEU FATOR DE BALANCIAMENTO   */
void ImpremePreOrdemFB (PArv raiz) {
    if (raiz != NULL) {
        printf("nó: %d - FB: %d\n", raiz->info,raiz->FB);
        ImpremePreOrdemFB(raiz->esq);
        ImpremePreOrdemFB(raiz->dir);
    }
}
int main (void) {
    /* Inserindo valores na árvore binária de busca */
    int valor;
    PArv raiz = ArvoreCria();
    while (scanf("%d", &valor) != EOF)
        raiz = ArvoreInsere(raiz, valor);

    /* Imprimindo a árvore usando os três algoritmos */
    printf("Impreção da árvore:");
    printf("\nPré-ordem: "); ImprimePreOrdem(raiz);
    printf("\nEm ordem: "); ImprimeEmOrdem(raiz);
    printf("\nPós-ordem: "); ImprimePosOrdem(raiz);
    printf("\n");

    /* Atribuindo o fator de balanceamento para cada nó */
    raiz = ArvoreAtribuiFB(raiz);

    /* Imprimindo a árvore em pré ordem juntamente com os respectivos FB's de cada nó */
    printf("Imprimindo os FB's:\n"); ImpremePreOrdemFB(raiz);

    return 0;
}