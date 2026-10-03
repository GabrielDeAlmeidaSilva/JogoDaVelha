#include "jogo.h"

Bloco* carregarPartidasDoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return NULL; 
    }

    Bloco *listaPartidas = NULL;
    char linha[1000];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\r\n")] = 0; // Remove a quebra de linha (\n ou \r\n)
        if (strlen(linha) > 0) {
            inserePartidaFinal(linha, &listaPartidas);
        }
    }
    fclose(arquivo);
    return listaPartidas;
}
