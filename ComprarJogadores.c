//Atualizado para no fim de cada partida mostra os fundos da equipa atualizados

void atualizarFundosPorResultado(int equipaIndex, dadosdasequipas equipasEDados[NUM_EQUIPAS], int resultado) {
    float ganho;

    // Exibe os fundos atuais antes da atualização
    printf("Fundos atuais da equipa %s: %.2f\n", equipasEDados[equipaIndex].equipa, equipasEDados[equipaIndex].fundosdoclube);

    // Definir os ganhos com base no resultado
    if (resultado == 1) { // Vitória
        ganho = 500000; // Ganho por vitória
        printf("A equipa %s ganhou! Recebeu %.2f.\n", equipasEDados[equipaIndex].equipa, ganho);
    }
    else if (resultado == 0) { // Empate
        ganho = 250000; // Ganho por empate
        printf("A equipa %s empatou! Recebeu %.2f.\n", equipasEDados[equipaIndex].equipa, ganho);
    }
    else { // Derrota
        ganho = 100000; // Ganho por derrota
        printf("A equipa %s perdeu! Recebeu %.2f.\n", equipasEDados[equipaIndex].equipa, ganho);
    }

    // Atualiza os fundos da equipa
    equipasEDados[equipaIndex].fundosdoclube += ganho;

    // Exibe os fundos após a atualização
    printf("Fundos atualizados da equipa %s: %.2f\n", equipasEDados[equipaIndex].equipa, equipasEDados[equipaIndex].fundosdoclube);
}


//Função para comprar jogadores

void comprarJogadores(dadosdasequipas equipasEDados[NUM_EQUIPAS], jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES], int equipaSelecionada) {
    int jogadoresComprados = 0;
    bool jogadoresCompradosDeEquipa[NUM_EQUIPAS] = { false }; // Array para rastrear se um jogador foi comprado de cada equipe

    while (jogadoresComprados < 3) {
        printf("\nEscolha uma equipa para comprar um jogador (ou digite 0 para sair):\n");
        for (int i = 0; i < NUM_EQUIPAS; i++) {
            if (i != equipaSelecionada && !jogadoresCompradosDeEquipa[i]) { // Exclui a própria equipe e equipes de onde já comprou
                printf("%d. %s\n", i + 1, equipasEDados[i].equipa);
            }
        }

        int escolhaEquipa;
        printf("Digite o número da equipa que deseja comprar um jogador (0 para sair): ");

        // Verifica se a entrada é um número válido
        while (scanf("%d", &escolhaEquipa) != 1) {
            printf("Caracter inválido. Por favor, insira um número: ");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }

        if (escolhaEquipa == 0) {
            break; // Sai do loop se o usuário escolher 0
        }

        // Valida a escolha da equipe
        if (escolhaEquipa < 1 || escolhaEquipa > NUM_EQUIPAS || escolhaEquipa - 1 == equipaSelecionada || jogadoresCompradosDeEquipa[escolhaEquipa - 1]) {
            printf("Seleção inválida. Tente novamente.\n");
            continue; // Volta ao início do loop
        }

        int equipaIndex = escolhaEquipa - 1; // Ajusta para índice baseado em zero
        printf("\nJogadores disponíveis na equipa %s:\n", equipasEDados[equipaIndex].equipa);
        printf("%-30s %-10s %-15s %-10s\n", "Nome", "Número", "Posição Ideal", "Força"); // cabeçalho
        printf("----------------------------------------------------------------\n");

        bool jogadorDisponivel = false;
        for (int j = 0; j < NUM_JOGADORES; j++) {
            if (strcmp(jogadoresPorEquipa[equipaIndex][j].posicaojogador, "") != 0) { // Exibe apenas jogadores que estão na equipe
                printf("%-30s %-10d %-15s %-10d\n", jogadoresPorEquipa[equipaIndex][j].nome, jogadoresPorEquipa[equipaIndex][j].numero, jogadoresPorEquipa[equipaIndex][j].posicaojogador, jogadoresPorEquipa[equipaIndex][j].forca);
                jogadorDisponivel = true;
            }
        }

        if (!jogadorDisponivel) {
            printf("Não há jogadores disponíveis na equipa %s.\n", equipasEDados[equipaIndex].equipa);
            continue; // Volta ao início do loop
        }

        while (true) { // Loop para tentar encontrar o jogador
            printf("\nEscolha um jogador para comprar (digite o nome completo): ");
            char nomeJogador[30];
            scanf(" %[^\n]", nomeJogador); // Lê o nome completo do jogador

            bool jogadorEncontrado = false;
            for (int j = 0; j < NUM_JOGADORES; j++) {
                if (strcmp(jogadoresPorEquipa[equipaIndex][j].nome, nomeJogador) == 0) { // Verifica se o nome completo corresponde
                    jogadorEncontrado = true;
                    printf("\nJogador encontrado: %s, Número: %d, Salário: %.2f, Força: %d\n",
                        jogadoresPorEquipa[equipaIndex][j].nome,
                        jogadoresPorEquipa[equipaIndex][j].numero,
                        jogadoresPorEquipa[equipaIndex][j].vencimento,
                        jogadoresPorEquipa[equipaIndex][j].forca);

                    // Calcula o valor da transferência
                    int mesesRestantes = jogadoresPorEquipa[equipaIndex][j].anosdoContrato * 12; // Supondo que anosdoContrato é o número de anos restantes
                    float valorTransferencia = jogadoresPorEquipa[equipaIndex][j].vencimento * 5 * mesesRestantes;

                    // Verifica se a equipa compradora tem fundos suficientes
                    if (equipasEDados[equipaSelecionada].fundosdoclube >= valorTransferencia) {
                        // Realiza a compra
                        equipasEDados[equipaSelecionada].fundosdoclube -= valorTransferencia; // Deduz o valor da transferência
                        jogadoresPorEquipa[equipaSelecionada][jogadoresComprados] = jogadoresPorEquipa[equipaIndex][j]; // Adiciona o jogador à equipa compradora
                        jogadoresPorEquipa[equipaIndex][j].posicaojogador[0] = '\0'; // Remove o jogador da equipa original
                        jogadoresPorEquipa[equipaSelecionada][jogadoresComprados].vencimento *= 1.5; // Aumenta o salário do jogador
                        jogadoresCompradosDeEquipa[equipaIndex] = true; // Marca que um jogador foi comprado dessa equipe
                        jogadoresComprados++;

                        printf("Jogador %s comprado com sucesso! Novo salário: %.2f\n", jogadoresPorEquipa[equipaSelecionada][jogadoresComprados - 1].nome, jogadoresPorEquipa[equipaSelecionada][jogadoresComprados - 1].vencimento);
                    }
                    else {
                        printf("Fundos insuficientes para comprar o jogador %s.\n", jogadoresPorEquipa[equipaIndex][j].nome);
                    }
                    break; // Sai do loop após encontrar e processar o jogador
                }
            }

            if (!jogadorEncontrado) {
                printf("Nenhum jogador encontrado com o nome completo %s. Tente novamente.\n", nomeJogador);
                // Retorna ao início do loop para escolher a equipe novamente
                break; // Sai do loop de busca de jogador
            }
        }

        // Pergunta se o utilizador deseja continuar a procurar
        if (jogadoresComprados < 3) {
            char continuar;
            printf("Deseja continuar a procurar jogadores? (s/n): ");
            scanf(" %c", &continuar);
            if (continuar != 's' && continuar != 'S') {
                break; // Sai do loop se o utilizador não quiser continuar
            }
        }
    }
}


//Main atualizada (falta por a parte para as taticas)

int main()
{
    setlocale(LC_ALL, "Portuguese");

    // cria treinadores para cada equipa
    char treinador[NUM_EQUIPAS][15];
    // cria dados para 18 equipas e jogadores para cada
    dadosdasequipas equipasEDados[NUM_EQUIPAS];
    jogadores jogadoresPorEquipa[NUM_EQUIPAS][NUM_JOGADORES]; // 20 jogadores por equipa

    // Abre o ficheiro "Equipas.txt"
    FILE* equipas = fopen("Equipas.txt", "r");
    if (equipas == NULL) {
        printf("Não foi possível abrir o ficheiro.\n");
        return 1;
    }

    // Lê as linhas do arquivo e guarda no local correto
    int equipaCount = 0;
    char line[50];

    // Ler treinador e equipa
    while (equipaCount < NUM_EQUIPAS && fgets(line, sizeof(line), equipas) != NULL) {
        sscanf(line, "%[^\n]", treinador[equipaCount]);

        if (fgets(line, sizeof(line), equipas) != NULL) {
            sscanf(line, "%[^\n]", equipasEDados[equipaCount].equipa);
        }

        equipasEDados[equipaCount].fundosdoclube = 100000000.0; // 100 milhões
        equipasEDados[equipaCount].despesasdoestadio = 100000.0; // 100 mil

        // Ler 20 jogadores
        for (int j = 0; j < NUM_JOGADORES; j++) {
            if (fgets(line, sizeof(line), equipas) != NULL) {
                sscanf(line, "%[^;];%d;%[^;];%d", jogadoresPorEquipa[equipaCount][j].nome, &jogadoresPorEquipa[equipaCount][j].numero, jogadoresPorEquipa[equipaCount][j].posicaojogador, &jogadoresPorEquipa[equipaCount][j].forca);

                //gera um valor aleatorio para o vencimento de cada jogador
                jogadoresPorEquipa[equipaCount][j].vencimento = (rand() % (3000000 - 700000 + 1)) + 700000; // Um valor random entre 700000 e 3000000
            }
        }
        equipaCount++;
    }

    fclose(equipas);

    // Chama a função para mostrar as equipas e captura o índice da equipa selecionada
    int equipaSelecionada = mostrarEquipas(treinador, equipasEDados, jogadoresPorEquipa, NUM_EQUIPAS);

    char continuar;
    int contadorCalendarios = 0; // Contador para os calendários criados

    do {
        criarCalendario(equipasEDados);
        contadorCalendarios++; // Incrementa o contador

        // Verifica se 5 calendários foram criados
        if (contadorCalendarios % 5 == 0) {
            // Pergunta se o usuário deseja comprar jogadores após cada 5 calendários
            printf("\nDeseja comprar jogadores? (s/n): ");
            scanf(" %c", &continuar);
            if (continuar == 's' || continuar == 'S') {
                comprarJogadores(equipasEDados, jogadoresPorEquipa, equipaSelecionada);
            }
        }

        // Simula o jogo da equipa
        printf("\nSimular o jogo da tua equipa %s? (s/n): ", equipasEDados[equipaSelecionada].equipa);
        scanf(" %c", &continuar);
        if (continuar == 's' || continuar == 'S') {
            simularJogo(equipasEDados, jogadoresPorEquipa, equipaSelecionada);
        }

        printf("\nDeseja gerar um novo calendário? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    return 0;
}
