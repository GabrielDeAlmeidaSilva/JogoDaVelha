#include "jogo.h"

void inicializaRanking(Ranking **list) {
    *list = NULL;
}

Ranking* cria_nodoRanking() {
    Ranking *novo = malloc(sizeof(Ranking));
    if (!novo) {
        printf("Problema de alocacao\n");
        return NULL;
    }
    novo->vitorias = 0;
    novo->prox = NULL;
    return novo;
}
Ranking* garantir_jogador(Ranking *list, const char *jogador) {
    if (strcmp(jogador, "Empate") == 0 || strcmp(jogador, "Computador") == 0) {
        return list;
    }

    Ranking *atual = list;
    while (atual != NULL) {
        if (strcmp(atual->nome, jogador) == 0) {
            return list; 
        }
        atual = atual->prox;
    }

    Ranking *novo = cria_nodoRanking();
    strcpy(novo->nome, jogador);
    novo->vitorias = 0;
    novo->prox = list;
    
    return novo;
}

void incrementar_vitoria(Ranking *list, const char *jogador) {
    if (strcmp(jogador, "Empate") == 0 || strcmp(jogador, "Computador") == 0) {
        return;
    }

    Ranking *atual = list;
    while (atual != NULL) {
        if (strcmp(atual->nome, jogador) == 0) {
            atual->vitorias++; 
            return; 
        }
        atual = atual->prox;
    }
}

Ranking* processarRankingArquivo(const char *arquivo, Ranking *list) {
    FILE *file = fopen(arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return list;
    }
    char linha[1000];

    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\r\n")] = 0;

        if (strlen(linha) == 0) {
            continue;
        }

        
        char linha_copia[1000];
        strcpy(linha_copia, linha);
        char *token = strtok(linha_copia, ";"); // Pula o ID
        if (token != NULL) {
            char *nome_jogador = strtok(NULL, ";"); // Pega o nome do jogador
            if (nome_jogador != NULL && strlen(nome_jogador) > 0) {
                list = garantir_jogador(list, nome_jogador);
            }
        }

        char *vencedor = strrchr(linha, ';');
        if (vencedor != NULL) {
            vencedor++; 
            incrementar_vitoria(list, vencedor);
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


void liberarRanking(Ranking **list) {
    if (list == NULL) return;
    
    Ranking *atual = *list;
    while (atual != NULL) {
        Ranking *temp = atual;
        atual = atual->prox;
      
        free(temp);
    }
    *list = NULL; 
}