#include <stdio.h>
#include <stdlib.h>
#include "./TAD_Inteiros/TAD_INTEIRO.H"

int main() {
    printf("Criando uma lista de inteiros!\n");
    Lista *minha_lista = lst_cria();
    if (lst_vazia(minha_lista))
    {
        printf("Minha lista esta vazia!");
    }
    
    printf("\n\n");
    return 0;
}