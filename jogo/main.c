#include "jogo.h"

int main() {
    int opcao;
    srand(time(NULL));

    // Lista principal de partidas registradas na memória durante a sessão
    Bloco *listaPartidasSessao = NULL;
    inicializa(&listaPartidasSessao);

    int idGlobal = 0;
    FILE *file = fopen("partidas_velha.txt", "r");
    if (file) {
        char linha[255 + 1];
        while (fgets(linha, sizeof(linha), file) != NULL) {
            idGlobal++;
        }
        fclose(file);
    }

    do {
        ler_dado("\n========== MENU JOGO DA VELHA ==========\n"
                 "1 - Jogar Partidas Jogo da Velha\n"
                 "2 - Salvar as partidas do Jogo da Velha\n"
                 "3 - Ranquear os usuarios do Jogo da Velha\n"
                 "4 - Sair do jogo da velha\n"
                 "Digite a opção .: ", &opcao);

        switch(opcao) {
            case 1: {
                char nome[49];
                int vitoriasUsuario = 0;
                int vitoriasComputador = 0;
                int empates = 0;
                int continuar = 1;
                int numPartida = 1;

                // Ler nome do jogador
                esc("\nDigite o nome do jogador => ");
                scanf(" %49s", nome);

            
                // Par ou Ímpar da partida inicial
                esc("\n--- Decisão de quem inicia (Par ou Ímpar) ---\n");
                int ganhou_jogador = par_impar(); // 0 = Jogador, 1 = Computador
                int vez = ganhou_jogador;

                // Ponteiro para registrar o início desta sessão de jogos
                Bloco *inicioSessao = NULL;

                while (continuar) {
                    // Incrementa o ID da partida
                    idGlobal++;

                    Partida partida;
                    partida.id = idGlobal;
                    strcpy(partida.nomeUsuario, nome);
                    strcpy(partida.nomeOponente, "Computador");
                    partida.jogadasUsuario = NULL;
                    partida.jogadasOponente = NULL;

                    int matriz[3][3];
                    inicializa_tabuleiro(matriz);

                    printf("\n--- PARTIDA N. %d (ID %d) ---\n", numPartida, partida.id);

                    int linha, coluna;

                    // Laço simples da partida
                    do {
                        imprime_tabuleiro(matriz, ganhou_jogador);

                        if (vez == 0) {
                            inteligencia_natural(matriz, &linha, &coluna);
                            atribui_matriz(matriz, linha, coluna, vez);
                            insereJogadaFinal(&(partida.jogadasUsuario), linha, coluna);
                        } else {
                            inteligencia_artificial(matriz, &linha, &coluna);
                            atribui_matriz(matriz, linha, coluna, vez);
                            insereJogadaFinal(&(partida.jogadasOponente), linha, coluna);
                        }

                        vez = !vez; // Inverte a vez
                    } while (verifica_vitoria(matriz) == 2);

                    imprime_tabuleiro(matriz, ganhou_jogador);

                    int resultado = verifica_vitoria(matriz);

                    // Atribui o resultado da partida
                    if (resultado == 0) {
                        printf("Vencedor: %s\n", partida.nomeUsuario);
                        strcpy(partida.resultado, partida.nomeUsuario);
                        vitoriasUsuario++;
                    } else if (resultado == 1) {
                        printf("Vencedor: Computador\n");
                        strcpy(partida.resultado, "Computador");
                        vitoriasComputador++;
                    } else {
                        printf("Empate!\n");
                        strcpy(partida.resultado, "Empate");
                        empates++;
                    }

                    // Inserir na lista encadeada da sessão
                    inserePartidaFinal(partida, &listaPartidasSessao);

                    // Alterna a ordem de quem inicia para a próxima partida
                    ganhou_jogador = !ganhou_jogador;
                    vez = ganhou_jogador;
                    numPartida++;

                    ler_dado("\nDeseja jogar mais uma partida? (1 - Sim / 0 - Nao) .: ", &continuar);
                }

                // Exibição do histórico das partidas jogadas
                printf("\n========== HISTÓRICO DE PARTIDAS ==========\n");
                imprimePartidas(listaPartidasSessao);

                // Vencedor geral do conjunto de partidas
                printf("\n========== RESULTADO GERAL ==========\n");
                printf("Placar: %s %d x %d Computador (Empates: %d)\n", nome, vitoriasUsuario, vitoriasComputador, empates);
                if (vitoriasUsuario > vitoriasComputador) {
                    printf("Vencedor Geral: %s!\n", nome);
                } else if (vitoriasComputador > vitoriasUsuario) {
                    printf("Vencedor Geral: Computador!\n");
                } else {
                    printf("Resultado Geral: Empate!\n");
                }
                
                break;
            }

            case 2: {
                // OPÇÃO 2: Salvar partidas no arquivo de texto
                if (listaPartidasSessao == NULL) {
                    printf("\n Nenhuma partida foi jogada na sessão atual para ser salva!\n");
                } else {
                    salvarDados(listaPartidasSessao);
                    liberarPartidas(&listaPartidasSessao);
                    printf("\n Partidas salvas com sucesso em 'partidas_velha.txt'!\n");
                }
                break;
            }

            case 3: {
                // OPÇÃO 3: Processar arquivo e exibir Ranking em ordem decrescente
                Ranking *listaRanking = NULL;
                inicializaRanking(&listaRanking);
                listaRanking = processarRankingArquivo("partidas_velha.txt", listaRanking);
                
                if (listaRanking == NULL) {
                    printf("\nNão há registros suficientes para exibir o ranking.\n");
                } else {
                    exibir_ranking(listaRanking);
                    liberarRanking(&listaRanking);
                }
                break;
            }

            case 4: {
                // OPÇÃO 4: Sair com critério de encerramento
                if (listaPartidasSessao != NULL) {
                    int opcaoSalvar;
                    ler_dado("\nDeseja salvar as partidas da sessão corrente no arquivo 'partidas_velha.txt' antes de sair?\n"
                             "(1 - Sim / 0 - Nao) .: ", &opcaoSalvar);

                    if (opcaoSalvar == 1) {
                        salvarDados(listaPartidasSessao);
                        printf("\nPartidas salvas com sucesso!\n");
                    }  
                    liberarPartidas(&listaPartidasSessao);
                    
                }
                printf("\nEncerrando o Jogo da Velha. Até logo!\n");
                break;
            }

            default:
                printf("\nOpção inválida! Digite um valor entre 1 e 4.\n");
                break;
        }

    } while (opcao != 4);

    return 0;
}