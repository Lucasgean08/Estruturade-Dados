#include <stdio.h>
#include <stdlib.h>
#include <process.h>

typedef struct {
	int id;
	char numero[21];
	char data_ajuizamento[24];
	int id_classe;
	int id_assunto;
	int ano_eleicao;
} Processo;

Processo* lerArquivo(const char *nomeArquivo, int *quantidade) {
	
	FILE *arquivo = fopen(nomeArquivo, "r");
	
	if (arquivo == NULL) {
		printf ("Erro ao abrir o arquivo.\n");
		return NULL;
	}
	
	Processo *processos = NULL;
    *quantidade = 0;
	char linha[300];
	fgets(linha, sizeof(linha), arquivo); // Ignora o cabe�alho
	
	
	while (fgets(linha, sizeof(linha), arquivo)) {
		printf(linha);
		processos = (Processo*) realloc(processos, (*quantidade + 1) * sizeof(Processo));
        if (processos == NULL) {
            printf("Erro ao alocar mem�ria.\n");
            fclose(arquivo);
            return NULL;
		}
		int i = *quantidade;
	
		sscanf(linha, "%d,\"%20[^\"]\",%23[^,],{%d},{%d},%d", &processos[i].id, processos[i].numero, 
        processos[i].data_ajuizamento, &processos[i].id_classe, &processos[i].id_assunto, &processos[i].ano_eleicao);
		(*quantidade)++;
	}
	
	fclose (arquivo);
	return processos;
}

int main() {
	
	int numProcessos = 0;
	int numClasse = 0;
	const char *linha = "\"id\",\"numero\",\"data_ajuizamento\",\"id_classe\",\"id_assunto\",\"ano_eleicao\"";
    
    printf("%s\n\n", linha);
    

//abrir arquivo
    Processo *processos = lerArquivo("processo_Copia.csv", &numProcessos);

	
	if (numProcessos < 0) {
		printf ("ERRO!\n");
		return 1;
	} else {
		printf("\n\nArquivo lido com sucesso!\nTotal de processos: %d \n\n", numProcessos);
	}
	

	
	free(processos);
	return 0;
}
