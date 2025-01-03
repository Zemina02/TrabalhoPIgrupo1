//atualizada apra mostrar a data de inicio no clube
//Funçao que mostra e escolhe a equipa
int mostrarEquipas(char treinador[NUM_EQUIPAS][15], dadosdasequipas equipas[NUM_EQUIPAS], jogadores jogadores[NUM_EQUIPAS][NUM_JOGADORES], int eCount)
{
    // Mostra a Lista das Equipas
    printf("Selecione uma equipa:\n");
    for (int i = 0; i < eCount; i++) {
        printf("%d. %s\n", i + 1, equipas[i].equipa);
    }

    // Pede ao utilizador para escolher e Valida a seleção
    int escolha = 0;
    while (escolha < 1 || escolha > eCount) {
        printf("Digite o numero da equipa que deseja selecionar: ");
        scanf("%d", &escolha);

        if (escolha < 1 || escolha > eCount) {
            printf("Selecao invalida, escolha outra vez.\n");
        }
    }

    // Mostra a equipa que o utilizador escolheu
    int SelecionaIndice = escolha - 1; // Ajustar para indice baseado em zero
    printf("\nDetalhes da equipa selecionada:\n");
    printf("Você escolheu a equipa: %s\n", equipas[SelecionaIndice].equipa);
    printf("Qual o nome do treinador(o teu)?\n");
    scanf("%s", treinador[SelecionaIndice]);
    printf("Treinador: %s\n", treinador[SelecionaIndice]);
    printf("\nJogadores:\n");
    printf("%-30s %-10s %-15s %-15s\n", "Nome", "Numero", "Posicaoo", "Data de Início"); // cabeçalho
    printf("---------------------------------------------------------------------------\n");

    for (int i = 0; i < NUM_JOGADORES; i++) {
        printf("%-30s %-10d %-15s %02d/%02d/%d\n",
            jogadores[SelecionaIndice][i].nome,
            jogadores[SelecionaIndice][i].numero,
            jogadores[SelecionaIndice][i].posicaojogador,
            jogadores[SelecionaIndice][i].datadoIniciodoContrato[2], // Dia
            jogadores[SelecionaIndice][i].datadoIniciodoContrato[1], // Mês
            jogadores[SelecionaIndice][i].datadoIniciodoContrato[0]); // Ano
    }

    return SelecionaIndice; // Retorna o índice da equipa selecionada
}






//isto é uma atualização de uma parte do codigo para a main
 // Ler 20 jogadores
        for (int j = 0; j < NUM_JOGADORES; j++) {
            if (fgets(line, sizeof(line), equipas) != NULL) {
                sscanf(line, "%[^;];%d;%[^;];%d", jogadoresPorEquipa[equipaCount][j].nome, &jogadoresPorEquipa[equipaCount][j].numero, jogadoresPorEquipa[equipaCount][j].posicaojogador, &jogadoresPorEquipa[equipaCount][j].forca);

                // Gera um valor aleatório para o vencimento de cada jogador
                jogadoresPorEquipa[equipaCount][j].vencimento = (rand() % (3000000 - 700000 + 1)) + 700000; // Um valor random entre 700000 e 3000000

                // Gera um ano aleatório entre 1999 e 2012
                jogadoresPorEquipa[equipaCount][j].datadoIniciodoContrato[0] = rand() % (2012 - 1999 + 1) + 1999; // Ano
                jogadoresPorEquipa[equipaCount][j].datadoIniciodoContrato[1] = rand() % 12 + 1; // Mês (1 a 12)
                jogadoresPorEquipa[equipaCount][j].datadoIniciodoContrato[2] = rand() % 31 + 1; // Dia (1 a 31)
            }
        }
        equipaCount++;
