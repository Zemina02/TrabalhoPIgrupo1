#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    int ataque;
    int medio;
    int defesa;
    int guarda;
} posicao;

void calcularEstatisticas(char* posicaojogador, posicao* stats) {
    srand(time(NULL));
    int numeroAleatorioexbaixo = (rand() % 10) + 1;
    int numeroAleatoriobaixo = (rand() % 21) + 20;
    int numeroAleatorioMedio = (rand() % 21) + 40;
    int numeroAleatorioAlto = (rand() % 21) + 60;
    int numeroAleatorioExAlto = (rand() % 20) + 80;

    if (strcmp(posicaojogador, "Guarda-Redes") == 0) {
        stats->ataque = numeroAleatorioexbaixo;
        stats->medio = numeroAleatoriobaixo;
        stats->defesa = numeroAleatorioMedio;
        stats->guarda = numeroAleatorioExAlto;
    }
    else if (strcmp(posicaojogador, "Defesa") == 0) {
        stats->ataque = numeroAleatoriobaixo;
        stats->medio = numeroAleatorioMedio;
        stats->defesa = numeroAleatorioExAlto;
        stats->guarda = numeroAleatorioMedio;
    }
    else if (strcmp(posicaojogador, "Medio") == 0) {
        stats->ataque = numeroAleatorioAlto;
        stats->medio = numeroAleatorioExAlto;
        stats->defesa = numeroAleatorioAlto;
        stats->guarda = numeroAleatoriobaixo;
    }
    else if (strcmp(posicaojogador, "Avancado") == 0) {
        stats->ataque = numeroAleatorioExAlto;
        stats->medio = numeroAleatorioAlto;
        stats->defesa = numeroAleatoriobaixo;
        stats->guarda = numeroAleatorioexbaixo;
    }
}
// Ler e criar ficheiro
int main(void) {
    FILE* ficheiroEntrada = fopen("Equipas.txt", "r");
    if (ficheiroEntrada == NULL) {
        printf("Erro ao abrir o ficheiro de entrada!\n");
        return 1;
    }

    FILE* ficheiroSaida = fopen("estatisticas_jogador.txt", "w");
    if (ficheiroSaida == NULL) {
        printf("Erro ao abrir o ficheiro de saída!\n");
        fclose(ficheiroEntrada);
        return 1;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), ficheiroEntrada)) {
        if (strchr(linha, ';') == NULL) {
            fprintf(ficheiroSaida, "%s", linha);
            continue;
        }

        char* nome = strtok(linha, ";");
        char* numero = strtok(NULL, ";");
        char* posicaojogador = strtok(NULL, ";");
        char* ativo = strtok(NULL, "\n");

        posicao stats;
        calcularEstatisticas(posicaojogador, &stats);

        fprintf(ficheiroSaida, "%s;%s;%s;%d;%d;%d;%d;%s\n", nome, numero, posicaojogador, stats.ataque, stats.medio, stats.defesa, stats.guarda, ativo);
    }

    fclose(ficheiroEntrada);
    fclose(ficheiroSaida);

    return 0;
}


