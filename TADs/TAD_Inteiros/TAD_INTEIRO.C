#include <stdlib.h>
#include <stdio.h>

Lista *lst_cria() {
    return NULL;
}

void lst_libera(Lista *l) {
    Lista* p = l;
    while (p != NULL)
    {   
        Lista* t = p->prox;
        free(p);
        p = t;
    }
}

Lista *lst_insere(Lista *l, int i) {
    Lista *novo = (Lista *)malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = l;
    return novo;
}

Lista *lst_retira(Lista *l, int v) {
    Lista* ant = NULL;
    Lista* p = l;

    while (p != NULL && p->info != v)
    {
        ant = p;
        p = p->prox;
    }

    if (p == NULL) {
        return l;
    }

    if (ant == NULL) {
        l = p->prox;
    } else {
        ant->prox = p->prox;
    }

    free(p);
    return l;
}

int lst_vazia(Lista *l) {
    return l == NULL;
    
}

Lista *lst_busca(Lista *l, int v) {
    Lista *aux = l;
    while (aux != NULL)
    {
        if (aux->info == v)
        {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void lst_imprime(Lista *l) {
    Lista *p = l;
    while (p != NULL)
    {
        printf("%d ", p->info);
        p = p->prox;
    }
}
