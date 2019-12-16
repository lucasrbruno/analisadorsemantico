#include "../headers/utils.h"
#include <stdio.h>
#include <stdlib.h>

void analiseLexica(MaquinaEstados *maquinaEstados, char *arquivo, char *nomeArquivo, ListaToken *listaToken, ListaToken *listaTokenIdentificadores){
    int tamArquivo = strlen(arquivo);
    int posicao;
    int valido = 1;
    int i;
    int numErros = 0;
    strcpy(BUFFER,"\0");

    //Iniciar palavras reservadas
    char **palavras_reservadas = malloc(32*(sizeof(char *)));
    for(i=0;i<32;i++){
        palavras_reservadas[i] = malloc(15*sizeof(char));
    }

    iniciarPalavrasReservadas(palavras_reservadas);

    //Gerar string com o caminho do arquivo de saida
    char *nomeArquivo01 = strtok(nomeArquivo,"/");
    char nomeArquivo02[100];
    while(nomeArquivo01 != NULL){
        sprintf(nomeArquivo02,"%s",nomeArquivo01);
        nomeArquivo01 = strtok(NULL,"/");
    }
    char *nomeArquivo03 = strtok(nomeArquivo02,".");
    char nomeArquivoFinal[100];
    sprintf(nomeArquivoFinal,"%s%s%s","out/",nomeArquivo03,"_tabela.txt");

    //Inicializar lista de tokens
    iniciarListaToken(listaToken);

    //Funcionamento do automato e reconhecimento de tokens
    for(posicao = 0;posicao<tamArquivo;posicao++){
        
        alimentarMaquinaEstados(maquinaEstados,arquivo[posicao],&valido,palavras_reservadas,listaToken);


        if(!valido){
            erroAnaliseSintatica(maquinaEstados->estadoAtual,LINHA,COLUNA);

            //Resetar o automato para o Estado 0 e limpar o buffer.
            maquinaEstados->estadoAtual = 0;
            strcpy(BUFFER,"\0");
            numErros++;
            valido = 1;
        }
        if(arquivo[posicao] != '\n'){
            COLUNA++;
        }else{
            LINHA++;
            COLUNA = 1;
        }
    }

    //O buffer ainda nao esta vazio
    if(strlen(BUFFER) > 0){
        identificarToken(maquinaEstados,palavras_reservadas,listaToken);
        //inserirListaToken(listaToken,"reservada",BUFFER,LINHA,COLUNA-(strlen(BUFFER)));
    }

    //Fim do arquivo mas o estado nao eh final
    if(maquinaEstados->estados[maquinaEstados->estadoAtual].final == 0){
        valido = 0;
    }

    if(numErros == 0){
        printf("\nAnalise Lexica: SUCESSO.\n");
        FILE *arq = fopen(nomeArquivoFinal,"w");
        char nomeArquivoIdentificadores[100];
        char nomeArquivoReservadas[100];
        char nomeArquivoSeparadores[100];
        char nomeArquivoOperadores[100];
        char nomeArquivoLiterais[100];
        char nomeArquivoComentarios[100];
        char nomeArquivoNumeros[100];
        char nomeArquivoDiretiva[100];

        sprintf(nomeArquivoIdentificadores,"%s%s%s","out/",nomeArquivo03,"_identificadores.txt");
        sprintf(nomeArquivoReservadas,"%s%s%s","out/",nomeArquivo03,"_reservadas.txt");
        sprintf(nomeArquivoSeparadores,"%s%s%s","out/",nomeArquivo03,"_separadores.txt");
        sprintf(nomeArquivoNumeros,"%s%s%s","out/",nomeArquivo03,"_numeros.txt");
        sprintf(nomeArquivoOperadores,"%s%s%s","out/",nomeArquivo03,"_operadores.txt");
        sprintf(nomeArquivoLiterais,"%s%s%s","out/",nomeArquivo03,"_literais.txt");
        sprintf(nomeArquivoComentarios,"%s%s%s","out/",nomeArquivo03,"_comentarios.txt");
        sprintf(nomeArquivoDiretiva,"%s%s%s","out/",nomeArquivo03,"_diretiva.txt");

        FILE *arqIdentificadores = fopen(nomeArquivoIdentificadores,"w");
        FILE *arqReservadas = fopen(nomeArquivoReservadas,"w");
        FILE *arqSeparadores = fopen(nomeArquivoSeparadores,"w");
        FILE *arqNumeros = fopen(nomeArquivoNumeros,"w");
        FILE *arqOperadores = fopen(nomeArquivoOperadores,"w");
        FILE *arqLiterais = fopen(nomeArquivoLiterais,"w");
        FILE *arqComentarios = fopen(nomeArquivoComentarios,"w");
        FILE *arqDiretiva = fopen(nomeArquivoDiretiva,"w");


        
        iniciarListaToken(listaTokenIdentificadores);

        escreverArquivoTokens(arq,arqIdentificadores,arqReservadas,arqNumeros,arqSeparadores,arqOperadores,arqLiterais,arqComentarios,arqDiretiva,listaToken,palavras_reservadas,listaTokenIdentificadores);

        fclose(arq);
        fclose(arqIdentificadores);
        fclose(arqReservadas);
        fclose(arqSeparadores);
        fclose(arqNumeros);
        fclose(arqOperadores);
        fclose(arqLiterais);
        fclose(arqComentarios);
        fclose(arqDiretiva);
    }else{
        printf("\nAnalise Lexica: ERRO.\n");
    }

    //Liberacao de memoria.
    //freePalavrasReservadas(palavras_reservadas);
    
    freeMaquinaEstados(maquinaEstados);
    
}

void escreverArquivoTokens(FILE *arquivoTokens, FILE *arqIdentificadores, FILE *arqReservados, FILE *arqNumeros, FILE *arqSeparadores, FILE *arqOperadores, FILE *arqLiterais, FILE *arqComentarios, FILE *arqDiretiva, ListaToken *listaToken, char **palavras_reservadas, ListaToken *listaTokenIdentificadores){
    Token *aux = listaToken->primeira;
    char teste[2048];
    while(aux != NULL){
        sprintf(teste,"%s",aux->valorBruto);
        if(!strcmp(teste,"\n")){
           sprintf(teste,"\\n");
        }
        if(!strcmp(teste,"\t")){
           sprintf(teste,"\\t");
        }
        fprintf(arquivoTokens,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        int achou = 0;

        if(!achou && isPalavraReservada(aux->valor,palavras_reservadas)){
            achou = 1;
            fprintf(arqReservados,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        }

        if(!achou && !strcmp(aux->valor,"numero")){
            achou = 1;
            fprintf(arqNumeros,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        }

        if(!achou && !strcmp(aux->valor,"identificador")){
            achou = 1;
            inserirListaToken(listaTokenIdentificadores,aux->valor,aux->valorBruto,aux->linha,aux->coluna);
            fprintf(arqIdentificadores,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        }

        if(!achou && !strcmp(aux->valor,"operador")){
            achou = 1;
            fprintf(arqOperadores,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        }

        if(!achou && !strcmp(aux->valor,"aspas_simples")){
            achou = 1;
            fprintf(arqLiterais,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        }

        if(!achou && !strcmp(aux->valor,"aspas_duplas")){
            achou = 1;
            fprintf(arqLiterais,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        }

        if(!achou && !strcmp(aux->valor,"comentario")){
            achou = 1;
            fprintf(arqComentarios,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        }

        if(!achou && !strcmp(aux->valor,"diretiva")){
            achou = 1;
            fprintf(arqDiretiva,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        }

        if(!achou){
            achou = 1;
            fprintf(arqSeparadores,"%s,\"%s\",%d,%d\n",aux->valor,teste,aux->linha,aux->coluna);
        }

        aux = aux->proxima;
    }
}

int isPalavraReservada(char *str, char **palavrasReservadas){
    int i;
    for(i=0;i<32;i++){
        if(!strcmp(str,palavrasReservadas[i])){
            return 1;
        }
    }
    return 0;
}

void identificarToken(MaquinaEstados *maquinaEstados, char **palavrasReservadas, ListaToken *listaToken){
    if(maquinaEstados->estados[maquinaEstados->estadoAtual].final == 1){
        int achou = 0;
        char tipo[50];
        int isNull = 0;
        //Identificacao de tipo de token
        if(!achou && strchr(SEPARADOR,BUFFER[0]) != NULL){
            char *aux = tipoSeparador(BUFFER[0]);
            sprintf(tipo,"%s",aux);
            if(strcmp(aux,"null") == 0){
                isNull = 1;
            }
            achou = 1;
        }

        if(!achou && isLiteralAspasDuplas(BUFFER)){
            sprintf(tipo,"%s","aspas_duplas");
            achou = 1;
        }

        if(!achou && isLiteralAspasSimples(BUFFER)){
            sprintf(tipo,"%s","aspas_simples");
            achou = 1;
        }

        if(!achou && isOperador(BUFFER)){
            sprintf(tipo,"%s",tipoOperador(BUFFER));
            achou = 1;
        }

        if(!achou && isNumero(BUFFER)){
            sprintf(tipo,"%s","numero");
            achou = 1;
        }

        if(!achou && isPalavraReservada(BUFFER,palavrasReservadas)){
            sprintf(tipo,"%s",BUFFER);
            achou = 1;
        }

        if(!achou && isComentario(BUFFER)){
            sprintf(tipo,"%s","comentario");
            achou = 1;
        }

        if(!achou && isDiretiva(BUFFER)){
            sprintf(tipo,"%s","diretiva");
            achou = 1;
        }

        if(!achou){
            sprintf(tipo,"%s","identificador");
        }
        if(!isNull){
            if(!isTokenDescartavel(tipo)){
                inserirListaToken(listaToken,tipo,BUFFER,LINHA,COLUNA-(strlen(BUFFER)));
            }
        }
        strcpy(BUFFER,"\0");
    }
}

int isTokenDescartavel(char *tipo){
    if(!strcmp(tipo,"espaco") || !strcmp(tipo,"quebra_linha") || !strcmp(tipo,"tabulacao") || !strcmp(tipo,"comentario") || !strcmp(tipo,"retorno_de_carruagem")){
        return 1;
    }
    return 0;
}

int isNumero(char *str){
    int i;
    for(i=0;i<strlen(str);i++){
        if((str[i] < 48 || str[i] > 57) && (str[i] != '.')){
            return 0;
        }
    }
    return 1;
}

char *tipoOperador(char *str){
    if(!strcmp(str,"+")){ return "mais"; }
    if(!strcmp(str,"*")){ return "vezes"; }
    if(!strcmp(str,"%%")){ return "porcento"; }
    if(!strcmp(str,"/")){ return "barra"; }
    if(!strcmp(str,"=")){ return "igual"; }
    if(!strcmp(str,"<")){ return "menor"; }
    if(!strcmp(str,">")){ return "maior"; }
    if(!strcmp(str,"!")){ return "negacao"; }
    if(!strcmp(str,"|")){ return "or_simples"; }
    if(!strcmp(str,"&")){ return "and_simples"; }
    if(!strcmp(str,"~")){ return "til"; }
    if(!strcmp(str,"^")){ return "circunflexo"; }
    if(!strcmp(str,"-")){ return "menos"; }
    if(!strcmp(str,"?")){ return "interrogacao"; }
    if(!strcmp(str,"+=")){ return "mais_igual"; }
    if(!strcmp(str,"++")){ return "mais_mais"; }
    if(!strcmp(str,"-=")){ return "menos_igual"; }
    if(!strcmp(str,"--")){ return "menos_menos"; }
    if(!strcmp(str,"*=")){ return "vezes_igual"; }
    if(!strcmp(str,"**")){ return "vezes_vezes"; }
    if(!strcmp(str,"/=")){ return "barra_igual"; }
    if(!strcmp(str,"==")){ return "igual_igual"; }
    if(!strcmp(str,"!=")){ return "diferente"; }
    if(!strcmp(str,"<=")){ return "menor_igual"; }
    if(!strcmp(str,">=")){ return "maior_igual"; }
    if(!strcmp(str,"||")){ return "or_duplo"; }
    if(!strcmp(str,"&&")){ return "and_duplo"; }

    return "null_operador";
    
}

char *tipoSeparador(char str){
    switch(str){
        case ' ': return "espaco";
        case ';': return "ponto_virgula";
        case '\n': return "quebra_linha";
        case '\r': return "retorno_de_carruagem";
        case '\t': return "tabulacao";
        case '(': return "abre_parenteses";
        case ')': return "fecha_parenteses";
        case '[': return "abre_colchetes";
        case ']': return "fecha_colchetes";
        case '{': return "abre_chaves";
        case '}': return "fecha_chaves";
        case ',': return "virgula";
        case '.': return "ponto";
        case ':': return "dois_pontos";
        default: return "null";
    }
}

int isOperador(char *str){
    int i;
    int achou = 0;
    for(i=0;i<strlen(str);i++){
        if(strchr(OPERADOR,str[i]) != NULL){
            achou++;
            continue;
        }
    }
    if(achou == strlen(str)){
        return 1;
    }
    return 0;
}

int isLiteralAspasDuplas(char *str){
    if(strlen(str) > 2){
        if(str[0] == '\"' && str[strlen(str)-1] == '\"'){
            return 1;
        }
    }
    return 0;
}

int isLiteralAspasSimples(char *str){
    if(strlen(str) > 2){
        if(str[0] == '\'' && str[strlen(str)-1] == '\''){
            return 1;
        }
    }
    return 0;
}

int isDiretiva(char *str){
    if(str[0] == '#'){
        return 1;
    }
    return 0;
}

int isComentario(char *str){
    if(strlen(str) < 3){
        return 0;
    }
    if(str[0] == '/' && str[1] == '/'){
        return 1;
    }
    if(strlen(str) < 4){
        return 0;
    }
    if(str[0] == '/' && str[1] == '*' && str[strlen(str)-2] == '*' && str[strlen(str)-1] == '/'){
        return 1;
    }
    return 0;
}

char *erroEstadoAtual(int estado){
    switch(estado){
        case 0: return "Caracter invalido.";
        case 1: return "Letra invalida para identificador.";
        case 2: return "Caracter invalido para numero.";
        case 3: return "Caracter invalido para numero.";
        case 4: return "Caracter invalido para operador '+'.";
        case 5: return "Caracter invalido para operador '-'.";
        case 6: return "Caracter invalido para operador '*'.";
        case 7: return "Caracter invalido para operador '/'.";
        case 8: return "Caracter invalido para operador '='.";
        case 9: return "Caracter invalido para operador '<'.";
        case 10: return "Caracter invalido para operador '>'.";
        case 11: return "Caracter invalido para operador '%'.";
        case 12: return "Caracter invalido para operador ''.";
        case 13: return "Caracter invalido para operador '!'.";
        case 14: return "Caracter invalido para operador '|'.";
        case 15: return "Caracter invalido para operador '&'.";
        case 16: return "Caracter invalido para literal '\"'.";
        case 17: return "Caracter invalido para literal '\"'.";
        case 18: return "Caracter invalido para literal '\''.";
        case 19: return "Caracter invalido para literal '\''.";
        case 20: return "Caracter invalido para literal '\\'.";
        case 21: return "Caracter invalido para diretiva.";
        case 22: return "Caracter invalido para comentario.";
        case 23: return "Caracter invalido para comentario.";
        case 24: return "Caracter invalido para comentario.";
        case 25: return "Caracter invalido para comentario.";
        case 26: return "Nao eh possivel colocar comentario dentro de comentario.";
        default: return "Erro desconhecido.";
    }
}

void erroAnaliseSintatica(int estadoAtual, int linha, int coluna){
    printf("Linha %d, Coluna %d: %s\n",linha,coluna,erroEstadoAtual(estadoAtual));
}
