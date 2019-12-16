#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Biblioteca necessaria para utilizacao do getopt().
#include "../headers/utils.h"
#include "../headers/lexico.h"
#include "../headers/sintatico.h"

int main(int argc,char **argv){
    int optc = 0;
	char *argv1 = NULL;

	// Funcao getopt(), (entrada por parametros).
	while((optc = getopt(argc, argv, "hc:a:s")) != -1){
		switch(optc){
			case 'a':
				argv1 = optarg;
				break;
			case 'h':
				printf("%s -h \"Ajuda\".\nExemplo de entrada:\n./tp1 -a ARQUIVO\n-a arquivo .c para "
				"analise.\n",argv[0]);
				exit(0);
			case 's':
                FLAG_EXIBIR_ARVORE = 1;
                break;
            default:
				printf("Opcao invalida.\nUtilize -h para ajuda.\n");
				exit(0);
		}
	}
	if(argc < 2){
		printf("Nenhum arquivo foi inserido.\nUtilize o parametro -h para ajuda.\n");
		exit(0);
	}

    int i;
    //char tabela_ascii[TAM_ASCII];
    //char comentario = '//';
    //char literal = ''','"';
    
    //iniciarTabelaAscii(tabela_ascii);

    char temp;
    int tamanho_arquivo = 0;

    //Descobrir tamanho do arquivo
    FILE *arq = fopen(argv1,"r");
    while(fscanf(arq,"%c",&temp)!=EOF){
        tamanho_arquivo++;
    }
    fclose(arq);

    //Armazenar o arquivo em vetor
    char *arquivo = malloc(tamanho_arquivo*sizeof(char));
    arq = fopen(argv1,"r");
    i=0;
    while(fscanf(arq,"%c",&temp)!=EOF){
        arquivo[i] = temp;
        i++;
    }
    i=0;
    fclose(arq);

    /*
    for(i=0;i<tamanho_arquivo;i++){
        printf("%c",arquivo[i]);
    }
    */
    //free(arquivo);
    

    //Iniciar automato.
    MaquinaEstados *automato = malloc(sizeof(MaquinaEstados));
    automato->estadoAtual = 0;
    automato->estados = malloc(NUM_ESTADOS*sizeof(Estado));
    
    for(i=0;i<NUM_ESTADOS;i++){
        criarEstado(&automato->estados[i],i);
    }

    ListaToken *listaToken = malloc(sizeof(ListaToken));

    //Inicializar lista de tokens (identificadores)
    ListaToken *listaTokenIdentificadores = malloc(sizeof(ListaToken));

    iniciarAutomato(automato);
    analiseLexica(automato,arquivo,argv1,listaToken,listaTokenIdentificadores);
    LISTATOKEN = listaToken; 
    analiseSintatica(listaTokenIdentificadores);
    /*
    for(i=0;i<32;i++){
        printf("Estado %d\n",i);
        int j;
        Transicao *aux = automato->estados[i].primeira;
        for(j=0;j<automato->estados[i].numTransicoes;j++){
            printf("[%d] %s\n",j,aux->conjunto);
            aux = aux->proxima;
        }
        printf("\n");
    }
    */

    return 0;
}