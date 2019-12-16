#ifndef LEXICO_H_INCLUDED
#define LEXICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "../headers/automato.h"



void analiseLexica(MaquinaEstados *maquinaEstados, char *arquivo, char *nomeArquivo, ListaToken *listaToken, ListaToken *listaTokenIdentificadores);
void escreverArquivoTokens(FILE *arquivoTokens, FILE *arqIdentificadores, FILE *arqReservados, FILE *arqNumeros, FILE *arqSeparadores, FILE *arqOperadores, FILE *arqLiterais, FILE *arqComentarios, FILE *arqDiretiva, ListaToken *listaToken, char **palavras_reservadas, ListaToken *listaTokenIdentificadores);
int isPalavraReservada(char *str, char **palavrasReservadas);
void identificarToken(MaquinaEstados *maquinaEstados, char **palavrasReservadas, ListaToken *listaToken);
int isNumero(char *str);
char *tipoSeparador(char str);
int isOperador(char *str);
void iniciarMensagensErro(MaquinaEstados *maquinaEstados);
void adicionarMensagemErro(MaquinaEstados *maquinaEstados, char *mensagem, int estado);
int isLiteralAspasDuplas(char *str);
int isLiteralAspasSimples(char *str);
int isDiretiva(char *str);
int isComentario(char *str);
char *erroEstadoAtual(int estado);
void erroAnaliseSintatica(int estadoAtual, int linha, int coluna);
int isTokenDescartavel(char *tipo);
char *tipoOperador(char *str);

#endif // LEXICO_H_INCLUDED