#ifndef ESTRUTURAS_
#define ESTRUTURAS_

#define MAX 100

typedef struct x_y {
  int x;
  int y;
} TIPO_X_Y;

typedef struct dimension {
  float xmenor;
  float xmaior;
  float ymenor;
  float ymaior;
} DIMENSION;

typedef struct device {
  int d;
  int dev;
} DEVICE;

typedef struct window {
  TIPO_X_Y janela;
  DIMENSION referencial;
  TIPO_X_Y centro;
  DEVICE device;
} DADOS;

/************************************************************/

typedef struct state {
	char ficheiro[MAX];
	int zoom;
	float speed[6];
  int indice_speed;
  TIPO_X_Y pos_rato;
  float convert[4];
  int num_ficheiro_save;
  int ctrl;
  int clique;
} STATE;


/************************************************************/

typedef struct posicao {
  int x;
  int y;
} POSXY;

typedef struct velocidade {
  int vx;
  int vy;
} VELOCIDADE;

typedef struct corpo_celestes {
  char ident[5];
  char cor[MAX];
  int cor_int;
  int massa;
  POSXY coordenadas;
  POSXY pos_print;
  VELOCIDADE velocidade;
} CORPO_CELESTE;


typedef struct estrutura {
  CORPO_CELESTE dado_util;
  struct estrutura *prox;
  struct estrutura *ant;
} ESTRUTURA;

/************************************************************/

typedef struct bases {
  int raio;
  char nome_corpo[MAX];
  ESTRUTURA * corpos;
} VECTOR_BASES;

#endif