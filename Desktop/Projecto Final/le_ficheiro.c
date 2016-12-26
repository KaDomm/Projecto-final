#include "le_ficheiro.h"

/**************************************************************************/

void inicia_estrutura_state ( STATE *state, char *argv[] )
{

  ZOOM= 0;
  state->speed[0]= 0;
  state->speed[1]= 0.5;
  state->speed[2]= 1;
  state->speed[3]= 2;
  state->speed[4]= 4;
  state->speed[5]= 8;
  state->indice_speed= 0;
  NUM_SAVE= 0;
}

/**************************************************************************/

int avalia_ficheiro ( char *argv[], DADOS *dados, STATE *state, VECTOR_BASES bases[] )
{
  if( argv[1] != NULL    &&    strcmp( argv[1], "-f\0" ) == 0 ) {
      if( le_ficheiro( argv[2], dados, state, bases ) == 1 )
        return 1;
  }
  else
    if( le_ficheiro( "sim_config.txt", dados, state, bases ) == 1 )
      return 1;

  return 0;
}

/**************************************************************************/

int le_ficheiro ( char str[], DADOS *dados, STATE *state, VECTOR_BASES bases[] )
{
  FILE * fp;

    strcpy( FICH_LIDO, str );

    fp= fopen( str, "r" );

    if( fp == NULL ) {
      printf( "\n !!! ERRO: a abrir o ficheiro %s! !!!\n\n", str );
      return 1;
    }
    distribui_dados ( dados, fp, bases );

    fclose( fp );

    return 0;
}

/**************************************************************************/

void distribui_dados ( DADOS *dados, FILE *fp, VECTOR_BASES bases[] )
{
  char v[MAX], nome[MAX], id[MAX], aux[MAX], cor[MAX];
  int x[6];

    do {
      fgets( v, sizeof v, fp );
      if( v[0] != '/' && sscanf( v, " %s %d %d", nome, &x[0], &x[1]) >= 2 ) {

        if( strcmp( nome, "JANELA\0" ) == 0 ) { 
          JANX= x[0];
          JANY= x[1]; 
        }
        if( strcmp( nome, "X\0" ) == 0 ) {
          LIMITE_MENOR_X= x[0];
          LIMITE_MAIOR_X= x[1]; 
        } 
        if( strcmp( nome, "Y\0" ) == 0 ) {
          LIMITE_MENOR_Y= x[0];
          LIMITE_MAIOR_Y= x[1]; 
        } 
        if( strcmp( nome, "C\0" ) == 0 ) {
          CENTRO_X= x[0];
          CENTRO_Y= x[1]-21; /* -21 diferença barra */
        }
        if( strcmp( nome, "ESTRELAS\0" ) == 0 )
          RAIO_ESTRELA= x[0]; 
        if( strcmp( nome, "PLANETAS\0" ) == 0 )
          RAIO_PLANETA= x[0];
        if( strcmp( nome, "ASTEROIDES\0" ) == 0 )
          RAIO_ASTEROIDE= x[0];
        if( strcmp( nome, "FRAGMENTOS\0" ) == 0 )
          RAIO_FRAGMENTO= x[0]; 
      }
      else {
       if( v[0] != '/' && sscanf( v, "%s %s %s %d %d %d %d %d %d", nome, id, cor, &x[0], &x[1], &x[2], &x[3], &x[4], &x[5] ) > 5 ) {
          
          sprintf( aux, "%s %s %d %d %d %d %d %d", id, cor, x[0], x[1], x[2], x[3], x[4], x[5] );
          if( strcmp( nome, "Estrela\0" ) == 0 )
            if( avalia_input ( aux, bases, dados, ESTRELA ) == 0 )
              iserir_elemento ( bases, ESTRELA, aux );
          if( strcmp( nome, "Planeta\0" ) == 0 )
            if( avalia_input ( aux, bases, dados, PLANETA ) == 0 )
              iserir_elemento ( bases, PLANETA, aux );
          if( strcmp( nome, "Asteroide\0" ) == 0 )
            if( avalia_input ( aux, bases, dados, ASTEROIDE ) == 0 )
              iserir_elemento ( bases, ASTEROIDE, aux );
          if( strcmp( nome, "Fragmento\0" ) == 0 )
            if( avalia_input ( aux, bases, dados, 3 ) == 0 )
              iserir_elemento ( bases, 3, aux );
        }
      }
    } while( feof( fp ) == 0 );
}

/**************************************************************************/

void abre_janela ( DADOS *dados )
{
  int d, dev;

    dev= g2_open_X11( JANX, JANY );
    d= g2_open_vd( );
    g2_clear( d );
    g2_attach( d, dev );
    g2_set_auto_flush( d, 0 );

    D= d;
    DEV= dev;
}
   
/**************************************************************************/

void actualiza_ecran ( DADOS *dados, STATE *state, VECTOR_BASES bases[] )
{ 

  g2_clear( D );

  g2_set_background ( DEV, 1 );

  imprime_referencial ( dados, state );

  imprime_corpos( bases, state, dados );

  insere_background ( dados );

  insere_barra ( dados );

} 

/**************************************************************************/

void insere_background ( DADOS *dados )
{

  g2_pen( DEV, 1 );
   g2_filled_rectangle( DEV, 4, JANY-40, JANX-4, JANY-5 );
  
  g2_pen( DEV, 0 );
   g2_rectangle( DEV, 3, 3, JANX-3, JANY-4 );
    g2_rectangle( DEV, 2, 2, JANX-2, JANY-3 );
     g2_rectangle( DEV, 1, 1, JANX-1, JANY-1 );

  g2_line( DEV, 3, JANY-41, JANX-3, JANY-41 );
   g2_line( DEV, 3, JANY-42, JANX-3, JANY-42 );

  g2_flush( D );
}

/**************************************************************************/

void insere_barra ( DADOS *dados )
{
  char str[256];

    g2_pen( DEV, 0 );
    g2_set_font_size( DEV, 14 );
  
    sprintf( str, "   RESET" );
     g2_string( DEV, (JANX/16) * 0, JANY-29, str );
      g2_rectangle( DEV, 5, JANY-40, (JANX/16)*2, JANY-5 );
   
    sprintf( str, "  ADD" );
     g2_string( DEV, (JANX/16)*2, JANY-29, str );
      g2_rectangle( DEV, (JANX/16)*2, JANY-40, (JANX/16)*4, JANY-5 );

    sprintf( str, "  REMOVE" );
     g2_string( DEV, (JANX/16)*4, JANY-29, str );
      g2_rectangle( DEV, (JANX/16)*4, JANY-40, (JANX/16)*6, JANY-5 );
     
    sprintf( str, "  SAVE" );
     g2_string( DEV, (JANX/16)*6, JANY-29, str );
      g2_rectangle( DEV, (JANX/16)*6, JANY-40, (JANX/16)*8, JANY-5 );
     
    sprintf( str, "  END" );
     g2_string( DEV, (JANX/16)*8, JANY-29, str );
      g2_rectangle( DEV, (JANX/16)*8, JANY-40, (JANX/16)*10, JANY-5 );
     
    sprintf( str, "  SPEED" );
     g2_string( DEV, (JANX/16)*10, JANY-29, str );
      g2_rectangle( DEV, (JANX/16)*10, JANY-40, (JANX/16)*12, JANY-5 );
     
    sprintf( str, "  ZOOM" );
     g2_string( DEV, (JANX/16)*12, JANY-29, str );
      g2_rectangle( DEV, (JANX/16)*12, JANY-40, (JANX/16)*14, JANY-5 );
     
    sprintf( str, "  TRIAL" );
     g2_string( DEV, (JANX/16)*14, JANY-29, str );
      g2_rectangle( DEV, (JANX/16)*14, JANY-40, JANX-5, JANY-5 );

    g2_flush( D );
}

/**************************************************************************/

void imprime_referencial ( DADOS *dados, STATE *state )
{
  char str[256];

    g2_pen( DEV, 0 );
    g2_set_font_size( DEV, 12 );
  
    g2_line( DEV, 9, CENTRO_Y, JANX-9, CENTRO_Y );

    sprintf( str, " %0.0f", LIMITE_MENOR_X - (LIMITE_MENOR_X/10)*(ZOOM) );
     g2_string( DEV, 6, CENTRO_Y-13, str );
    sprintf( str, "%0.0f", LIMITE_MAIOR_X - (LIMITE_MAIOR_X/10)*(ZOOM) );
     g2_string( DEV, JANX-30, CENTRO_Y-13, str );

    g2_line( DEV, CENTRO_X, 8, CENTRO_X, JANY-47 );

    sprintf( str, "  %0.0f", LIMITE_MENOR_Y - (LIMITE_MENOR_Y/10)*(ZOOM) );
     g2_string( DEV, CENTRO_X+2, 7, str );
    sprintf( str, "  %0.0f", LIMITE_MAIOR_Y - (LIMITE_MAIOR_Y/10)*(ZOOM) );
     g2_string( DEV, CENTRO_X+2, JANY-57, str );
    g2_flush( D );
}

/**************************************************************************/

void captura_rato ( STATE *state, DADOS *dados )
{
  double x_mouse , y_mouse;
  unsigned int button_mouse, botao_drt, botao_esq;
  char str[256];

    g2_query_pointer ( DEV, &x_mouse, &y_mouse, &button_mouse );
      XM= (int) x_mouse;
      YM= (int) y_mouse;
   
    g2_pen( DEV, 0 );
    g2_set_font_size( DEV, 15 );

    sprintf( str, " x=%d y= %d Speed = %0.1f ", XM, YM, state->speed[state->indice_speed] );
     g2_string( DEV, 20, 23, str );  

    g2_flush( D );

    botao_drt = button_mouse & MASK_DRT;
    botao_esq = button_mouse & MASK_ESQ;
  
    if( botao_drt == MASK_DRT ) {
      BOT_RATO = 1;
      return ;
    } 
    if( botao_esq == MASK_ESQ ) { 
      BOT_RATO = 2;
      return ;
    } 
    else {
      CONTROLO = 0;  
      BOT_RATO = 0;
    }                               
}

/**************************************************************************/

int avalia_so_1_clique ( STATE *state, DADOS *dados, VECTOR_BASES bases[] )
{
  
  if( CONTROLO == 0 ) {
    if( BOT_RATO == 1 ) {
      CONTROLO = 1;
      if( avalia_posicao_rato ( state, dados, bases ) == 1 )
        return 1;
    }
    if( BOT_RATO == 2 ) {
      avalia_zoom ( state, dados );
      CONTROLO = 1;
    }
  }
  return 0;
}

/**************************************************************************/

int avalia_posicao_rato ( STATE *state, DADOS *dados, VECTOR_BASES bases[] )
{
  char str[256];
  g2_pen( DEV, 0 );
  g2_set_font_size( DEV, 15 );

    if( ZONA_Y_BARRA ) {
      if( 5 <= XM && XM <= (JANX/16)*2 ) {            /*RESET */
        liberta_lista ( bases );
        ZOOM= 0;
        SPEED= 2;
      }
      if( 2*(JANX/16) <= XM && XM <= (JANX/16)*4 )    /*ADD*/
        add ( bases, dados );     
      if( 4*(JANX/16) <= XM && XM <= (JANX/16)*6 )    /*REMOVE*/
        remove_ ( state, bases, dados );
      if( 6*(JANX/16) <= XM && XM <= (JANX/16)*8 )    /*SAVE*/
        save ( bases, state, dados );
      if( 8*(JANX/16) <= XM && XM <= (JANX/16)*10 ) { /*END*/
        end ( dados );
        return 1; 
      }
      if( 10*(JANX/16) <= XM && XM <= (JANX/16)*12 )  /*SPEED*/
        if( SPEED >= 0  && SPEED < 5 )
          SPEED= SPEED+1;
      if( 12*(JANX/16) <= XM && XM <= (JANX/16)*14 )  /*ZOOM*/
        avalia_zoom ( state, dados );   
      if( 14*(JANX/16) <= XM && XM <= JANX-5 ) {      /*TRAIL*/
        sprintf( str, "TRIAL" );
         g2_string( DEV, JANX/2, JANY/2, str ); 
      }   
    }
    g2_flush( D );
    return 0;
}

/**************************************************************************/

void avalia_zoom ( STATE *state, DADOS *dados )
{

  if( BOT_RATO == 1 && ZOOM < 8 )
    ZOOM= ZOOM + 1;
  if( BOT_RATO == 2 && ZOOM > 0 )
    ZOOM= ZOOM - 1;
}

/**************************************************************************/

void end ( DADOS *dados )
{
  
  g2_close( D );
  printf ( "\n\n\t\t*** Programa terminado com sucesso! ***\n\n" );
}

/**************************************************************************/

void save ( VECTOR_BASES bases[], STATE *state, DADOS *dados )
{
  FILE * fp;
  ESTRUTURA * ap;
  char v[MAX], nome[MAX];
  int i, n;

    for( i= 0; FICH_LIDO[i] != '.'; i++ )
     v[i]= FICH_LIDO[i];
    v[i]= '\0';
    sprintf( nome, "%s_%d.txt", v, NUM_SAVE );
    fp= fopen( nome, "w" );
    if( fp == NULL ) { 
      printf( "\n !!! ERRO: a abrir o ficheiro %s !!!\n\n", FICH_LIDO );
      return ; 
    }
    NUM_SAVE= NUM_SAVE + 1;
    fprintf( fp, "// Dimensao da janela em pixeis. Largura e altura\n" );
    fprintf( fp, "JANELA %d %d\n\n", JANX, JANY );
    fprintf( fp, "// Dimensoes do referencial fisico em unidades adequadas [UA]\n" );
    fprintf( fp, "// dimensão e valor minimo e maximo\n" );
    fprintf( fp, "// Sera necessario transformar X e Y nas coordenadas da janela gráfica\n" );
    fprintf( fp, "X  %0.0f %0.0f\n", LIMITE_MENOR_X, LIMITE_MAIOR_X );
    fprintf( fp, "Y  %0.0f %0.0f\n\n", LIMITE_MENOR_Y, LIMITE_MAIOR_Y );
    fprintf( fp, "// Centro do referencial fisico (0,0) na janela grafica (pixeis)\n" );
    fprintf( fp, "C %d %d\n\n", CENTRO_X, CENTRO_Y+21 );
    fprintf( fp, "// Tamanhos dos corpos celestes em pixeis para a representacao gradfica\n" );
    fprintf( fp, "ESTRELAS    %d\n", RAIO_ESTRELA );
    fprintf( fp, "PLANETAS    %d\n", RAIO_PLANETA );
    fprintf( fp, "ASTEROIDES   %d\n", RAIO_ASTEROIDE );
    fprintf( fp, "FRAGMENTOS   %d\n\n", RAIO_FRAGMENTO );
    fprintf( fp, "// Corpos celestes a serem especificados pelo utilizador\n" );
    fprintf( fp, "// Nota: x,y - Posicao em relacao ao centro de coordenadas fisico\n" );
    fprintf( fp, "// ESTRELA    identificacao cor massa x y\n" );
    fprintf( fp, "// PLANETA    identificacao cor massa x, y, vx, vy\n" );
    fprintf( fp, "// ASTEROIDE  identificacao cor massa x, y, vx, vy\n\n" );
    fprintf( fp, "\n// Elementos existentes no Universo:\n\n" );
    for ( n= 0; n != 4; n++ ) {
      ap= bases[n].corpos; 
      if ( ap == NULL )
        fprintf( fp, "\n// Não existem %ss no universo!\n", bases[n].nome_corpo );
      else
        fprintf( fp, "\n// %ss no universo:\n\n", bases[n].nome_corpo );
        for ( ; ap != NULL; ap= ap->prox ) {
          fprintf( fp, " %s %s", bases[n].nome_corpo, IDENTIFICACAO );
          fprintf( fp, " %s %d", COR, MASSA );
          fprintf( fp, " %d %d", COORDENADAS_X, COORDENADAS_Y );
          if( n == ESTRELA )
            fprintf( fp, "\n\n" );
          else
            fprintf( fp, " %d %d\n\n", VEL_X, VEL_Y );
        }
    }
    fclose( fp );
}

/**************************************************************************/

void imprime_corpos( VECTOR_BASES bases[], STATE *state, DADOS *dados )
{
  int i;
  char str[256];
  ESTRUTURA * ap;
  
    g2_set_font_size( DEV, 11 );    
    for( i=0; i < 4; i++ )
      for( ap= bases[i].corpos; ap != NULL; ap= ap->prox ) {
        g2_pen( D, ap->dado_util.cor_int );
         g2_filled_circle( D, POS_X, POS_Y, RAIO + 5 * ZOOM );
        g2_pen( D, 0 );
         sprintf( str, "%s", IDENTIFICACAO );
          g2_string( DEV, POS_X, POS_Y - RAIO - 5 * ZOOM - 13, str );  
        g2_flush( D );
      }
}
 
/**************************************************************************/
/* x_pixel / x_referencial = relação entre os dois */ 
void pixel_ref ( DADOS *dados, STATE *state )
{

  state->convert[0]= -1 * CENTRO_X / ( ( LIMITE_MENOR_X ) - ( LIMITE_MENOR_X / 10 ) * ZOOM );
  state->convert[1]= ( JANX - CENTRO_X ) / (  LIMITE_MAIOR_X  - ( LIMITE_MAIOR_X / 10 ) * ZOOM );
  state->convert[2]= -1 * CENTRO_Y / ( ( LIMITE_MENOR_Y ) - ( LIMITE_MENOR_Y / 10 ) * ZOOM );
  state->convert[3]= ( (JANY - 42 ) - CENTRO_Y ) / ( ( LIMITE_MAIOR_Y ) - ( LIMITE_MAIOR_Y / 10 ) * ZOOM );

  /*for(i=0; i<=3;i++)
   printf("\n %d -  %f \n", i, state->convert[i] );*/
}

/*

DADOS
  printf( "\nJanela %d %d\n", JANX, JANY );
  printf( "X %0.0f %0.0f\n", LIMITE_MENOR_X, LIMITE_MAIOR_X);
  printf( "Y %0.0f %0.0f\n", LIMITE_MENOR_Y, LIMITE_MAIOR_Y);
  printf( "C %d %d\n", CENTRO_X, CENTRO_Y );
  printf( "ESTRELAS %d\n", dados->raio_estrela);
  printf( "PLANETAS %d\n", dados->raio_planeta);
  printf( "ASTEROIDES %d\n", dados->raio_asteroide);
  printf( "FRAGMENTOS %d\n", dados->raio_fragmento);

STATE
  printf( "\nFicheiro = %s", FICH_LIDO );
  printf( "\nZoom = %d", state->zoom );
  printf( "\nSpeed = %f", state->speed );
  printf( "\nXM = %d YM = %d", state->pos_rato.x, state->pos_rato.y );
  printf( "\nFicheiro save = %d", NUM_SAVE );
  printf( "\nCtrl = %d", CONTROLO );
  printf( "\nClique = %d", state->clique );
  fflush(stdout);

  */