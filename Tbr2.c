#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tbr2.h"


int main()
{
	Pasta *raiz = NULL;
	Arquivo *arq = NULL;
	FILE *file = NULL;
	char s[200];
	char nome[200];
	char comando[6] = " ";
	int i,cont = 0,r=1;

	system("cls");

	do
	{
		strcpy(comando,"");
		fflush(stdin);
		printf("%s\n",comando );
		printf("=> ");
		scanf("%[^\n]s",s);
		printf("..........................\n");
                                                                             
		//Chamando a função que separa o comando do nome do arquivo
		cont = Comandos(0,s,comando,cont,' ');//<--pegando o comando
		cont = Comandos(cont+1,s,nome,0,'\0');//<--pegando o nome do arquivo

		//Comandos Gerais:
		printf("Comando = %s\n",comando);
		if(strcmp(comando,"ls")==0){
			printf("LS\n");
		}else{
			if(strcmp(comando,"lsf")==0){
				printf("LSF\n");
			}else{
				if(strcmp(comando,"dir")==0){
					printf("DIR\n");
				}
			}
		}

		//Comando para pasta
		if(strcmp(comando,"cd")==0){	
			if(Cd(&raiz,nome)){
				printf("..........................\n");
				printf("Pasta: %s",nome);
				printf("..........................\n");
			}else{
				printf("MSG: Pasta nao existe!\n");
			}
		}else{
			if(strcmp(comando,"cdb")==0){
				printf("db\n");
			}else{
				if(strcmp(comando,"mkdir")==0){
					raiz = CriaPasta(nome);
				}else{
					if(strcmp(comando,"rm")==0){
						printf("rm\n");
					}else{
						if(strcmp(comando,"mv")==0){
							printf("mv\n");
						}
					}
				}
			}
		}

		//Comando para arquivo
		if(strcmp(comando,"new")==0){
			
			if(file==NULL){
				file = open(nome,"w");
				fclose(file);
			}else{
				printf("MSG: Arquivo ja existe!\n");
			}
		}
		else{
			if(strcmp(comando,"edit")==0){
					gravaLinha(file,nome);
			}
			else{
				if(strcmp(comando,"del")==0){

					if(file!=NULL){
						remove(nome);
						printf("Arquivo removido\n");
						file = NULL;
						fclose(file);
					}else{
						printf("MSG: Arquivo nao existe!\n");
					}

				}
				else{
					if(strcmp(comando,"view")==0){
						Imprime(file,nome);
						printf("..........................\n");
					}
				}
			}
		}
		
	cont = 0;//reiniciando a variável
	}while(strcmp(comando,"exit")!=0);

	return 0;
}

//Separando o comando do nome do arquivo;
int Comandos(int i, char s[], char comando[],int cont,char condicao)
{
	char c;
	for(;;i++)
	{
		c = s[i];
		
		/*condicao de parada, se for para o comando, a condicao é ' '(espaço), 
		se for para o nome do arquivo a condição é '\0'(fim da string);*/
		if(c==condicao) break;
		comando[cont] = c;

		cont++;
	}
	comando[cont]='\0';//colocando o '\0' na ultima posição;
	return cont;

}

FILE *open(char *filename,char *type)
{
    FILE *file = fopen(filename,type);
    if (file==NULL)
    {
        printf("Erro ao Criar\n");
        return NULL;
    }

    return file;
}


void gravaLinha(FILE *arquivo, char nome[])
{
	char linha[200];
    if (arquivo!=NULL)
    {
    	arquivo = open(nome,"a");
    	printf("Editando: %s\n",nome);
    	printf("..........................\n");
    	do{
    		linha[0] = '\0';
    		fflush(stdin);
    		gets(linha);
    		if (strcmp(linha,":save")!=0 && strcmp(linha,":quit")!=0)
    			fprintf(arquivo,"%s\n",linha);

    	}while(strcmp(linha,":save")!=0 && strcmp(linha,":quit")!=0);
    	printf("..........................\n");
    	printf("MSG: Arquivo salvo com sucesso!\n\n");
    }else{
    	printf("MSG: Arquivo nao existe!\n\n");
    }
    fclose(arquivo);
}


void Imprime(FILE *file, char nome[])
{
	FILE *pont_arq;
  	char texto_str[200];

  	if (file!=NULL){
  		printf("Vendo: %s\n",nome);
    	printf("..........................\n");
  		//abrindo o arquivo_frase em modo "somente leitura"
  		pont_arq = fopen(nome, "r");
  
  		//enquanto não for fim de arquivo o looping será executado
  		//e será impresso o texto
  		while(fgets(texto_str, 200, file) != NULL)
  		printf("%s", texto_str);
  
  		//fechando o arquivo
  		fclose(pont_arq);
  	}else{
  		printf("MSG: Arquivo nao existe!\n");
  	}
  
}

//Mover entre as pastas
int Cd(Pasta **raiz,char *nome)
{
    Pasta *aux=NULL,*anterior=NULL;
    if (*raiz==NULL)
    {
        return 0;
    }
    else
    {
        aux = *raiz;
        while (aux!=NULL && strcmp(aux->nome,nome)!=0)
        {
            anterior = aux;
            aux = aux->prox;
        }

        if (aux==NULL)
        {
            return 0;
        }
        else
        {
            if (anterior==NULL)
            {
                *raiz = aux->prox;
            }
            else
            {
                anterior->prox = aux->prox;
            }
            return 1;
        }
    }
}

Pasta *CriaPasta(char *nome)
{
    Pasta *novo=NULL,*dados=NULL;

    novo=criaDado(nome);

    Inserir(&dados,novo);

    return dados;
}

Pasta *criaDado(char *nome)
{
    Pasta *novo=malloc(sizeof(Pasta));
    novo->lista=malloc(sizeof(Arquivo));

    novo->lista->prox = NULL;
    novo->lista->nome = malloc(sizeof(char)*30);
    novo->lista->caminhoEmDisco = malloc(sizeof(char)*200);

    strcpy(novo->lista->caminhoEmDisco,nome);
    novo->numSubPastas = 0;
    novo->numArquivos = 0;
    
    novo->nome = malloc(sizeof(char)*30);
    
    strcpy(novo->nome,nome);
    novo->prox = NULL;
    novo->sub = NULL;
    
    return novo;
}

void Inserir(Pasta **dados,Pasta *novo)
{
	Pasta *aux=NULL,*anterior=NULL;
    if (*dados == NULL)
    {
        *dados = novo;
    }
    else
    {
        aux = *dados;
        while (aux!=NULL)
        {
            anterior = aux;
            aux->sub = anterior;
            aux = aux->prox;
        }

        if (anterior==NULL)
        {
            novo->prox = aux;
            novo->sub = aux->sub;
            *dados = novo;
        }
        else
        {
            novo->prox=aux;
            novo->sub = novo;
            anterior->prox=novo;
        }
    }
}

void print(Pasta *pasta)
{
    Pasta *aux = pasta;
    int i;
    for (i=0;aux!=NULL;i++,aux=aux->prox)
    {
        printf("%s",pasta->lista->nome);
    }
}

