#include <stdio.h>
#include <stdlib.h>
#include "./TAD_Inteiros/TAD_INTEIRO.H"

int main() {
    printf("Criando uma lista de inteiros!\n");
    Lista *minha_lista = lst_cria();
    
    /*if (lst_vazia(minha_lista))
    {
        printf("Minha lista esta vazia!");
    }*/
    for (int i = 0; i < 10; i++)
    {
        minha_lista = lst_insere(minha_lista, rand()%100);
    }

    lst_imprime(minha_lista);

    int v;
    printf("\n\nInforme valor a ser buscado: ");
    scanf("%d", &v);
    
    if(lst_busca(minha_lista, v) != NULL) {
        printf("Valor (%d) encontrado!\n", v);
    } else {
        printf("Valor (%d) não encontrado!\n", v);
    };

    printf("\nInforme valor a ser removido: ");
    scanf("%d", &v);
    minha_lista = lst_retira(minha_lista , v);

    lst_imprime(minha_lista);

    lst_libera(minha_lista);
    printf("\n\n");
    return 0;
}