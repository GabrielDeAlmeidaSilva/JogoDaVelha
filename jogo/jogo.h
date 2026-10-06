#ifndef JOGO_H
#define JOGO_H

#define FALSE 0
#define TRUE 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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
void inserePartidaFinal(Partida partida, Bloco **list);

//impressao
void converteStringPartida(Partida dados, char *buffer);
void converteStringJogadas(Jogada *dados, char *buffer);
void imprimeJogadas(Jogada *list);
void imprimePartidas(Bloco *list);
void salvarDados(Bloco *list);

//FREE
void liberarJogadas(Jogada **list);
void liberarPartidas(Bloco **list);

typedef struct Ranking {
    char nome[50];
    int vitorias;
    struct Ranking *prox;
} Ranking;

void inicializaRanking(Ranking **list);
Ranking* cria_nodoRanking();

void incrementar_vitoria(Ranking *list, const char *jogador);
Ranking* processarRankingArquivo(const char *arquivo, Ranking *list);
void ordena (Ranking **list);
void exibir_ranking(Ranking *list);
Ranking* garantir_jogador(Ranking *list, const char *jogador);
void liberarRanking(Ranking **list);

//jogo
int number_verify(char *n);
void ler_dado(char *msg, int *var);
void esc(char *msg);

int par_impar();
void inicializa_tabuleiro(int matriz[3][3]);
void imprime_tabuleiro(int matriz[3][3], int vencedor); 
int valida_jogada(int i, int j, int matriz[3][3]);
int verifica_vitoria(int matriz[3][3]);
void inteligencia_artificial(int matriz[3][3], int *linha, int *coluna);
void inteligencia_natural(int matriz[3][3], int *linha, int *coluna);
void atribui_matriz(int matriz[3][3], int i, int j, int quem);


#endif