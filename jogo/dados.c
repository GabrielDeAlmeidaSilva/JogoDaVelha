#include "jogo.h"

void inicializa(Bloco **list) {
    *list = NULL;
}

Bloco* criar_nodo() {
    Bloco *novo = malloc(sizeof(Bloco));
    if (!novo) {
        printf("Problema de alocacao\n");
        exit(0);
    }

    novo->dados.jogadasUsuario = NULL;
    novo->dados.jogadasOponente = NULL;
    novo->prox = NULL;

    return novo;
}

void insereJogadaFinal(Jogada **list, int linha, int coluna) {
    Jogada *novo = malloc(sizeof(Jogada));
    if (!novo) {
        printf("Problema de alocacao\n");
        exit(0);
    }
    novo->linha = linha;
    novo->coluna = coluna;
    novo->prox = NULL;

    if (*list == NULL) {
        *list = novo;
    } else {
        Jogada *aux = *list;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;   
    }
}

void preencheDadosPartida(Partida *dados, char linha[]) {
    char *token = strtok(linha, ";");
    if (token == NULL) return;

    // ID
    char *endptr;
    dados->id = (int)strtol(token, &endptr, 10);

    // NomeUsuario
    token = strtok(NULL, ";");
    if (token != NULL) {
        strcpy(dados->nomeUsuario, token);
    }

    // JogadasUsuario
    while ((token = strtok(NULL, ";")) != NULL) {
        if (token[0] == '\0') {
            break;
        }
        int l, c;
        if (sscanf(token, "%d-%d", &l, &c) == 2) {
           insereJogadaFinal(&(dados->jogadasUsuario), l, c);
        } else {
            // NomeOponente
           strcpy(dados->nomeOponente, token);
           break; 
        }
    }

    // JogadasOponente
    while ((token = strtok(NULL, ";")) != NULL) {
        if (token[0] == '\0') {
            break;
        }
        int l, c;
        if (sscanf(token, "%d-%d", &l, &c) == 2) {
           insereJogadaFinal(&(dados->jogadasOponente), l, c);
        } else {
            // Resultado
           strcpy(dados->resultado, token);
           break;
        }
    }
}

int inserePartidaFinal(char linha[], Bloco **list) {
    if (list == NULL) return 0;

    Bloco *novo = criar_nodo();
    preencheDadosPartida(&(novo->dados), linha);

    if (*list == NULL) {
        *list = novo;
    } else {
        Bloco *aux = *list;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

    return 1;
}

void converteStringJogadas(Jogada *dados, char *buffer) {
    char temp[100];
    Jogada *aux = dados;
    while (aux != NULL) {
        sprintf(temp, "%d-%d;", aux->linha, aux->coluna);
        strcat(buffer, temp);
        aux = aux->prox;
    }
}

void converteStringPartida(Partida dados, char *buffer) {
    char temp[100];
    buffer[0] = '\0';
    
    sprintf(buffer, "%d;%s;", dados.id, dados.nomeUsuario);
    converteStringJogadas(dados.jogadasUsuario, buffer);

    strcat(buffer, ";");
    sprintf(temp, "%s;", dados.nomeOponente);
    strcat(buffer, temp);

    converteStringJogadas(dados.jogadasOponente, buffer);

    strcat(buffer, ";");
    sprintf(temp, "%s;", dados.resultado);
    strcat(buffer, temp);


}

void imprimeJogadas(Jogada *list) {
    Jogada *aux = list;
    while (aux != NULL) {
        printf("(%d,%d) ", aux->linha, aux->coluna);
        aux = aux->prox;
    }
    printf("\n");
}

void imprimePartidas(Bloco *list) {
    char linha[1000];

    for (Bloco *aux = list; aux != NULL; aux = aux->prox) {
        converteStringPartida(aux->dados, linha);
        printf("%s\n", linha);
    }
}

void salvarDados(Bloco *list){
    FILE *arquivo;
    char linha[1000];

    arquivo = fopen("partidas_velha.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(0);
    }


    for(Bloco *aux = list; aux != NULL; aux = aux->prox){
        converteStringPartida(aux->dados, linha);
        fprintf(arquivo, "%s\n", linha);
    }

     fclose(arquivo);

}
