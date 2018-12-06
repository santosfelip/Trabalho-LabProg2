#ifndef TBR_H_INCLUDED
#define TBR_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

	typedef struct arq
	{
		struct arq *prox;
		char *nome;
		char *caminhoEmDisco;
	}Arquivo;
	
	typedef struct pasta
	{
		struct pasta *sub;
		struct pasta *prox;
		Arquivo *lista;
		char *nome;
		int numSubPastas;
		int numArquivos;
	}Pasta;

	//Protótipos de arquivos
	int Comandos(int i, char s[], char comando[],int cont,char condicao);
	FILE *open(char *filename,char *type);
	void gravaLinha(FILE *arquivo, char nome[]);
	void Imprime(FILE *file,char nome[]);

	//Protótipos pra entrar nas pastas
	int Cd(Pasta **raiz,char *nome);
	Pasta *CriaPasta(char *nome);
	Pasta *criaDado(char *nome);
	void Inserir(Pasta **dados,Pasta *novo);


#endif // TBR2_H_INCLUDED