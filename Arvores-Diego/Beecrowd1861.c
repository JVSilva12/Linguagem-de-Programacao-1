/* QUESTÃO 1861 DE ÁRVORES FEITA NO BEECROWD - PROF. DIEGO ROCHA */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_MAX 11

/* Estrutura para árvore de Assassinos */
struct arv_ass {
    char nome[SIZE_MAX];
    int num_mortes;
    struct arv_ass* dir;
    struct arv_ass* esq;
};

typedef struct arv_ass Arv_Ass;
typedef struct arv_ass* PArv_Ass;

/* Estrutura para árvore de Vítimas */
struct arv_vit {
    char nome[SIZE_MAX];
    struct arv_vit* dir;
    struct arv_vit* esq;
};

typedef struct arv_vit Arv_Vit;
typedef struct arv_vit* PArv_Vit;

/* Funções para Árvore de Assassinos */
PArv_Ass ArvoreAssCria (void) {
    return NULL;
}

PArv_Ass ArvoreAssAloca (void) {
    PArv_Ass novo_no = (PArv_Ass) malloc(sizeof(Arv_Ass));
    return novo_no;
}

void ArvoreAssDeleta (PArv_Ass raiz) {
    if (raiz != NULL) {
        ArvoreAssDeleta(raiz->esq);
        ArvoreAssDeleta(raiz->dir);
        free(raiz);
    }
}

PArv_Ass ArvoreAssInsere (PArv_Ass raiz, char* nome_ass) {
    if (raiz == NULL) {
        PArv_Ass novo_no = ArvoreAssAloca();
        strcpy(novo_no->nome, nome_ass);
        novo_no->num_mortes = 1;
        novo_no->esq = ArvoreAssCria();
        novo_no->dir = ArvoreAssCria();
        return novo_no;
    } else if (strcmp(nome_ass, raiz->nome) < 0) {
        raiz->esq = ArvoreAssInsere(raiz->esq, nome_ass);
    } else if (strcmp(nome_ass, raiz->nome) > 0) {
        raiz->dir = ArvoreAssInsere(raiz->dir, nome_ass);
    } else {
        raiz->num_mortes++;
    }
    return raiz;
}

/* Funções para Árvore de Vítimas */
PArv_Vit ArvoreVitCria (void) {
    return NULL;
}

PArv_Vit ArvoreVitAloca (void) {
    PArv_Vit novo_no = (PArv_Vit) malloc(sizeof(Arv_Vit));
    return novo_no;
}

void ArvoreVitDeleta (PArv_Vit raiz) {
    if (raiz != NULL) {
        ArvoreVitDeleta(raiz->esq);
        ArvoreVitDeleta(raiz->dir);
        free(raiz);
    }
}

PArv_Vit ArvoreVitInsere (PArv_Vit raiz, char* nome_vit) {
    if (raiz == NULL) {
        PArv_Vit novo_no = ArvoreVitAloca();
        strcpy(novo_no->nome, nome_vit);
        novo_no->esq = ArvoreVitCria();
        novo_no->dir = ArvoreVitCria();
        return novo_no;
    } else if (strcmp(nome_vit, raiz->nome) < 0) {
        raiz->esq = ArvoreVitInsere(raiz->esq, nome_vit);
    } else if (strcmp(nome_vit, raiz->nome) > 0) {
        raiz->dir = ArvoreVitInsere(raiz->dir, nome_vit);
    }
    return raiz;
}

/* Busca na árvore de vítimas */
int ProcuraAss (PArv_Vit raiz, char* nome_ass) {
    if (raiz == NULL) return 0;
    else if (strcmp(nome_ass, raiz->nome) < 0)
        return ProcuraAss(raiz->esq, nome_ass);
    else if (strcmp(nome_ass, raiz->nome) > 0)
        return ProcuraAss(raiz->dir, nome_ass);
    else
        return 1;
}

/* Hall dos Assassinos */
void HallDosAssassinos(PArv_Ass raiz_ass, PArv_Vit raiz_vit) {
    if (raiz_ass != NULL) {
        HallDosAssassinos(raiz_ass->esq, raiz_vit);
        if (!ProcuraAss(raiz_vit, raiz_ass->nome)) {
            printf("%s %d\n", raiz_ass->nome, raiz_ass->num_mortes);
        }
        HallDosAssassinos(raiz_ass->dir, raiz_vit);
    }
}

/* Função Principal */
int main (void) {
    char nome_ass[SIZE_MAX], nome_vit[SIZE_MAX];
    PArv_Ass lista_ass = ArvoreAssCria();
    PArv_Vit lista_vit = ArvoreVitCria();

    while (scanf("%s %s", nome_ass, nome_vit) != EOF) {
        lista_ass = ArvoreAssInsere(lista_ass, nome_ass);
        lista_vit = ArvoreVitInsere(lista_vit, nome_vit);
    }

    printf("HALL OF MURDERERS\n");
    HallDosAssassinos(lista_ass, lista_vit);

    ArvoreAssDeleta(lista_ass);
    ArvoreVitDeleta(lista_vit);

    return 0;
}
