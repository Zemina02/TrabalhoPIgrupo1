// Função para resetar as posições dos jogadores
void resetarPosicoes(jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES]) {
    for (int i = 0; i < NUM_EQUIPAS; i++) {
        for (int j = 0; j < NUM_JOGADORES; j++) {
            // Armazena a posição atual em posicaoIdeal antes de resetar
            strcpy(jogadoresPorEquipa[i][j].posicaoIdeal, jogadoresPorEquipa[i][j].posicaojogador);
            strcpy(jogadoresPorEquipa[i][j].posicaojogador, ""); // Reseta a posição para uma string vazia
        }
    }
}

// Função auxiliar para posicionar jogadores
void posicionarJogadores(jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES], int equipaSelecionada, const char* posicao, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Escolha o jogador para %s %d:\n", posicao, i + 1);

        // Mostra os jogadores disponíveis para a posição
        printf("\nJogadores disponíveis:\n");
        printf("%-30s %-15s\n", "Nome", "Posição Ideal"); // Alterado para mostrar "Posição Ideal"
        printf("-----------------------------------------------\n");
        for (int j = 0; j < NUM_JOGADORES; j++) {
            // Exibe apenas jogadores que não estão posicionados
            if (strcmp(jogadoresPorEquipa[equipaSelecionada][j].posicaojogador, "") == 0) {
                printf("%-30s %-15s\n", jogadoresPorEquipa[equipaSelecionada][j].nome, jogadoresPorEquipa[equipaSelecionada][j].posicaoIdeal); // Exibe a posição ideal
            }
        }

        // Mensagem para o utilizador
        printf("\nNome: "); // Agora aparece após a tabela

        char nomeJogador[30];
        scanf(" %[^\n]", nomeJogador); // Lê o nome do jogador

        // Extrai o primeiro nome
        char primeiroNome[30];
        sscanf(nomeJogador, "%s", primeiroNome); // Pega apenas o primeiro nome

        // Converte o primeiro nome para minúsculas
        for (int k = 0; primeiroNome[k]; k++) {
            primeiroNome[k] = tolower(primeiroNome[k]);
        }

        bool encontrado = false;
        for (int j = 0; j < NUM_JOGADORES; j++) {
            // Extrai o primeiro nome do jogador na lista e converte para minúsculas
            char nomeDoJogador[30];
            sscanf(jogadoresPorEquipa[equipaSelecionada][j].nome, "%s", nomeDoJogador);
            for (int k = 0; nomeDoJogador[k]; k++) {
                nomeDoJogador[k] = tolower(nomeDoJogador[k]);
            }

            if (strcmp(nomeDoJogador, primeiroNome) == 0) {
                // Verifica se o jogador já foi posicionado
                if (strcmp(jogadoresPorEquipa[equipaSelecionada][j].posicaojogador, "") == 0) {
                    strcpy(jogadoresPorEquipa[equipaSelecionada][j].posicaojogador, posicao);
                    encontrado = true;
                }
                else {
                    printf("Jogador %s já está posicionado. Tente novamente.\n", primeiroNome);
                    encontrado = true; // O jogador foi encontrado, mas já está posicionado
                }
                break;
            }
        }
        if (!encontrado) {
            printf("Jogador %s não encontrado. Tente novamente.\n", primeiroNome);
            i--; // Decrementa o contador para permitir nova tentativa
        }
    }
}

int escolherTatica(jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES], dadosdasequipas equipasEDados[NUM_EQUIPAS], int equipaSelecionada) {
    // Resetar as posições dos jogadores
    resetarPosicoes(jogadoresPorEquipa);

    int taticasEscolhida;
    printf("\nEscolha a tática:\n");
    printf("\n1. 4-3-3\n");
    printf("\n2. 4-4-2\n");
    printf("\n3. 5-3-2\n");
    printf("\n4. 4-5-1\n");
    printf("\nDigite o número da tática que deseja escolher: ");

    // Verifica se a entrada é um número válido
    if (scanf("%d", &taticasEscolhida) != 1) {
        // Limpa o buffer de entrada
        while (getchar() != '\n');
        printf("\nCaracter inválido. Por favor, insira um número.\n");
        return -1; // Retorna -1 para indicar erro
    }

    int defensores = 0, medios = 0, avancados = 0;

    // Definindo as posições com base na tática escolhida
    switch (taticasEscolhida) {
    case 1: // 4-3-3
        defensores = 4; medios = 3; avancados = 3;
        break;
    case 2: // 4-4-2
        defensores = 4; medios = 4; avancados = 2;
        break;
    case 3: // 5-3-2
        defensores = 5; medios = 3; avancados = 2;
        break;
    case 4: // 4-5-1
        defensores = 4; medios = 5; avancados = 1;
        break;
    default:
        printf("Tática inválida. Por favor, escolha 1, 2, 3 ou 4.\n");
        return -1; // Retorna -1 para indicar erro
    }

    // Mostra os jogadores disponíveis e suas posições ideais
    printf("\nJogadores disponíveis para posicionamento:\n");
    printf("%-30s %-15s\n", "Nome", "Posição Ideal"); // cabeçalho alterado
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < NUM_JOGADORES; i++) {
        // Exibe apenas jogadores que não estão posicionados
        if (strcmp(jogadoresPorEquipa[equipaSelecionada][i].posicaojogador, "") == 0) {
            printf("%-30s %-15s\n", jogadoresPorEquipa[equipaSelecionada][i].nome, jogadoresPorEquipa[equipaSelecionada][i].posicaoIdeal); // Exibe a posição ideal
        }
    }

    // Posiciona os jogadores de acordo com a tática escolhida
    printf("Formação escolhida: %d-%d-%d\n", defensores, medios, avancados);
    posicionarJogadores(jogadoresPorEquipa, equipaSelecionada, "Defesa", defensores);
    posicionarJogadores(jogadoresPorEquipa, equipaSelecionada, "Medio", medios);
    posicionarJogadores(jogadoresPorEquipa, equipaSelecionada, "Avancado", avancados);

    // Calcular e exibir o poder de ataque e defesa
    int poderAtaque = calcularPoderAtaque(jogadoresPorEquipa[equipaSelecionada]);
    int poderDefesa = calcularPoderDefesa(jogadoresPorEquipa[equipaSelecionada]);

    printf("\nPoder de Ataque da equipa %s: %d\n", equipasEDados[equipaSelecionada].equipa, poderAtaque);
    printf("Poder de Defesa da equipa %s: %d\n", equipasEDados[equipaSelecionada].equipa, poderDefesa);

    return 0; // Retorna 0 para indicar sucesso
}

//na main
    // Chama a função para mostrar as equipas e captura o índice da equipa selecionada
    int equipaSelecionada = mostrarEquipas(treinador, equipasEDados, jogadoresPorEquipa, NUM_EQUIPAS);

    // Criar as jornadas automaticamente após a seleção da equipa
    printf("Pressione Enter para criar o calendário de jogos...\n");
    getchar(); // Espera pelo input do utilizador
    getchar(); // Captura o Enter
    limparTela();


    // Criar as jornadas automaticamente após a seleção da equipa
    int** primeirosjogos = criarCalendario(equipasEDados);
    printf("Primeira Jornada-----------------------------------------\n");

    int** segundojogos = criarCalendario(equipasEDados);
    printf("Segunda Jornada------------------------------------------\n");

    int** terceirojogos = criarCalendario(equipasEDados);
    printf("Terceira Jornada-----------------------------------------\n");


    // Escolher a tática antes de simular o jogo
    int resultadoEscolha;
    do {
        resultadoEscolha = escolherTatica(jogadoresPorEquipa, equipasEDados, equipaSelecionada);
        if (resultadoEscolha != 0) {
            printf("Caracter inválido. Tente novamente.\n");
        }
    } while (resultadoEscolha != 0); // Continua pedindo até que a escolha seja válida
