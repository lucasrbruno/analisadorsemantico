#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

#include "../headers/automato.h"
#include "../headers/utils.h"

void analiseSintatica(ListaToken *listaTokenIdentificadores);
void consumirToken(int cont);
int tokenIgual(Token *token, char *str);
int tokenDiferente(Token *token, char *str);
void erroSintatico(Token *token, char *erro);
Token *getToken();
void printfSintatico(int cont, char *str);
void proximoPontoVirgula();

void iniciarTabela();
void adicionarNaTabela(Token* token, char* tipo);
void verificaTabela(Token* token);
void verificaTipos(char* tipo1, char* tipo2);
int verificarListaDiretivas(int cont);
int verificarLinguagem(int cont);
int verificarFuncao(int cont);
int verificarTipo(int cont);
int verificarListaArg(int cont);
int verificarArg(int cont);
int verificarDeclaracao(int cont);
int verificarListaIdentificadores(int cont, char* tipo);
int verificarStatement(int cont);
int verificarStatementFor(int cont);
int verificarStatementWhile(int cont);
int verificarStatementReturn(int cont);
int verificarExpressao(int cont);
int verificarExpressao1(int cont, char* tipo);
int verificarExpressao02(int cont, char* tipo);
int verificarStatementIf(int cont);
int verificarStatementEscopo(int cont);
int verificarExpressaoOpcional(int cont);
int verificarParteElse(int cont);
int verificarListaStatement(int cont);
int verificarListaStatementLinha(int cont);
int verificarValorR(int cont);
int verificarValorRLinha(int cont);
int verificarComparacao(int cont);
int verificarMagnitude(int cont);
int verificarMagnitudeLinha(int cont);
int verificarTermo(int cont);
int verificarTermoLinha(int cont);
int verificarFator(int cont);
int verificarAritmetica(int cont);
int verificarAritmeticaOperadorDuplicado(int cont);
int verificarAritmeticaOperadorIgualComposto(int cont);
int verificarStatementDoWhile(int cont);
int verificarSwitch01(int cont);
int verificarSwitch02(int cont);
int verificarListaCase(int cont);
int verificarListaCaseLinha(int cont);
int verificarChamadaFuncao(int cont);
int verificarListaArgChamadaFuncao(int cont);
int verificarListaArgChamadaFuncaoLinha(int cont);

int isAritmetica(Token *aux);
int isComparacao(Token *aux);
int isFator(Token *aux);
int isTipoDeclaracao(Token *aux);
int isAritmeticaOperadorDuplicado(Token *aux);
int isAritmeticaOperadorIgualComposto(Token *aux);


#endif // SINTATICO_H_INCLUDED