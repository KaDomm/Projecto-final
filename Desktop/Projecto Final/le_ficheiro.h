#ifndef LE_FICHEIRO_H
#define LE_FICHEIRO_H

#include <stdio.h>
#include <stdlib.h>
#include <g2.h>
#include <g2_X11.h>
#include <string.h>
#include "lista.h"
#include "estruturas.h"

#define MASK_DRT 0x0100
#define MASK_ESQ 0x0400
#define DEV dados->device.dev
#define D dados->device.d
#define JANX dados->janela.x
#define JANY dados->janela.y
#define ZONA_Y_BARRA YM >= JANY-40 && YM <= JANY-5
#define LIMITE_MENOR_X dados->referencial.xmenor
#define LIMITE_MAIOR_X dados->referencial.xmaior
#define LIMITE_MENOR_Y dados->referencial.ymenor
#define LIMITE_MAIOR_Y dados->referencial.ymaior
#define CENTRO_Y dados->centro.y
#define CENTRO_X dados->centro.x
#define RAIO_ESTRELA bases[0].raio
#define RAIO_PLANETA bases[1].raio
#define RAIO_ASTEROIDE bases[2].raio
#define RAIO_FRAGMENTO bases[3].raio
#define XM state->pos_rato.x
#define YM state->pos_rato.y
#define ZOOM state->zoom
#define SPEED state->indice_speed
#define BOT_RATO state->clique
#define CONTROLO state->ctrl
#define NUM_SAVE state->num_ficheiro_save
#define FICH_LIDO state->ficheiro
#define POS_X ap->dado_util.pos_print.x
#define POS_Y ap->dado_util.pos_print.y

/************************************************************/

void inicia_estrutura_state ( STATE *state, char *argv[] );

int avalia_ficheiro ( char *argv[], DADOS *dados, STATE *state, VECTOR_BASES bases[] );

int le_ficheiro ( char str[], DADOS *dados, STATE *state, VECTOR_BASES bases[] );

void distribui_dados ( DADOS *dados, FILE *fp, VECTOR_BASES bases[] );

void abre_janela ( DADOS *dados );

void actualiza_ecran ( DADOS *dados, STATE *state, VECTOR_BASES bases[] );

void insere_background ( DADOS *dados );

void insere_barra ( DADOS *dados );

void imprime_referencial ( DADOS *dados, STATE *state );

void captura_rato ( STATE *state, DADOS *dados );

int avalia_so_1_clique ( STATE *state, DADOS *dados, VECTOR_BASES bases[] );

int avalia_posicao_rato ( STATE *state, DADOS *dados, VECTOR_BASES bases[] );

void end ( DADOS *dados );

void avalia_zoom ( STATE *state, DADOS *dados );

void save ( VECTOR_BASES bases[], STATE *state, DADOS *dados );

void imprime_corpos( VECTOR_BASES bases[], STATE *state, DADOS *dados );

void pixel_ref ( DADOS *dados, STATE *state );

#endif