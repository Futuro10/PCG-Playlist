#include <stdio.h> // Biblioteca padr�o para entrada e sa�da (ex: printf, scanf)
#include <string.h> // Biblioteca para manipular strings (ex: strcpy, strcmp)

#define MAX_GENEROS 6 // N�mero m�ximo de g�neros musicais
#define MAX_MUSICAS 100 // N�mero m�ximo de m�sicas que podem ser armazenadas

// Fun��o para trocar dois elementos (nomes e dura��es) de lugar
void swap(char *str1, char *str2, int *dur1, int *dur2) {
    char temp_str[100]; // Vari�vel tempor�ria para guardar um nome ou g�nero
    int temp_dur; // Vari�vel tempor�ria para guardar a dura��o

    // Troca os textos (nomes ou g�neros)
    strcpy(temp_str, str1);
    strcpy(str1, str2);
    strcpy(str2, temp_str);

     // Troca as dura��es
    temp_dur = *dur1;
    *dur1 = *dur2;
    *dur2 = temp_dur;
}

// Fun��o para ordenar a playlist por ordem alfab�tica dos nomes das m�sicas
void sort_playlist(char nomes[][100], char generos[][50], int duracoes[], int quantidade) {
    int i, j;
    for (i = 0; i < quantidade - 1; i++) {
        for (j = 0; j < quantidade - i - 1; j++) {
            // Compara nomes e troca se estiverem fora de ordem
            if (strcmp(nomes[j], nomes[j + 1]) > 0) {
                swap(nomes[j], nomes[j + 1], &duracoes[j], &duracoes[j + 1]);
                swap(generos[j], generos[j + 1], &duracoes[j], &duracoes[j + 1]);
            }
        }
    }
}

int main() {
    char nomes[MAX_MUSICAS][100]; // Armazena os nomes das m�sicas
    char generos[MAX_MUSICAS][50]; // Armazena os g�neros das m�sicas
    int duracoes[MAX_MUSICAS]; // Armazena a dura��o das m�sicas (em segundos)
    int quantidade = 0; // Conta quantas m�sicas j� foram adicionadas
    int opcao; // Guarda a op��o escolhida no menu
    int i, j; // Contadores para loops

    char generos_preestabelecidos[MAX_GENEROS][50] = {
        "Eletronica",
        "Funk",
        "Rock",
        "Jazz",
        "Pop",
        "Hip-Hop"
    };

    do {
        // Mostra as op��es do menu
        printf("\n----- Menu -----\n");
        printf("1. Adicionar musica\n");
        printf("2. Listar musicas\n");
        printf("3. Montar playlist por tempo maximo\n");
        printf("4. Montar playlist por genero\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao); // L� a escolha do usu�rio

        if (opcao == 1) {
            if (quantidade >= MAX_MUSICAS) { // Verifica se j� chegou ao limite
                printf("A playlist esta cheia!\n");
            } else {
                printf("Digite o nome da musica: ");
                scanf(" %[^\n]s", nomes[quantidade]); // L� o nome da m�sica com espa�os

                printf("Escolha o genero:\n");
                for (i = 0; i < MAX_GENEROS; i++) {
                    printf("%d. %s\n", i + 1, generos_preestabelecidos[i]);
                }
                printf("Escolha uma opcao de genero (1-%d): ", MAX_GENEROS);
                int genero_opcao;
                scanf("%d", &genero_opcao);

                if (genero_opcao >= 1 && genero_opcao <= MAX_GENEROS) {
                    // Copia o g�nero escolhido para a lista
                    strcpy(generos[quantidade], generos_preestabelecidos[genero_opcao - 1]);
                } else {
                    // Se o usu�rio digitar um n�mero inv�lido
                    printf("Opcao de genero invalida. Genero nao atribuido.\n");
                    strcpy(generos[quantidade], "Indefinido");
                }

                printf("Digite a duracao (em segundos): ");
                scanf("%d", &duracoes[quantidade]); // L� a dura��o

                quantidade++; // Adiciona 1 � quantidade total de m�sicas
                printf("Musica adicionada com sucesso!\n");
            }

        } else if (opcao == 2) {
            if (quantidade == 0) {
                printf("A playlist esta vazia.\n");
            } else {
                sort_playlist(nomes, generos, duracoes, quantidade); // Ordena m�sicas por nome

                printf("\n--- Playlist ---\n");
                for (i = 0; i < quantidade; i++) {
                    printf("Musica %d:\n", i + 1);
                    printf("Nome: %s\n", nomes[i]);
                    printf("Genero: %s\n", generos[i]);
                    printf("Duracao: %d minutos\n\n", duracoes[i] / 60); // Converte segundos em minutos
                }
            }

        } else if (opcao == 3) {
            int tempo_maximo_minutos;
            printf("Digite o tempo maximo da playlist (em minutos): ");
            scanf("%d", &tempo_maximo_minutos);
            int tempo_maximo = tempo_maximo_minutos * 60; // Converte para segundos

            // Ordena m�sicas
            sort_playlist(nomes, generos, duracoes, quantidade);

            int tempo_total = 0;
            printf("\n--- Playlist por Tempo Maximo ---\n");
            for (i = 0; i < quantidade; i++) {
                if (tempo_total + duracoes[i] <= tempo_maximo) {
                    printf("Musica %d:\n", i + 1);
                    printf("Nome: %s\n", nomes[i]);
                    printf("Genero: %s\n", generos[i]);
                    printf("Duracao: %d minutos\n\n", duracoes[i] / 60);
                    tempo_total += duracoes[i];
                }
            }
            printf("Tempo total da playlist: %d minutos\n", tempo_total / 60);

        } else if (opcao == 4) {
            int generos_escolhidos[MAX_GENEROS] = {0}; // Vetor para marcar quais g�neros foram escolhidos
            int genero_opcao;

            printf("Escolha os generos para a playlist (digite 0 para terminar):\n");
            for (i = 0; i < MAX_GENEROS; i++) {
                printf("%d. %s\n", i + 1, generos_preestabelecidos[i]);
            }

            while (1) {
                printf("Escolha uma opcao de genero (1-%d) ou 0 para terminar: ", MAX_GENEROS);
                scanf("%d", &genero_opcao);

                if (genero_opcao == 0) {
                    break; // Sai do loop se o usu�rio digitar 0
                }

                if (genero_opcao >= 1 && genero_opcao <= MAX_GENEROS) {
                    generos_escolhidos[genero_opcao - 1] = 1;
                    printf("Genero %s adicionado � playlist.\n", generos_preestabelecidos[genero_opcao - 1]);
                } else {
                    printf("Opcao invalida! Tente novamente.\n");
                }
            }

            sort_playlist(nomes, generos, duracoes, quantidade);

            printf("\n--- Playlist por Generos Escolhidos ---\n");
            int tempo_total = 0;
            for (i = 0; i < quantidade; i++) {
                for (j = 0; j < MAX_GENEROS; j++) {
                    if (generos_escolhidos[j] == 1 && strcmp(generos[i], generos_preestabelecidos[j]) == 0) {
                        printf("Musica %d:\n", i + 1);
                        printf("Nome: %s\n", nomes[i]);
                        printf("Genero: %s\n", generos[i]);
                        printf("Duracao: %d minutos\n\n", duracoes[i] / 60);
                        tempo_total += duracoes[i];
                        break; // Sai do loop interno ap�s encontrar o g�nero
                    }
                }
            }
            printf("Tempo total da playlist: %d minutos\n", tempo_total / 60);

        } else if (opcao == 5) {
            printf("Saindo do programa...\n");
        } else {
            printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 5); // Repete o menu at� a op��o ser 5 (sair)

    return 0; // Encerra o programa
}
