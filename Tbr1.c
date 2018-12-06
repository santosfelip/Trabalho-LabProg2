#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Comandos(int i, char s[], char comando[],int cont,char condicao);
FILE *open(char *filename,char *type);
void gravaLinha(FILE *arquivo, char nome[]);
void Imprime(FILE *file,char nome[]);

int main()
{
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

