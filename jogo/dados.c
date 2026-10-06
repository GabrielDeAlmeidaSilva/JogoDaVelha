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


void inserePartidaFinal(Partida partida, Bloco **list) {
    

    Bloco *novo = criar_nodo();
    novo->dados = partida;

    if (*list == NULL) {
        *list = novo;
    } else {
        Bloco *aux = *list;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
    }

   
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
    sprintf(temp, "%s", dados.resultado);
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

void liberarJogadas(Jogada **list) {
    if (list == NULL) return;
    
    Jogada *atual = *list;
    while (atual != NULL) {
        Jogada *temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *list = NULL; 
}

void liberarPartidas(Bloco **list) {
    if (list == NULL) return;
    
    Bloco *atual = *list;
    while (atual != NULL) {
        Bloco *temp = atual;
        atual = atual->prox;
   
     
        liberarJogadas(&(temp->dados.jogadasUsuario));
        liberarJogadas(&(temp->dados.jogadasOponente));
        
        free(temp);
    }
    *list = NULL; 
}