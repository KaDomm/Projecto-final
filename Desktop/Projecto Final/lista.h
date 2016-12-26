#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <g2.h>
#include <g2_X11.h>
#include "estruturas.h"
#include "le_ficheiro.h"

#define IDENTIFICACAO ap->dado_util.ident
#define COR ap->dado_util.cor
#define MASSA ap->dado_util.massa
#define COORDENADAS_X ap->dado_util.coordenadas.x
#define POS_PRINT_X ap->dado_util.pos_print.x
#define COORDENADAS_Y ap->dado_util.coordenadas.y
#define POS_PRINT_Y ap->dado_util.pos_print.y
#define VEL_X ap->dado_util.velocidade.vx
#define VEL_Y ap->dado_util.velocidade.vy
#define X_RECEBIDO ap->dado_util.coordenadas.x
#define Y_RECEBIDO ap->dado_util.coordenadas.y
#define RAIO bases[i].raio
#define ESTRELA 0
#define PLANETA 1
#define ASTEROIDE 2
#define FRAGMENTO 3


/**************************************************************************/

void inicia_vector_bases ( VECTOR_BASES bases[], DADOS dados );

void add ( VECTOR_BASES bases[], DADOS *dados );

int pede_dados_utilizador ( char v[], int tipo );

int avalia_input ( char v[], VECTOR_BASES bases[], DADOS *dados, int tipo );

int define_cor ( char cor[] );

void imprime_instrucoes ( void );

void abre_janela_apoio ( char cor[] );

int avalia_identificacao ( char v[], VECTOR_BASES bases[], int tipo );

int iserir_elemento (  VECTOR_BASES bases[], int tipo, char v[] );

int mostra_elementos ( VECTOR_BASES bases[], float zona[] );

void mostra_corpo_celeste ( ESTRUTURA *ap, int i );

void remove_ ( STATE *state, VECTOR_BASES bases[], DADOS *dados );

int select_zona ( STATE *state, DADOS *dados, float zona[] );

int procura_corpo_celeste ( char remov[], ESTRUTURA *base_do_tipo, ESTRUTURA **ap );

void remove_corpo_celeste ( ESTRUTURA *ap_actual, ESTRUTURA **base_do_tipo );

void liberta_lista ( VECTOR_BASES bases[] );

void actualiza_posicao ( VECTOR_BASES bases[] );

void actualiza_pos_print ( VECTOR_BASES bases[], STATE state, DADOS *dados );


#endif