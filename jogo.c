#include "jogo.h"

void atribui_matriz(int matriz[3][3], int i, int j, int quem) {
    matriz[i][j] = (quem == 0) ? 0 : 1;    
}

/*Funções em si*/
void inteligencia_natural(int matriz[3][3], int *linha, int *coluna){
    int i, j;
    do {
        ler_dado("Digite a linha => ", &i);
        ler_dado("Digite a coluna => ", &j);
    } while(!valida_jogada(i, j, matriz));

    *linha = i;
    *coluna = j;
}

void inteligencia_artificial(int matriz[3][3], int *linha, int *coluna) {   
    //Testa a vitoria do robo tambem
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(matriz[i][j] == -1){
                matriz[i][j] = 1; 
                //Se ele for ganhar
                if(verifica_vitoria(matriz) == 1) {
                    *linha = i;
                    *coluna = j;
                    matriz[i][j] = -1; 
                    return;
                }
                //desfaz a jogada
                matriz[i][j] = -1;
            }
        }
    }

    //Algoritimo do testa tudo
    //E blockeia tudo
    //Não Passa nada
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(matriz[i][j] == -1){
                matriz[i][j] = 0; 
                //Se ele for ganhar
                if(verifica_vitoria(matriz) == 0) {
                    *linha = i;
                    *coluna = j;
                    matriz[i][j] = -1; 
                    return;
                }
                //desfaz a jogada
                matriz[i][j] = -1;
            }
        }
    }

    // Se ver o centro moscando ele marca
    if(matriz[1][1] == -1) {
        *linha = 1;
        *coluna = 1;
        return;
    }

    //verificar as quinas
    if(matriz[0][0] == -1) {
        *linha = 0;
        *coluna = 0;
        return;
    }

    if(matriz[0][2] == -1) {
        *linha = 0;
        *coluna = 2;
        return;
    }

    if(matriz[2][0] == -1) {
        *linha = 2;
        *coluna = 0;
        return;
    }

    if(matriz[2][2] == -1) {
        *linha = 2;
        *coluna = 2;
        return;
    }
    
    //Por ultimo pega os meios
    if(matriz[0][1] == -1) {
        *linha = 0;
        *coluna = 1;
        return;
    }

    if(matriz[1][0] == -1) {
        *linha = 1;
        *coluna = 0;
        return;
    }

    if(matriz[2][1] == -1) {
        *linha = 2;
        *coluna = 1;
        return;
    }

    if(matriz[1][2] == -1) {
        *linha = 1;
        *coluna = 2;
        return;
    }
}

int verifica_vitoria(int matriz[3][3]){
    // 0 Jogador ganhou
    // 1 Computador ganhou
    // 2 Continua
    // 3 Empate

    //verificar se o jogador ganhou
    if( //Verificar as de cima
        (matriz[0][0] == 0 && matriz[0][1] == 0 && matriz[0][2] == 0) ||
        (matriz[1][0] == 0 && matriz[1][1] == 0 && matriz[1][2] == 0) ||
        (matriz[2][0] == 0 && matriz[2][1] == 0 && matriz[2][2] == 0) ||
        //Verificar as do lado    
        (matriz[0][0] == 0 && matriz[1][0] == 0 && matriz[2][0] == 0) ||
        (matriz[0][1] == 0 && matriz[1][1] == 0 && matriz[2][1] == 0) ||
        (matriz[0][2] == 0 && matriz[1][2] == 0 && matriz[2][2] == 0) ||
        //Verificar a diagonal
        (matriz[0][0] == 0 && matriz[1][1] == 0 && matriz[2][2] == 0) ||
        (matriz[2][0] == 0 && matriz[1][1] == 0 && matriz[0][2] == 0) 
    ) 
    {
        return 0;
    }

    if( //Verificar as de cima
        (matriz[0][0] == 1 && matriz[0][1] == 1 && matriz[0][2] == 1) ||
        (matriz[1][0] == 1 && matriz[1][1] == 1 && matriz[1][2] == 1) ||
        (matriz[2][0] == 1 && matriz[2][1] == 1 && matriz[2][2] == 1) ||
        //Verificar as do lado    
        (matriz[0][0] == 1 && matriz[1][0] == 1 && matriz[2][0] == 1) ||
        (matriz[0][1] == 1 && matriz[1][1] == 1 && matriz[2][1] == 1) ||
        (matriz[0][2] == 1 && matriz[1][2] == 1 && matriz[2][2] == 1) ||
        //Verificar a diagonal
        (matriz[0][0] == 1 && matriz[1][1] == 1 && matriz[2][2] == 1) ||
        (matriz[2][0] == 1 && matriz[1][1] == 1 && matriz[0][2] == 1) 
    ) 
    {
        return 1;
    }

    //Verificar se deu velha
    int achou = FALSE;
    int i, j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            //tem espaço livre
            if(matriz[i][j] == -1){
                achou = TRUE;
            }
        }
    }

    if(!achou) {
        return 3;
    }

    return 2;
}

int valida_jogada(int i, int j, int matriz[3][3]){
    if(i < 0 || i > 2){
        return FALSE;
    }

    if(j < 0 || j > 2){
        return FALSE;
    }

    if(matriz[i][j] != -1) {
        return FALSE;
    }

    return TRUE;
}


void imprime_tabuleiro(int matriz[3][3], int vencedor) {
    char simbolo_0 = (vencedor == 0) ? 'X' : 'O';
    char simbolo_1 = (vencedor == 1) ? 'X' : 'O';

    int i, j;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){

            if(matriz[i][j] == -1) {
                esc("   ");
            } else if(matriz[i][j] == 0) {
                printf(" %c ", simbolo_0);
            } else {
                if(matriz[i][j] == 1) {
                    printf(" %c ", simbolo_1);
                }
            }
            if(j <= 1) {
                esc(" | ");
            }
        }
        esc("\n");
        if(i <= 1) {
            printf("____ _____ ____\n");
        }
    }  
    esc("\n----------------------\n\n");
}

void inicializa_tabuleiro(int matriz[3][3]) {
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            matriz[i][j] = -1;
        }
    }
}


int par_impar() {
    int jogada_computador;
    int jogada_jogador;
    int escolha_jogador;

    //Se retornar 0 o jogador ganhou
    //Se retornar 1 o computador ganhou

    //Determinar se o usuario quer impar ou par
    do {
        ler_dado("Digite 0 para par e 1 para impar .: ", &escolha_jogador);
    } while(escolha_jogador != 0 && escolha_jogador != 1);

    //Jogada do computador
    esc("Par ou impar 1 a 10.\n");
    esc("O computador já esolheu o numero.\n");
    //Sorteia um numero de 1 a 10
    jogada_computador = (rand() % 10) + 1;

    //Jogada do usuario
    do {
        ler_dado("Digite um numero de 1 a 10 .: ", &jogada_jogador);
    } while (jogada_jogador < 1 || jogada_jogador > 10);

    //determinar quem ganhou
    if(((jogada_computador + jogada_jogador) % 2) == escolha_jogador) {
        esc("O jogador venceu o par ou impar!\n\n");
        return 0;
    } else {
        esc("O computador venceu o par ou impar!\n\n");
        return 1;
    }
}


void esc(char *msg) {
    printf("%s", msg);
}

int number_verify(char *n){
    int tamanho_numero = strlen(n);
    int quantos_errados = 0;

    if(tamanho_numero == 0) return 0;
    if(tamanho_numero == 1 && n[0] == '-') return 0; // '-'

    int inicio = (n[0] == '-' || n[0] == '+') ? 1 : 0;

    for(int i = inicio; n[i] != '\0'; i++){
        if(!isdigit(n[i])) { // 0 - 9
            quantos_errados++;
        } 
    }

    if(quantos_errados){ // 1 2 3 0
        return 0;
    } 

    return 1;    
}

void ler_dado(char *msg, int *var){
    char num[1000];

    if(!strcmp(msg, "") == 0) printf("%s", msg);

    scanf("%999s", num);

    while(!number_verify(num)){
        printf("Escreva so numeros .: ");
        scanf("%999s", num);
    }

    *var = atoi(num);
}