#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxLineLength 1000


typedef struct {
    char nome[50];
    char telefone[20];
    char curso[50];
    float nota1;
    float nota2;
    float media;
    char situacao[10];
} Aluno;

void calcularSituacao(Aluno *aluno) {
    aluno->media = (aluno->nota1 + aluno->nota2) / 2.0;
    strcpy(aluno->situacao, aluno->media >= 7.0 ? "APROVADO" : "REPROVADO");
}

int main() {
    setlocale(LC_ALL, "brazilian");

    FILE *entrada = fopen("DadosEntrada.cvs", "r");
    if (!entrada) {
        entrada = fopen("DadosEntrada.txt", "r");
        if (!entrada) {
            printf("não existe arquivo");
            return 1;}
        }

    FILE *saida = fopen("SituacaoFinal.cvs", "w");
    if (!saida) {
        printf("erro ao criar o arquivo");
        fclose(entrada);
        return 1;
    }

    char linha[maxLineLength];
    while (fgets(linha, maxLineLength, entrada)) {
        Aluno aluno;
        sscanf(linha, "%[^,],%[^,],%[^,],%f,%f", aluno.nome, aluno.telefone, aluno.curso, &aluno.nota1, &aluno.nota2);
        calcularSituacao(&aluno);
        fprintf(saida, "%s, %.2f, %s\n", aluno.nome, aluno.media, aluno.situacao);
    }

    fclose(entrada);
    fclose(saida);

    printf("sucesso ao criar arquivo");

    return 0;
}

