# Jogo da Velha em C utilizando lista encadeada 

Este projeto consiste numa implementação do **Jogo da Velha** (Tic-Tac-Toe) em linguagem C, desenvolvida com recurso a estruturas de dados dinâmicas (listas simplesmente ligadas), gestão de memória, inteligência artificial preventiva e persistência de dados em ficheiro de texto.

---

## 🚀 Funcionalidades

- **Modo de Jogo contra o Computador (IA):**
  - Decisão inicial de quem começa através de um jogo de *Par ou Ímpar*.
  - Inteligência artificial que analisa jogadas para vencer, bloquear o adversário, ocupar o centro e cantos do tabuleiro.
  - Alternância automática de quem inicia cada partida seguinte numa mesma sessão de jogo.
- **Histórico e Registo Dinâmico:**
  - Armazenamento de partidas e jogadas individuais recorrendo a listas dinâmicas encadeadas (`Bloco`, `Partida` e `Jogada`).
  - Apresentação do histórico detalhado e do resultado geral da sessão de jogos no ecrã.
- **Persistência em Ficheiro:**
  - Gravação do histórico de partidas no ficheiro `partidas_velha.txt`.
  - Confirmação e opção automática de gravação ao encerrar o programa caso existam dados pendentes.
- **Sistema de Ranking:**
  - Leitura e processamento dos registos armazenados no ficheiro `partidas_velha.txt`.
  - Contagem acumulada do número de vitórias por utilizador.
  - Ordenação decrescente do ranking através do algoritmo Bubble Sort aplicado à lista ligada.
  - Libertação e gestão rigorosa de memória alocada dinamicamente com `free`.

---

## 📁 Estrutura do Projeto

| Ficheiro | Descrição |
| :--- | :--- |
| **`jogo.h`** | Cabeçalho principal com as definições de estruturas (`Jogada`, `Partida`, `Bloco`, `Ranking`) e protótipos de funções. |
| **`main.c`** | Ponto de entrada do programa com a gestão do menu interativo e o fluxo principal de execução. |
| **`jogo.c`** | Implementação da lógica do tabuleiro, validações de jogadas, tomada de decisão da IA e jogo de Par ou Ímpar. |
| **`dados.c`** | Funções de manipulação de listas ligadas de partidas e jogadas, formatação de dados, gravação em ficheiro e libertação de memória. |
| **`ranking.c`** | Parsing do ficheiro de dados, contagem e atualização de vitórias, ordenação e exibição do ranking. |

---

##  Estruturas de Dados Utilizadas

- **`Jogada`:** Lista ligada simples que armazena as coordenadas `(linha, coluna)` de cada jogada efetuada.
- **`Partida`:** Registo contendo o ID da partida, o nome do utilizador, o oponente, ponteiros para as jogadas e o resultado final.
- **`Bloco`:** Nodo da lista ligada de partidas armazenadas na memória durante a sessão.
- **`Ranking`:** Lista encadeada utilizada para registar o nome do utilizador e a respetiva contagem de vitórias.

---

## ⚙️ Compilação e Execução

Para compilar o projeto utilizando o `gcc`, execute o seguinte comando no terminal:

```bash
gcc dados.c jogo.c main.c ranking.c -o programa
```

Para executar a aplicação:

```bash
./programa
```

---


## 📋 Menu Principal

1. **Jogar Partidas Jogo da Velha:** Inicia uma nova série de partidas contra o computador.
2. **Salvar as partidas do Jogo da Velha:** Escreve as partidas da sessão atual no ficheiro `partidas_velha.txt`.
3. **Ranquear os usuarios do Jogo da Velha:** Lê o ficheiro de dados e apresenta o ranking de vitórias ordenado.
4. **Sair do jogo da velha:** Encerra a aplicação, permitindo guardar partidas não salvas antes de sair.
