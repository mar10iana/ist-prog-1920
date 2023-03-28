#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"

/*-------------------------------------------------------------------------------------
| Nome da funcao: linha_branca
| Tipo: int
| Argumentos: char line []
| Funcao: A funcao linha_branca verifica se uma linha e composta so por espacos. Esta funcao
| e util na leitura de ficheiros uma vez que evita problemas no programa caso o
| ficheiro possua linhas em branco.
| Sempre que se verifique que a linha lida possui informacao, e retornado o valor 1.
+------------------------------------------------------------------------------------*/

int linha_branca(char line[])
{
    int i=0;
    while (line[i]!='\n')
    {
        if (line[i]!=' ')
        {
            return 1;
        }
        i = i + 1;
    }
    return 2;
}

/*---------------------------------------------------------------------------------
| Nome da funcao: abre_ficheiros_r
| Tipo: FILE *
| Argumentos: char *nome_ficheiro, FILE *saida
| Funcao: Esta funcao abre os ficheiros para ler e se ele nao existir
| imprime um aviso e acaba o programa
+--------------------------------------------------------------------------------*/

FILE * abre_ficheiros_r(char *nome_ficheiro,FILE *saida)
{
    FILE *fp;
    fp = fopen(nome_ficheiro, "r");
    if (fp == NULL)
    {
        fprintf(saida,"Ficheiro nao encontrado\n");
        return 0;
    }
    else
        return fp;
}

/*---------------------------------------------------------------------------------
| Nome da funcao: erro_alocacao_memoria_I
| Tipo: void
| Argumentos: LISTA_I *topo1, FILE *saida
| Funcao: Esta funcao testa a alocacao de memoria
| emitindo uma mensagem se esta for mal sucedida
+--------------------------------------------------------------------------------*/

void erro_alocacao_I(LISTA_I *topo1,FILE *saida)
{
    if (topo1 == NULL)
    {
        fprintf(saida,"Erro na alocacao de memoria\n");
        exit (0);
    }
}

/*---------------------------------------------------------------------------------
| Nome da funcao: erro_alocacao_memoria_C
| Tipo: void
| Argumentos: LISTA_I *topo1, FILE *saida
| Funcao: Esta funcao testa a alocacao de memoria
| emitindo uma mensagem se esta for mal sucedida
+--------------------------------------------------------------------------------*/

void erro_alocacao_C(LISTA_C *topo1,FILE *saida)
{
    if (topo1 == NULL)
    {
        fprintf(saida,"Erro na alocacao de memoria\n");
        exit (0);
    }
}

/*---------------------------------------------------------------------------------
| Nome da funcao: cria_bloco_i
| Tipo: LISTA_I *
| Argumentos: INDIVIDUO x, LISTA_I *ap
| Funcao: Esta funcao atribui o individuo ao bloco de memoria
| previamente alocado.
+--------------------------------------------------------------------------------*/

LISTA_I * cria_bloco_i(INDIVIDUO x, LISTA_I *ap)
{
        ap -> individuo = x;

        ap -> prox_individuo = NULL;

        return ap;
}

/*---------------------------------------------------------------------------------
| Nome da funcao: leitura_ids
| Tipo: LISTA_I *
| Argumentos: char line [MAXSTR],FILE *saida
| Funcao: Esta funcao aloca memoria e atribui a uma estrutura do tipo INDIVIDUO
| as informacoes que obteve da linha lida do ficheiro.
+--------------------------------------------------------------------------------*/

LISTA_I * leitura_ids(char line [MAXSTR],FILE *saida){
    char individuo[ID] = {"\0"};
    int contagio, contacto;
    LISTA_I *ap;
    INDIVIDUO x;
    int i;

    ap = (LISTA_I*)calloc(1, sizeof(LISTA_I));
    erro_alocacao_I(ap,saida);

    i = sscanf(line,"[ %s %d %d", individuo, &contagio, &contacto);

    if(i == 3)
    {
        strcpy(x.id_individuo, individuo);
        x.dia_contagio = contagio;
        x.dia_contacto_risco = contacto;

        ap = cria_bloco_i(x, ap);

        return ap;
    }

    return NULL;
}

/*--------------------------------------------------------------------------------
| Nome da funcao: cria_lista_I
| Tipo: LISTA_I *
| Argumentos: LISTA_I *topo, LISTA_I *novo, FILE *saida, int i
| Funcao: Esta funcao cria a lista dos individuos se os dados destes forem validos.
| Existe uma criacao da lista como fila, mas com a possibilidade de remocao de
| qualquer elemento.
+---------------------------------------------------------------------------------*/

LISTA_I * cria_lista_i(LISTA_I *topo,LISTA_I *novo,FILE *saida,int i)
{
    if(novo == NULL)
    {
        fprintf(saida,"Dados invalidos\n");
        return 0;
    }

    LISTA_I* aux;

    if (i == 0)
        topo = novo;

    else
    {
        aux = topo;

        while (aux -> prox_individuo != NULL)
        {
            aux = aux -> prox_individuo;
        }
        aux -> prox_individuo = novo;
    }

    return topo;
}

/*----------------------------------------------------------------------------------
| Nome da funcao: cria_bloco_c
| Tipo: LISTA_C *
| Argumentos: CONTACTO x, LISTA_C *ap
| Funcao: Funcao: Esta funcao atribui o contacto ao bloco de memoria
| previamente alocado.
+-------------------------------------------------------------------------------*/

LISTA_C * cria_bloco_c(CONTACTO x,LISTA_C *ap)
{
        ap -> contacto = x;

        ap -> prox = NULL;

        return ap;
}

/*----------------------------------------------------------------------------------
| Nome da funcao: leitura_cont
| Tipo: LISTA_C *
| Argumentos: char line[MAXSTR], FILE *saida
| Funcao: Esta funcao aloca memoria e atribui a uma estrutura do tipo CONTACTO
| as informacoes que obteve da linha lida do ficheiro.
+--------------------------------------------------------------------------------*/

LISTA_C * leitura_cont(char line[MAXSTR],FILE *saida)
{
    char ident[ID] = {"\0"};
    int d;
    POSICAO p;
    LISTA_C *ap;
    CONTACTO x;
    int i;

    ap = (LISTA_C*)calloc(1, sizeof(LISTA_C));
    erro_alocacao_C(ap,saida);

    i = sscanf(line, "%s %f %f %d", ident, &p.x, &p.y, &d);

    if(i == 4)
    {
        strcpy(x.id_contacto, ident);
        x.xy = p;
        x.dia = d;

        ap = cria_bloco_c(x, ap);

        return ap;
    }

    return NULL;
}

/*-----------------------------------------------------------------------------------
| Nome da funcao: cria_lista_C
| Tipo: LISTA_C *
| Argumentos: LISTA_C *topo, LISTA_C *novo, LISTA_I *topo1, FILE *saida
| Funcao: Esta funcao cria a lista dos individuos se os dados destes forem validos.
| Existe uma criacao da lista como fila, mas com a possibilidade de remocao de
| qualquer elemento.
+------------------------------------------------------------------------------------*/

LISTA_C * cria_lista_c(LISTA_C *topo,LISTA_C *novo,LISTA_I *topo1,FILE *saida)
{
    LISTA_C* aux=NULL;
    LISTA_I* aux1 = topo1;

    if(novo == NULL)
    {
        fprintf(saida,"Dados invalidos\n");
        return 0;
    }

    if (topo == NULL)
        topo = novo;

    else
    {
        aux = topo;

        while (aux -> prox != NULL)
        {
            aux = aux -> prox;
        }

        aux -> prox = novo;
    }

    while(aux1->prox_individuo != NULL)
    {
        aux1 = aux1->prox_individuo;
    }

    aux1->individuo.p_contacto = topo;

    return topo;
}

/*----------------------------------------------------------------------------
| Nome da funcao: imprime_listas
| Tipo: void
| Argumentos: LISTA_I* topo, FILE *dados2
| Funcao: Imprime num ficheiro os dados das listas com a
| mesma organizacao do ficheiro lido
+----------------------------------------------------------------------------*/

void imprime_listas(LISTA_I *topo, FILE *dados2)
{
    LISTA_I *aux = topo;
    LISTA_C *aux2=NULL;

    while(aux!=NULL)
    {
        aux2 = aux -> individuo.p_contacto;

        fprintf(dados2, "[ %s %d %d\n", aux->individuo.id_individuo,
               aux->individuo.dia_contagio, aux->individuo.dia_contacto_risco);

        while(aux2 != NULL)
        {
            fprintf(dados2, "%s %.1f %.1f %d\n", aux2->contacto.id_contacto, aux2->contacto.xy.x,
                   aux2->contacto.xy.y, aux2->contacto.dia);
            aux2 = aux2 -> prox;
        }
        fprintf(dados2, "]\n");

        aux = aux -> prox_individuo;
    }
}

/*----------------------------------------------------------------------------
| Nome da funcao: contagem
| Tipo: void
| Argumentos: LISTA_I *topo, FILE *saida
| Funcao: determina o numero total de smartphones e de contactos, imprimindo
| estes valores num ficheiro
+----------------------------------------------------------------------------*/
void contagem (LISTA_I *topo, FILE *saida)
{
    LISTA_I *auxi = topo;
    LISTA_C *auxc=NULL;
    int i = 0, c = 0;

    while (auxi != NULL)
    {
        auxc = auxi->individuo.p_contacto;

        while(auxc != NULL)
        {
            c = c + 1;
            auxc = auxc->prox;
        }

        i = i + 1;
        auxi = auxi->prox_individuo;
    }

    fprintf(saida, "%d %d", i, c);
}
/*-----------------------------------------------------------------------------
| Nome da fun��o: insere_dados_no_contacto
| Argumentos: POSICAO xy, int d, FILE*saida
| Fun�ao: Esta funcao aloca memoria e atribui a uma estrutura do tipo LISTA_C
| as informacoes que obteve da linha de comando
+--------------------------------------------------------------------------------*/
LISTA_C * insere_dados_no_contacto(POSICAO xy,int d,FILE*saida, char ident[ID])
{
    LISTA_C *novo;

    novo = (LISTA_C*)calloc(1, sizeof(LISTA_C));
    erro_alocacao_C(novo,saida);

    novo->contacto.dia = d;
    novo->contacto.xy= xy;
    strcpy(novo->contacto.id_contacto,ident);

    return novo;
}
/*----------------------------------------------------------------------------
| Nome da funcao: insere_contacto
| Tipo: LISTA_C *
| Argumentos:LISTA_C *topo, char ident[ID] LISTA_C* novo
| Funcao: Insere um novo elemento na lista de contactos de um indiv�duo tendo
| em conta a ordem cronologica e alfab�tica
+----------------------------------------------------------------------------*/

LISTA_C * insere_contacto(LISTA_C *topo,LISTA_C* novo)
{
    LISTA_C *ant=topo, *auxc=topo;
    char ident[ID];
    strcpy(ident,novo->contacto.id_contacto);

    if((topo->contacto.dia<novo->contacto.dia) ||
       (topo->contacto.dia==novo->contacto.dia
        && strcmp(topo->contacto.id_contacto,novo->contacto.id_contacto)>0))
    {
        novo->prox=topo;
        return novo;
    }
    while(auxc->prox!=NULL)
    {
        if(auxc->contacto.dia > novo->contacto.dia)
        {
            ant = auxc;
            auxc = auxc -> prox;
        }

        if(auxc->contacto.dia == novo->contacto.dia)
        {
            while(auxc->prox!=NULL && strcmp(auxc->contacto.id_contacto,ident)<0)
            {
                ant = auxc;
                auxc = auxc->prox;
            }

            if(strcmp(auxc->contacto.id_contacto,ident)==0
               && auxc->contacto.xy.x==novo->contacto.xy.x
               && auxc->contacto.xy.y==novo->contacto.xy.y)
                return topo;

            ant->prox = novo;
            novo->prox = auxc;
            break;
        }

        if(auxc->contacto.dia < novo->contacto.dia)
        {
            ant->prox = novo;
            novo->prox = auxc;
            break;
        }
    }
    if(auxc->prox == NULL)
    {
        auxc->prox = novo;
        novo->prox = NULL;
    }
    return topo;
}

/*----------------------------------------------------------------------------
| Nome da funcao: insere_individuo
| Tipo: LISTA_I *
| Argumentos:
| Funcao: Insere um novo elemento na lista de indiv�duos tendo
| em conta a ordem alfab�tica
+----------------------------------------------------------------------------*/

LISTA_I * insere_individuo(LISTA_I *topo,FILE *saida,
                           LISTA_C *novo1,LISTA_C *novo2)
{
    LISTA_I *ant=NULL, *aux=topo, *novo;
    char ident[ID];
    strcpy(ident,novo2->contacto.id_contacto);

    novo = (LISTA_I*)calloc(1, sizeof(LISTA_I));
    erro_alocacao_I(novo,saida);

    novo->individuo.dia_contacto_risco= -1;
    novo->individuo.dia_contagio=-1;
    strcpy(novo->individuo.id_individuo,ident);
    novo1->prox=NULL;
    novo->individuo.p_contacto = novo1;

    if(strcmp(topo->individuo.id_individuo,ident)>0)
    {
        novo->prox_individuo=topo;
        return novo;
    }
    while((strcmp(aux->individuo.id_individuo,ident)<0) && (aux->prox_individuo!=NULL))
    {
        ant = aux;
        aux = aux->prox_individuo;
    }
    if(aux->prox_individuo == NULL)
    {
        aux->prox_individuo= novo;
        novo->prox_individuo = NULL;
    }
    else
    {
        ant->prox_individuo = novo;
        novo->prox_individuo = aux;
    }
    return topo;
}

/*----------------------------------------------------------------------------
| Nome da funcao: novo_contacto
| Tipo: LISTA_I *
| Argumentos:char ident1[ID], char ident2[ID], float a, float b,
| int d, FILE *saida, LISTA_I *topo
| Funcao: Regista um novo contacto na lista de contactos de cada um dos
| individuos
+----------------------------------------------------------------------------*/

LISTA_I *novo_contacto(LISTA_C *novo1, LISTA_C *novo2, LISTA_I *topo,FILE *saida)
{
    LISTA_I *auxi = topo;
    int i=0, j=0;

    while(auxi != NULL)
    {
        if(strcmp(auxi->individuo.id_individuo,novo1->contacto.id_contacto) == 0)
        {
            auxi->individuo.p_contacto = insere_contacto(auxi->individuo.p_contacto,novo2);
            i=1;
        }
        if(strcmp(auxi->individuo.id_individuo,novo2->contacto.id_contacto) == 0)
        {
            auxi->individuo.p_contacto = insere_contacto(auxi->individuo.p_contacto,novo1);
            j=1;
        }
        auxi=auxi->prox_individuo;
    }
    if(i!=1)
    {
        topo= insere_individuo(topo,saida,novo2,novo1);
    }
    if(j!=1)
    {
        topo= insere_individuo(topo,saida,novo1,novo2);
    }
    return topo;
}

/*----------------------------------------------------------------------------
| Nome da funcao: procura_contacto
| Tipo: void
| Argumentos: char ident[ID], int dia, FILE *saida, LISTA_I *topo
| Funcao: Esta funcao procura os contactos de um smartphone num dia especifico
| e escreve os mesmos no ficheiro saida.
+----------------------------------------------------------------------------*/

void procura_contacto(char ident[ID], int d, FILE *saida, LISTA_I *topo)
{
    LISTA_I *aux = topo;
    LISTA_C *aux1=NULL;
    int i=0;

    while(aux != NULL)
    {
        if(strcmp(ident, aux->individuo.id_individuo) == 0)
        {
            aux1 = aux-> individuo.p_contacto;
            while(aux1 != NULL)
            {
                if(d == -1)
                {
                    i=1;
                    fprintf(saida, "%s %s %.1f %.1f %d\n", ident, aux1->contacto.id_contacto,
                            aux1->contacto.xy.x, aux1->contacto.xy.y, aux1->contacto.dia);
                }
                else if(d == aux1->contacto.dia)
                {
                    i=1;
                    fprintf(saida, "%s %s %.1f %.1f %d\n", ident, aux1->contacto.id_contacto,
                            aux1->contacto.xy.x, aux1->contacto.xy.y, aux1->contacto.dia);
                }
                aux1 = aux1-> prox;
            }
        }
        aux = aux->prox_individuo;
    }
    if(i==0)
        fprintf(saida,"0");
}

/*----------------------------------------------------------------------------
| Nome da funcao: contactos_mutuos
| Tipo: void
| Argumentos: char ident1[ID], char ident2[ID], FILE *saida
| Funcao: Esta funcao procura contactos mutuos entre dois individuos e
| escreve os mesmos no ficheiro saida.
+----------------------------------------------------------------------------*/

void contactos_mutuos(LISTA_I *topo, char ident1[ID], char ident2[ID], FILE *saida)
{
    int cont = 0;
    LISTA_I *auxi1 = topo, *auxi2 = topo;
    LISTA_C *auxc1=NULL, *auxc2=NULL;

    while(strcmp(ident1, auxi1->individuo.id_individuo) != 0)
        auxi1 = auxi1-> prox_individuo;

    while(strcmp(ident2, auxi2->individuo.id_individuo) != 0)
        auxi2 = auxi2-> prox_individuo;

    auxc1= auxi1->individuo.p_contacto;
    auxc2= auxi2->individuo.p_contacto;

    while(auxc1 != NULL)
    {
        while(auxc2!= NULL)
        {
            if(strcmp(ident1, auxc2->contacto.id_contacto) == 0
               && strcmp(ident2, auxc1->contacto.id_contacto) ==0)
            {
                cont = cont + 1;

                fprintf(saida, "%s %s %.1f %.1f %d\n", ident1, ident2,
                        auxc2 -> contacto.xy.x, auxc2 -> contacto.xy.y,
                        auxc2 -> contacto.dia);
            }
            auxc2 = auxc2 -> prox;
        }
        auxc1 = auxc1 -> prox;
    }

    if(cont == 0)
        fprintf(saida, "0");
}

/*----------------------------------------------------------------------------
| Nome da funcao: apaga_contacto
| Tipo: LISTA_I *
| Argumentos: LISTA_I *topo, FILE *saida, char ident[ID], int d
| Funcao: Esta funcao apaga os contactos correspondentes a um identificador
| numa dada e escreve no ficheiro saida a inform��o dos contactos apagados.
| Se um identificador ficar sem contactos associados esta apaga esse
| identificador
+----------------------------------------------------------------------------*/

LISTA_I * apaga_contacto(LISTA_I *topo, FILE *saida, char ident[ID], int d)
{
    LISTA_I *auxi1=topo, *auxi2=topo, *anti1=topo, *anti2=topo;
    LISTA_C *auxc1=NULL, *auxc2=NULL, *antc1=NULL, *antc2=NULL;
    char ch[MAXSTR][ID];
    int i=0,j=0,cont=0;

    while(auxi1!=NULL)
    {
        auxc1 = auxi1-> individuo.p_contacto;
        antc1 = auxc1;
        if(strcmp(ident, auxi1->individuo.id_individuo)==0)
        {
            if(auxi1->individuo.p_contacto->contacto.dia == d)
            {
                while(auxi1->individuo.p_contacto->prox!=NULL)
                {
                    auxi1->individuo.p_contacto = auxi1->individuo.p_contacto->prox;
                    strcpy(ch[i],auxi1->individuo.p_contacto->contacto.id_contacto);
                    fprintf(saida, "%s %s %.1f %.1f %d\n", auxi1->individuo.id_individuo, auxc1->contacto.id_contacto,
                                auxc1->contacto.xy.x, auxc1->contacto.xy.y, auxc1->contacto.dia);
                    fprintf(saida, "%s %s %.1f %.1f %d\n", auxc1->contacto.id_contacto, auxi1->individuo.id_individuo,
                                auxc1->contacto.xy.x, auxc1->contacto.xy.y, auxc1->contacto.dia);
                    i++;
                }
                if(auxi1->individuo.p_contacto->prox==NULL)
                {
                    strcpy(ch[i],auxi1->individuo.p_contacto->contacto.id_contacto);
                    fprintf(saida, "%s %s %.1f %.1f %d\n", auxi1->individuo.id_individuo, auxc1->contacto.id_contacto,
                                auxc1->contacto.xy.x, auxc1->contacto.xy.y, auxc1->contacto.dia);
                    fprintf(saida, "%s %s %.1f %.1f %d\n", auxc1->contacto.id_contacto, auxi1->individuo.id_individuo,
                                auxc1->contacto.xy.x, auxc1->contacto.xy.y, auxc1->contacto.dia);
                    i++;
                    if(cont==0)
                        topo= topo->prox_individuo;
                    else
                        anti1->prox_individuo=auxi1->prox_individuo;
                }
            }
            else
            {
                while(auxc1->prox != NULL)
                {
                    if(auxc1->contacto.dia == d)
                    {
                        strcpy(ch[i],auxc1->contacto.id_contacto);
                        antc1->prox = auxc1->prox;
                        fprintf(saida, "%s %s %.1f %.1f %d\n", auxi1->individuo.id_individuo, auxc1->contacto.id_contacto,
                                auxc1->contacto.xy.x, auxc1->contacto.xy.y, auxc1->contacto.dia);
                        fprintf(saida, "%s %s %.1f %.1f %d\n", auxc1->contacto.id_contacto, auxi1->individuo.id_individuo,
                                auxc1->contacto.xy.x, auxc1->contacto.xy.y, auxc1->contacto.dia);
                        i++;
                    }
                    else
                        antc1 = auxc1;
                    auxc1 = auxc1->prox;
                }
                if(auxc1->prox == NULL && auxc1->contacto.dia == d)
                {
                    strcpy(ch[i],auxc1->contacto.id_contacto);
                    antc1->prox=NULL;
                    fprintf(saida, "%s %s %.1f %.1f %d\n", auxi1->individuo.id_individuo, auxc1->contacto.id_contacto,
                                auxc1->contacto.xy.x, auxc1->contacto.xy.y, auxc1->contacto.dia);
                    fprintf(saida, "%s %s %.1f %.1f %d\n", auxc1->contacto.id_contacto, auxi1->individuo.id_individuo,
                                auxc1->contacto.xy.x, auxc1->contacto.xy.y, auxc1->contacto.dia);
                    i++;
                }
            }
        }
        cont ++;
        anti1 = auxi1;
        auxi1 = auxi1->prox_individuo;
    }
    while(j<MAXSTR)
    {
        cont = 0;
        auxi2=topo;
        anti2=topo;
        while(auxi2!=NULL)
        {
            if(strcmp(auxi2->individuo.id_individuo,ch[j])==0)
            {
                auxc2=auxi2->individuo.p_contacto;
                antc2=auxc2;

                if(strcmp(auxi2->individuo.p_contacto->contacto.id_contacto, ident)==0
                   && auxi2->individuo.p_contacto->contacto.dia == d)
                {
                    while(auxi2->individuo.p_contacto->prox!=NULL)
                        auxi2->individuo.p_contacto = auxi2->individuo.p_contacto->prox;

                    if(auxi2->individuo.p_contacto->prox==NULL)
                    {
                        if(cont==0)
                            topo= topo->prox_individuo;
                        else
                            anti2->prox_individuo=auxi2->prox_individuo;
                    }
                }
                else
                {
                    while(auxc2->prox!=NULL)
                    {
                        if(strcmp(auxc2->contacto.id_contacto, ident)==0
                           && auxc2->contacto.dia == d)
                               antc2->prox = auxc2->prox;
                        antc2=auxc2;
                        auxc2=auxc2->prox;
                    }
                    if(auxc2->prox == NULL && strcmp(auxc2->contacto.id_contacto, ident)==0
                           && auxc2->contacto.dia == d)
                           antc2->prox = NULL;
                    }
            }
            cont++;
            anti2 = auxi2;
            auxi2 = auxi2->prox_individuo;
        }
        j++;
    }
    if(i==0)
        fprintf(saida, "0\n");
    return topo;
}

/*----------------------------------------------------------------------------
| Nome da funcao: diagnosticado
| Tipo: LISTA_I *
| Argumentos: char ident[ID], int dia, LISTA_I *topo,FILE *saida
| Funcao: Esta funcao marca um identificador como tendo sido diagnosticado
| infetado numa dada data e imprime no ficheiro saida os contactos de
| risco diretos, retornando o topo da lista de individuos.
+----------------------------------------------------------------------------*/

LISTA_I* diagnosticado(char ident[ID], int dia, LISTA_I *topo,FILE *saida)
{
    LISTA_I *aux=topo;
    LISTA_C *auxc=NULL;
    int i=0;

    while(aux != NULL)
    {
        auxc = aux->individuo.p_contacto;

        if(strcmp(ident,aux->individuo.id_individuo)==0 && dia!=-1)
        {
            aux->individuo.dia_contagio = dia;

            while(auxc!=NULL)
            {
               i=1;
               fprintf(saida, "%s %s %.1f %.1f %d\n",aux->individuo.id_individuo, auxc->contacto.id_contacto,
                            auxc->contacto.xy.x, auxc->contacto.xy.y, auxc->contacto.dia);
               auxc = auxc->prox;
            }
        }
        aux= aux->prox_individuo;
    }
    if(i==0)
        fprintf(saida,"0");

    return topo;
}

/*----------------------------------------------------------------------------
| Nome da funcao:
| Tipo:
| Argumentos:
| Funcao:
+----------------------------------------------------------------------------*/


void cadeia_de_contactos2(LISTA_I *topo, LISTA_I *auxi2, LISTA_C *auxc2, char ident1[], FILE *saida)
{
    LISTA_I *auxi = topo;
    LISTA_C *auxc = NULL;

    while (auxi != NULL)
    {
        if (strcmp(auxc2->contacto.id_contacto, auxi->individuo.id_individuo) == 0)
        {
            auxc = auxi->individuo.p_contacto;
            break;
        }
        auxi = auxi->prox_individuo;
    }

    while(auxc != NULL)
    {

        if ((auxc->contacto.dia >= auxc2->contacto.dia) && (strcmp(auxc->contacto.id_contacto, ident1)!= 0))
        {
            fprintf(saida, "%s %s %.1f %.1f %d \n",auxi->individuo.id_individuo, auxc->contacto.id_contacto,
                            auxc->contacto.xy.x, auxc->contacto.xy.y, auxc->contacto.dia);

            strcpy(auxi2->individuo.id_individuo, auxc->contacto.id_contacto);

            cadeia_de_contactos2(topo, auxi, auxc, auxi->individuo.id_individuo, saida);
            break;

        }
        auxc= auxc->prox;
    }
}

/*----------------------------------------------------------------------------
| Nome da funcao:
| Tipo:
| Argumentos:
| Funcao:
+----------------------------------------------------------------------------*/


void cadeia_de_contactos(LISTA_I *topo, char ident1[ID], int intervalo, FILE *saida)
{
    LISTA_I *auxi = topo;
    LISTA_C *auxc=NULL;
    int cont = 0;
    int diamin, diamax;

    while (auxi != NULL)
    {
        if (strcmp(ident1, auxi->individuo.id_individuo)==0)
        {
            auxc = auxi->individuo.p_contacto;
            break;
        }
        auxi = auxi->prox_individuo;
    }

    diamax = auxi->individuo.dia_contagio;
    diamin = auxi->individuo.dia_contagio - intervalo;

    while(auxc != NULL)
    {
       if (auxi->individuo.dia_contagio == -1)
            break;

        if ((auxc->contacto.dia >= diamin) && (auxc->contacto.dia <= diamax))
        {
            cont = cont + 1;
            fprintf(saida, "%s %s %.1f %.1f %d \n",ident1, auxc->contacto.id_contacto,
                            auxc->contacto.xy.x, auxc->contacto.xy.y, auxc->contacto.dia);

            cadeia_de_contactos2(topo, auxi, auxc, auxi->individuo.id_individuo, saida);
            break;
        }
    }

    if (cont == 0)
        fprintf(saida, "0");


}

/*---------------------------------------------------------------------------------
| Nome da funcao: le_linha_de_comando
| Tipo: int
| Argumentos: int argc, char *argv[]
| Funcao: Esta funcao verifica se os dados inseridos atrav�s da linha de comando
| sao validos e invoca a funcao definida pelo utilizador, retornando o topo da
| lista de individuos
+--------------------------------------------------------------------------------*/

LISTA_I * le_linha_de_comando(int argc, char *argv[], LISTA_I *topo1, FILE *saida)
{
    int dia;
    int i, j, k;
    POSICAO xy;
    LISTA_C *novoc1, *novoc2;

    if(strcmp(argv[7],"-t")==0 && argc==8)
        contagem(topo1, saida);

    else if(strcmp(argv[7],"-n")==0 && argc==13)
    {
        i=sscanf(argv[10], "%f", &xy.x);
        j=sscanf(argv[11], "%f", &xy.y);
        k=sscanf(argv[12], "%d", &dia);

        if(strlen(argv[8])==3 && strlen(argv[9])==3 && i==1 && j==1 && k==1)
        {
            novoc1 = insere_dados_no_contacto(xy,dia,saida,argv[8]);
            novoc2 = insere_dados_no_contacto(xy,dia,saida,argv[9]);
            topo1 = novo_contacto(novoc1,novoc2,topo1,saida);
            contagem(topo1, saida);
        }
    }
    else if(strcmp(argv[7],"-p")==0 && argc==10)
    {
        i=sscanf(argv[9], "%d", &dia);

        if(strlen(argv[8])==3 && i==1)
            procura_contacto(argv[8],dia,saida,topo1);

    }
    else if(strcmp(argv[7],"-m")==0 && argc==10 && strlen(argv[8])==3 && strlen(argv[9])==3)
        contactos_mutuos(topo1,argv[8],argv[9],saida);

    else if(strcmp(argv[7],"-a")==0 && argc==10)
    {
        i=sscanf(argv[9], "%d", &dia);

        if(strlen(argv[8])==3 && i==1)
            topo1 = apaga_contacto(topo1,saida,argv[8],dia);
    }
    else if(strcmp(argv[7],"-i")==0 && argc==10)
    {
        i=sscanf(argv[9], "%d", &dia);

        if(strlen(argv[8])==3 && i==1)
            topo1 = diagnosticado(argv[8],dia,topo1,saida);
    }
    else if(strcmp(argv[7],"-c")==0 && argc==10)
    {
        i=sscanf(argv[9], "%d", &dia);

        if(strlen(argv[8])==3 && i==1)
            cadeia_de_contactos(topo1, argv[8], dia, saida);
    }
    else
    {
        fprintf(saida,"Linha de comando invalida\n");
        exit (0);
    }

    return topo1;
}
