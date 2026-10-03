#include <stdio.h>
#include <stdlib.h>
#include "jogo.h" // Importa o seu arquivo de cabeçalho local

int main() {
    char linha_exemplo[] = "1;Lucas;1-1;2-2;3-3;;Computador;1-2;2-1;;Lucas;";

    Bloco *minha_lista;
    inicializa(&minha_lista);
     inserePartidaFinal(linha_exemplo, &minha_lista);

     imprimePartidas(minha_lista);
    salvarDados(minha_lista);

    return 0;
}