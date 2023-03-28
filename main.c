#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"
#include "funcoes.c"

int main(int argc, char*argv[])
{
    FILE *dados1, *saida, *dados2;
    char line[MAXSTR];
    char *p_reto1, *p_reto2;
    LISTA_I *topo1=NULL, *novo1;
    LISTA_C *topo2, *novo2;
    int i=0;

    dados2 = fopen(argv[6], "w");
    saida = fopen(argv[2], "w");
    dados1= abre_ficheiros_r(argv[4], saida);

    if(strcmp(argv[1],"-0")!=0 || strcmp(argv[3],"-1")!=0 || strcmp(argv[5],"-2")!=0)
    {
        fprintf(saida,"Linha de comando invalida\n");
        return 0;
    }

    topo1 = (LISTA_I *)calloc(1 ,sizeof(LISTA_I));
    erro_alocacao_I(topo1, saida);
    topo1 -> prox_individuo = NULL;
    topo2 = (LISTA_C *)calloc(1 ,sizeof(LISTA_C));
    erro_alocacao_C(topo2, saida);

    while (fgets(line, MAXSTR, dados1)!= NULL)
    {
        if (linha_branca(line)==1)
        {
            p_reto1=strchr(line,'[');
            p_reto2=strchr(line,']');
            if(p_reto1!= NULL)
            {
                novo1= leitura_ids(line, saida);
                topo1 = cria_lista_i(topo1, novo1, saida, i);
                i=1;
                topo2 = NULL;
            }
            else if(p_reto2 == NULL)
            {
                novo2 = leitura_cont(line, saida);
                topo2 = cria_lista_c(topo2, novo2, topo1, saida);
            }
        }
    }

    topo1 = le_linha_de_comando(argc,argv,topo1,saida);

    imprime_listas(topo1, dados2);

    return 0;
}
