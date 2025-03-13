#include <stdio.h>
#include <stdlib.h>

typedef struct arv
{
    char info;
    struct arv *esq;
    struct arv *dir;
} Arv;

Arv *arv_criavazia()
{
    return NULL;
}

Arv *arv_cria(char c, Arv *sae, Arv *sad)
{
    Arv *p = (Arv *)malloc(sizeof(Arv));
    p->info = c;
    p->esq = sae;
    p->dir = sad;
    return p;
}

void arv_imprime(Arv *a)
{
    if (a)
    {
        printf("%c ", a->info);
        arv_imprime(a->esq);
        arv_imprime(a->dir);
    }
    printf(">");
}

Arv *arv_libera(Arv *a)
{
    if (a)
    {
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    return NULL;
}

int arv_pertence(Arv *a, char c)
{
    if (!a)
    {
        return 0;
    }
    else
    {
        return a->info == c || arv_pertence(a->esq, c) || arv_pertence(a->dir, c);
    }
}

int max2(int a, int b)
{
    return (a > b) ? a : b;
}

int arv_altura(Arv *a)
{
    if (!a)
    {
        return -1;
    }
    else
    {
        return 1 + max2(arv_altura(a->esq), arv_altura(a->dir));
    }
}

int arv_vazia(Arv *a)
{
    return a == NULL;
}

int main()
{
    // Arv *raiz = arv_criavazia();
    // Arv *no1 = arv_cria('F', arv_criavazia(), arv_criavazia());
    // Arv *no2 = arv_cria('E', arv_criavazia(), arv_criavazia());
    // Arv *no3 = arv_cria('C', no2, no1);
    // Arv *no4 = arv_cria('D', arv_criavazia(), arv_criavazia());
    // Arv *no5 = arv_cria('B', arv_criavazia(), no4);
    // raiz = arv_cria('A', no5, no3);

    Arv *a = arv_cria('A',
                      arv_cria('B',
                               arv_criavazia(),
                               arv_cria('D', arv_criavazia(), arv_criavazia())),
                      arv_cria('C',
                               arv_cria('E', arv_criavazia(), arv_criavazia()),
                               arv_cria('F',
                                        arv_cria('G', arv_criavazia(), arv_criavazia()),
                                        arv_criavazia())));

    arv_imprime(a);

    printf("\n\nValor [1] pertence, [2] nao pertence!\n");
    printf("\nF : [%d]", arv_pertence(a, 'F'));
    printf("\nH : [%d]\n", arv_pertence(a, 'H'));

    int h;
    h = arv_altura(a);
    printf("\nA árvore possui %d niveis\n", h);

    arv_libera(a);

    printf("\n\n");
    return 0;
}