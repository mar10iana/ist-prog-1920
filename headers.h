#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 100
#define ID 4

typedef struct posicao{
    float x;
    float y;
}POSICAO;

typedef struct contacto{
    POSICAO xy;
    int dia;
    char id_contacto[ID];
}CONTACTO;

typedef struct lista_c{
    CONTACTO contacto;
    struct lista_c* prox;
}LISTA_C;

typedef struct individuo{
    int dia_contagio;
    int dia_contacto_risco;
    char id_individuo[ID];
    LISTA_C* p_contacto;
}INDIVIDUO;

typedef struct lista_i{
    INDIVIDUO individuo;
    struct lista_i* prox_individuo;
}LISTA_I;

FILE * abre_ficheiros_r(char *nome_ficheiro, FILE *saida);
void erro_alocacao_I(LISTA_I *topo1, FILE *saida);
void erro_alocacao_C(LISTA_C *topo1, FILE *saida);
LISTA_I * cria_bloco_i(INDIVIDUO x, LISTA_I *ap);
LISTA_I * leitura_ids(char line [MAXSTR], FILE *saida);
LISTA_I * cria_lista_i(LISTA_I *topo, LISTA_I *novo, FILE *saida, int i);
LISTA_C * cria_bloco_c(CONTACTO x, LISTA_C *ap);
LISTA_C * leitura_cont(char line[MAXSTR], FILE *saida);
LISTA_C * cria_lista_c(LISTA_C *topo, LISTA_C *novo, LISTA_I *topo1, FILE *saida);
void imprime_listas(LISTA_I *topo, FILE *dados2);
void contagem(LISTA_I *topo, FILE *saida);
LISTA_C * insere_dados_no_contacto(POSICAO xy,int d,FILE*saida,char ident[ID]);
LISTA_C * insere_contacto(LISTA_C *topo, LISTA_C* novo);
LISTA_I * insere_individuo(LISTA_I *topo,FILE *saida,
                           LISTA_C *novo1, LISTA_C *novo2);
LISTA_I * novo_contacto(LISTA_C *novo1, LISTA_C *novo2, LISTA_I *topo,FILE *saida);
void procura_contacto(char ident[ID], int d, FILE *saida, LISTA_I *topo);
void contactos_mutuos(LISTA_I *topo, char ident1[ID], char ident2[ID], FILE *saida);
LISTA_I * apaga_contacto(LISTA_I *topo, FILE *saida, char ident[ID], int d);
LISTA_I * diagnosticado(char ident[ID], int dia, LISTA_I *topo,FILE *saida);
void cadeia_de_contactos2(LISTA_I *topo, LISTA_I *auxi2, LISTA_C *auxc2, char ident1[], FILE *saida);
void cadeia_de_contactos(LISTA_I *topo, char ident1[ID], int intervalo, FILE *saida);
LISTA_I * le_linha_de_comando(int argc, char *argv[], LISTA_I *topo1, FILE *saida);
lista_paragens * update_paragem(char nome[PARAGEM_MAX], lista_paragens * topo);
paragem_struct return_paragem(char nome[PARAGEM_MAX], lista_paragens *topo);
lista_paragens* cria_lista_paragens(paragem_struct paragem);
lista_carreiras * update_carreira(char nome[CARREIRA_MAX], lista_carreiras * topo, 
    float custo, float duracao, paragem_struct origem, paragem_struct destino);

#endif
