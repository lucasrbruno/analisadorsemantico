#include <stdio.h>
#include "../headers/utils.h"
#include "../headers/lexico.h"

void criarEstado(Estado *estado, int idEstado){
    estado->id = idEstado;
    estado->numTransicoes = 0;
    iniciarLista(estado);
}

void adicionarTransicao(MaquinaEstados *maquinaEstados, int idTransicao, char *conjunto){
    //Estado *e = malloc(sizeof(Estado));
}

void alimentarMaquinaEstados(MaquinaEstados *maquinaEstados, char token, int *valido, char **palavrasReservadas, ListaToken *listaToken){
    int i;
    Transicao *aux = maquinaEstados->estados[maquinaEstados->estadoAtual].primeira;
    int achou = 0;
    for(i=0;i<maquinaEstados->estados[maquinaEstados->estadoAtual].numTransicoes;i++){
        int j;
        for(j=0;aux->conjunto[j]!='\0';j++){
            if(aux->conjunto[j] == token){
                maquinaEstados->estadoAtual = aux->proximoEstado;
                if(strchr(SEPARADOR,token) == NULL){
                    sprintf(BUFFER,"%s%c",BUFFER,token);
                }else{
                    identificarToken(maquinaEstados,palavrasReservadas,listaToken);
                    
                    if(maquinaEstados->estados[maquinaEstados->estadoAtual].final == 1){
                        sprintf(BUFFER,"%c",token);    
                        identificarToken(maquinaEstados,palavrasReservadas,listaToken);
                    }else{
                        sprintf(BUFFER,"%s%c",BUFFER,token);
                    }
                }
                achou = 1;
                break;
            }
        }
        if(achou){
            break;
        }
        aux = aux->proxima;
    }
    //if(!achou){
    //    (*valido) = 0; 
    //}

    if((!achou) && (maquinaEstados->estadoAtual != 0)){
        maquinaEstados->estadoAtual = 0;
        aux = maquinaEstados->estados[maquinaEstados->estadoAtual].primeira;
        identificarToken(maquinaEstados,palavrasReservadas,listaToken);
        strcpy(BUFFER,"\0");

        for(i=0;i<maquinaEstados->estados[maquinaEstados->estadoAtual].numTransicoes;i++){
            int j;
            for(j=0;aux->conjunto[j]!='\0';j++){
                if(aux->conjunto[j] == token){
                    maquinaEstados->estadoAtual = aux->proximoEstado;
                    if(strchr(SEPARADOR,token) == NULL){
                        sprintf(BUFFER,"%s%c",BUFFER,token);
                    }else{
                        identificarToken(maquinaEstados,palavrasReservadas,listaToken);
                        
                        if(maquinaEstados->estados[maquinaEstados->estadoAtual].final == 1){
                            sprintf(BUFFER,"%c",token);    
                            identificarToken(maquinaEstados,palavrasReservadas,listaToken);
                        }else{
                            sprintf(BUFFER,"%s%c",BUFFER,token);
                        }
                    }
                    achou = 1;
                    break;
                }
            }
            if(achou){
                break;
            }
            aux = aux->proxima;
        }
        if(!achou){
            (*valido) = 0; 
        }
    }
}



void iniciarAutomato(MaquinaEstados *maquinaEstados){
    setEstadoFinal(maquinaEstados,0);
    inserirLista(&maquinaEstados->estados[0],"$",1);
    inserirLista(&maquinaEstados->estados[0],"_",1);
    inserirLista(&maquinaEstados->estados[0],LETRA,1);
    inserirLista(&maquinaEstados->estados[0],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[0],NUMERO,2);
    inserirLista(&maquinaEstados->estados[0],"+",4);
    inserirLista(&maquinaEstados->estados[0],"-",5);
    inserirLista(&maquinaEstados->estados[0],"*",6);
    inserirLista(&maquinaEstados->estados[0],"/",7);
    inserirLista(&maquinaEstados->estados[0],"=",8);
    inserirLista(&maquinaEstados->estados[0],"<",9);
    inserirLista(&maquinaEstados->estados[0],">",10);
    inserirLista(&maquinaEstados->estados[0],"%",11);
    inserirLista(&maquinaEstados->estados[0],"!",13);
    inserirLista(&maquinaEstados->estados[0],"~",13);
    inserirLista(&maquinaEstados->estados[0],"^",13);
    inserirLista(&maquinaEstados->estados[0],"?",13);
    inserirLista(&maquinaEstados->estados[0],"|",14);
    inserirLista(&maquinaEstados->estados[0],"&",15);
    inserirLista(&maquinaEstados->estados[0],"\"",16);
    inserirLista(&maquinaEstados->estados[0],"'",18);
    inserirLista(&maquinaEstados->estados[0],"#",21);
    

    inserirLista(&maquinaEstados->estados[1],LETRA,1);
    inserirLista(&maquinaEstados->estados[1],"_",1);
    inserirLista(&maquinaEstados->estados[1],NUMERO,1);
    inserirLista(&maquinaEstados->estados[1],SEPARADOR,0);

    inserirLista(&maquinaEstados->estados[2],NUMERO,3);
    inserirLista(&maquinaEstados->estados[2],".",3);
    inserirLista(&maquinaEstados->estados[2],SEPARADOR,0);

    inserirLista(&maquinaEstados->estados[3],NUMERO,3);
    inserirLista(&maquinaEstados->estados[3],SEPARADOR,0);

    inserirLista(&maquinaEstados->estados[4],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[4],"+",0);
    inserirLista(&maquinaEstados->estados[4],"=",0);

    inserirLista(&maquinaEstados->estados[5],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[5],"-",0);
    inserirLista(&maquinaEstados->estados[5],"=",0);
    
    inserirLista(&maquinaEstados->estados[6],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[6],"=",0);

    inserirLista(&maquinaEstados->estados[7],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[7],"=",0);
    inserirLista(&maquinaEstados->estados[7],"/",22);
    inserirLista(&maquinaEstados->estados[7],"*",23);

    inserirLista(&maquinaEstados->estados[8],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[8],"=",0);

    inserirLista(&maquinaEstados->estados[9],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[9],"=",0);

    inserirLista(&maquinaEstados->estados[10],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[10],"=",0);

    inserirLista(&maquinaEstados->estados[11],SEPARADOR,0);

    inserirLista(&maquinaEstados->estados[12],SEPARADOR,0);

    setEstadoFinal(maquinaEstados,13);
    inserirLista(&maquinaEstados->estados[13],SEPARADOR,0);
    inserirLista(&maquinaEstados->estados[13],LETRA,1);
    
    inserirLista(&maquinaEstados->estados[14],"|",0);
    
    inserirLista(&maquinaEstados->estados[15],"&",0);

    inserirLista(&maquinaEstados->estados[16],"\\",17);
    inserirLista(&maquinaEstados->estados[16],"\"",0);
    inserirLista(&maquinaEstados->estados[16],"'",16);
    inserirLista(&maquinaEstados->estados[16],LETRA,16);
    inserirLista(&maquinaEstados->estados[16],OPERADOR,16);
    inserirLista(&maquinaEstados->estados[16],SEPARADOR,16);
    inserirLista(&maquinaEstados->estados[16],NUMERO,16);
    
    inserirLista(&maquinaEstados->estados[17],LETRA,16);
    inserirLista(&maquinaEstados->estados[17],OPERADOR,16);
    inserirLista(&maquinaEstados->estados[17],SEPARADOR,16);
    inserirLista(&maquinaEstados->estados[17],NUMERO,16);
    inserirLista(&maquinaEstados->estados[17],"'",16);
    inserirLista(&maquinaEstados->estados[17],"\\",16);
    inserirLista(&maquinaEstados->estados[17],"\"",16);

    inserirLista(&maquinaEstados->estados[18],LETRA,19);
    inserirLista(&maquinaEstados->estados[18],OPERADOR,19);
    inserirLista(&maquinaEstados->estados[18],SEPARADOR,19);
    inserirLista(&maquinaEstados->estados[18],NUMERO,19);
    inserirLista(&maquinaEstados->estados[18],"'",19);
    inserirLista(&maquinaEstados->estados[18],"\"",19);
    inserirLista(&maquinaEstados->estados[18],"\\",20);

    inserirLista(&maquinaEstados->estados[19],"'",0);

    inserirLista(&maquinaEstados->estados[20],LETRA,19);
    inserirLista(&maquinaEstados->estados[20],OPERADOR,19);
    inserirLista(&maquinaEstados->estados[20],SEPARADOR,19);
    inserirLista(&maquinaEstados->estados[20],NUMERO,19);
    inserirLista(&maquinaEstados->estados[20],"'",19);
    inserirLista(&maquinaEstados->estados[20],"\"",19);
    inserirLista(&maquinaEstados->estados[20],"\\",20);

    
    inserirLista(&maquinaEstados->estados[21],"\n",0);
    inserirLista(&maquinaEstados->estados[21],".",21);
    inserirLista(&maquinaEstados->estados[21],LETRA,21);
    inserirLista(&maquinaEstados->estados[21],OPERADOR,21);
    inserirLista(&maquinaEstados->estados[21],SEPARADOR,21);
    inserirLista(&maquinaEstados->estados[21],NUMERO,21);
    inserirLista(&maquinaEstados->estados[21],"'",21);
    inserirLista(&maquinaEstados->estados[21],"\"",21);
    inserirLista(&maquinaEstados->estados[21],"\\",21);

    inserirLista(&maquinaEstados->estados[22],"\n",0);
    inserirLista(&maquinaEstados->estados[22],".",22);
    inserirLista(&maquinaEstados->estados[22],LETRA,22);
    inserirLista(&maquinaEstados->estados[22],OPERADOR,22);
    inserirLista(&maquinaEstados->estados[22],SEPARADOR,22);
    inserirLista(&maquinaEstados->estados[22],NUMERO,22);
    inserirLista(&maquinaEstados->estados[22],"'",22);
    inserirLista(&maquinaEstados->estados[22],"\"",22);
    inserirLista(&maquinaEstados->estados[22],"\\",22);

    inserirLista(&maquinaEstados->estados[23],"*",24);
    inserirLista(&maquinaEstados->estados[23],"/",25);
    inserirLista(&maquinaEstados->estados[23],"\n",23);
    inserirLista(&maquinaEstados->estados[23],".",23);
    inserirLista(&maquinaEstados->estados[23],LETRA,23);
    inserirLista(&maquinaEstados->estados[23],OPERADOR,23);
    inserirLista(&maquinaEstados->estados[23],SEPARADOR,23);
    inserirLista(&maquinaEstados->estados[23],NUMERO,23);
    inserirLista(&maquinaEstados->estados[23],"'",23);
    inserirLista(&maquinaEstados->estados[23],"\"",23);
    inserirLista(&maquinaEstados->estados[23],"\\",23);

    inserirLista(&maquinaEstados->estados[24],"/",0);
    inserirLista(&maquinaEstados->estados[24],"\n",23);
    inserirLista(&maquinaEstados->estados[24],".",23);
    inserirLista(&maquinaEstados->estados[24],LETRA,23);
    inserirLista(&maquinaEstados->estados[24],OPERADOR,23);
    inserirLista(&maquinaEstados->estados[24],SEPARADOR,23);
    inserirLista(&maquinaEstados->estados[24],NUMERO,23);
    inserirLista(&maquinaEstados->estados[24],"'",23);
    inserirLista(&maquinaEstados->estados[24],"\"",23);
    inserirLista(&maquinaEstados->estados[24],"\\",23);

    inserirLista(&maquinaEstados->estados[25],"*",26);
    inserirLista(&maquinaEstados->estados[25],"/",23);
    inserirLista(&maquinaEstados->estados[25],"\n",23);
    inserirLista(&maquinaEstados->estados[25],".",23);
    inserirLista(&maquinaEstados->estados[25],LETRA,23);
    inserirLista(&maquinaEstados->estados[25],OPERADOR,23);
    inserirLista(&maquinaEstados->estados[25],SEPARADOR,23);
    inserirLista(&maquinaEstados->estados[25],NUMERO,23);
    inserirLista(&maquinaEstados->estados[25],"'",23);
    inserirLista(&maquinaEstados->estados[25],"\"",23);
    inserirLista(&maquinaEstados->estados[25],"\\",23);
    //inserirLista(&maquinaEstados->estados[],,);
}
