#include "jogo.h"

Ranking* cria_nodoRanking() {
    Ranking *novo = malloc(sizeof(Ranking));
    if (!novo) {
        printf("Problema de alocacao\n");
        exit(0);
    }
    novo->vitorias = 0;
    novo->prox = NULL;
    return novo;
}

Ranking* atualizar_ou_inserir(Ranking *list, const char *jogador) {
    if (strcmp(jogador, "Empate") == 0 || strcmp(jogador, "Computador") == 0) {
        return list;
    }

    Ranking *atual = list;

    while (atual != NULL) {
        if (strcmp(atual->nome, jogador) == 0) {
            atual->vitorias++; 
            return list;
        }
        atual = atual->prox;
    }

    Ranking *novo = cria_nodoRanking();
    strcpy(novo->nome, jogador);
    novo->vitorias = 1;
    novo->prox = list;
    list = novo;
    
    return list; 
}


Ranking* processarRankingArquivo(const char *arquivo, Ranking *list){
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return list; // Retorna a lista atual em vez de fechar o programa com exit
    }
    char linha[1000];

    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\r\n")] = 0; // Remove quebra de linha

        if (strlen(linha) == 0){
            continue;
        }

        // Separa todos os tokens da linha usando ';'
        char *token = strtok(linha, ";");
        char idPartida[50] = "";
        char nomeUsuario[50] = "";
        char ultimoToken[50] = "";

        if (token != NULL) {
            strcpy(idPartida, token);
        }

        int count = 0;
        while (token != NULL) {
            if (count == 1) { // O segundo campo é o nome do Usuário
                strcpy(nomeUsuario, token);
            }
            strcpy(ultimoToken, token); // Guarda o último token não vazio
            token = strtok(NULL, ";");
            count++;
        }

        // Se o resultado gravado for igual ao ID do usuário, substitui pelo nome do usuário
        if (strcmp(ultimoToken, idPartida) == 0 || strcmp(ultimoToken, "1") == 0) {
            if (strlen(nomeUsuario) > 0) {
                strcpy(ultimoToken, nomeUsuario);
            }
        }

        // Atualiza o ranking se o vencedor for um jogador válido
        if (strlen(ultimoToken) > 0) {
            list = atualizar_ou_inserir(list, ultimoToken);
        }
    }

    fclose(file);
    return list;
}

void ordena (Ranking **list){
 if(*list == NULL || (*list)->prox == NULL) {
    return;
 }
 int trocou;
 Ranking *aux;
 
 do {
    trocou = 0;
    aux = *list;

    while(aux->prox != NULL){
        if (aux->vitorias < aux->prox->vitorias) {
            int temp = aux->vitorias;
            aux->vitorias = aux->prox->vitorias;
            aux->prox->vitorias = temp;

            char temp_nome[50];
            strcpy(temp_nome, aux->nome);
            strcpy(aux->nome, aux->prox->nome);
            strcpy(aux->prox->nome, temp_nome);

            trocou = 1;
        }
        aux = aux->prox;
    }

}  while (trocou == 1);

}


void exibir_ranking(Ranking *list) {
    ordena(&list);
    printf("\n--- RANKING DE VITORIAS ---\n");
    Ranking *atual = list;
    while (atual != NULL) {
        printf("Jogador: %s | Vitorias: %d\n", atual->nome, atual->vitorias);
        atual = atual->prox;
    }
}
