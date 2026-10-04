#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

//declaracao das struct
typedef struct Jogada {
    int linha;
    int coluna;
    struct Jogada *prox;
} Jogada;

typedef struct Partida {
    int id;
    char nomeUsuario[50];
    Jogada *jogadasUsuario;
    char nomeOponente[50];
    Jogada *jogadasOponente;
    char resultado[50];

}Partida;

typedef struct Bloco {
    Partida dados;
    struct Bloco *prox;
}Bloco;

//inciacao
void inicializa(Bloco **list);
Bloco* criar_nodo();

//insercao
void insereJogadaFinal(Jogada **list, int linha, int coluna );
void preencheDadosPartida(Partida *dados, char linha[]);
int inserePartidaFinal(char linha[], Bloco **list);

//impressao
void converteStringPartida(Partida dados, char *buffer);
void converteStringJogadas(Jogada *dados, char *buffer);
void imprimeJogadas(Jogada *list);
void imprimePartidas(Bloco *list);
void salvarDados(Bloco *list);

typedef struct Ranking {
    char nome[50];
    int vitorias;
    struct Ranking *prox;
} Ranking;

Ranking* cria_nodoRanking();
Ranking* atualizar_ou_inserir(Ranking *list, const char *jogador);
Ranking* processarRankingArquivo(const char *nome_arquivo, Ranking *list);
void ordena (Ranking **list);
void exibir_ranking(Ranking *list);


#endif