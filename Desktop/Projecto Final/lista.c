#include "lista.h"

/**************************************************************************/

void inicia_vector_bases ( VECTOR_BASES bases[], DADOS dados )
{
  RAIO_ESTRELA= 0;
    strcpy( bases[ESTRELA].nome_corpo, "Estrela\0" );
      bases[ESTRELA].corpos= ( ESTRUTURA * ) NULL;

  RAIO_PLANETA= 0;
    strcpy( bases[PLANETA].nome_corpo, "Planeta\0" );
      bases[PLANETA].corpos= ( ESTRUTURA * ) NULL;

  RAIO_ASTEROIDE= 0;
    strcpy( bases[ASTEROIDE].nome_corpo, "Asteroide\0" );
      bases[ASTEROIDE].corpos= ( ESTRUTURA * ) NULL;

  RAIO_FRAGMENTO= 0;
    strcpy( bases[3].nome_corpo, "Fragmento\0" );
      bases[3].corpos= ( ESTRUTURA * ) NULL;
}

/**************************************************************************/

void liberta_lista ( VECTOR_BASES bases[] )
{
  ESTRUTURA * ap, * ap_aux;
  int i;

    for( i=0; i != 4; i++ ) {
      ap= bases[i].corpos;
      bases[i].corpos= NULL;

      while( ap != NULL ) {
        ap_aux= ap->prox;
        free( ap );
        ap= ap_aux;
      }
    }
}

/**************************************************************************/

void add ( VECTOR_BASES bases[], DADOS *dados )
{
  char v[100];
  int tipo;

    printf( "\n Que tipo de elemento quer inserir?\n" );
    printf( "\n 0- Estrelas\n 1- Planetas\n 2- Asteroides\n" );

    if( scanf( "%d", &tipo ) == 1) {
      if( tipo >= 0 && tipo <= 3 ) {
        if( pede_dados_utilizador ( v, tipo ) == 1 ) {
          fgets( v, sizeof v, stdin );
          printf( "\n Dados incorrectos! Elemento ignorado!\n\n" );
          return ;
        }
        if( avalia_input ( v, bases, dados, tipo ) == 1) {
          fgets( v, sizeof v, stdin );
          printf( "\n Dados incorrectos! Elemento ignorado!\n\n" );
          return ;
        }
        printf( "\n Voltar à janela do programa!\n" ); 
        if( iserir_elemento ( bases, tipo, v ) == 1 )
          return ; 
      }
      else {
        fgets( v, sizeof v, stdin );
        printf( "\n Caracter inválido! \n" );
        return ;
      }
    }
    else {
      fgets( v, sizeof v, stdin );
      printf( "\n Caracter inválido! \n" );
      return ;
    }
}

/**************************************************************************/

int pede_dados_utilizador ( char v[], int tipo )
{
  int a=0, b=0, c=0, x[5];
  char ident[5], cor[MAX];

    imprime_instrucoes ( );
  
    printf( "\n Inserir a identificação:\n" );
    fscanf( stdin, "%s", ident );

    printf( " Inserir a cor:\n" );
    abre_janela_apoio ( cor );
    x[0]= define_cor ( cor );

    printf( " Inserir a massa do corpo:\n" );
    a= fscanf( stdin, "%d", &x[1] );  

    printf( " Inserir as coordenadas X e Y:\n" );
    b= fscanf( stdin, "%d %d", &x[2], &x[3] );

    if( tipo != ESTRELA ) {
      printf( " Inserir as velocidades vx e vy:\n" );
      c= fscanf( stdin, "%d %d", &x[4], &x[5] );
    }
    if( tipo == ESTRELA )
      if( a+b+c != 3 )
        return 1;
    if( tipo != ESTRELA )
      if( a+b+c != 5 )
        return 1; 

    sprintf( v, "%s %s %d %d %d %d %d %d", ident, cor, x[0], x[1], x[2], x[3], x[4], x[5] );
    return 0;

}

/**************************************************************************/

void imprime_instrucoes ( void )
{
  
  printf( "\n\n\t\tInserir elemento de acordo com as seguintes regras!\n" );
  printf( "\n   1º- Selecionar que elemento deseja inserir.\n" );
  printf( "\n   2º- A identificação não deve ter mais de 8 caracteres.\n" );
  printf( "\n   3º- A identificação deve ser unica!\n" );
  printf( "\n   4º- Os parametros devem estar entre os valores estabelecidos!\n\n" );
}

/**************************************************************************/

int define_cor ( char cor[] )
{
  if ( strcmp( cor, "BRANCO" ) == 0 )
    return 0;
  if ( strcmp( cor, "PRETO" ) == 0 )
    return 1;
  if ( strcmp( cor, "AZUL" ) == 0 )
    return 3;
  if ( strcmp( cor, "VERDE" ) == 0 )
    return 7;
  if ( strcmp( cor, "CASTANHO" ) == 0 )
    return 9;
  if ( strcmp( cor, "ROXO" ) == 0 )
    return 12;
  if ( strcmp( cor, "CYAN" ) == 0 )
    return 18;
  if ( strcmp( cor, "VERMELHO" ) == 0 )
    return 19;
  if ( strcmp( cor, "LARANJA" ) == 0 )
    return 22;
  if ( strcmp( cor, "AMARELO" ) == 0 )
    return 25;    
  else
    return -1;
}

/**************************************************************************/    

int avalia_input ( char v[], VECTOR_BASES bases[], DADOS *dados, int tipo )
{  
  int x[5];
  char ident[5], cor[MAX];
    
    sscanf( v, "%s %s %d %d %d %d %d %d", ident, cor, &x[0], &x[1], &x[2], &x[3], &x[4], &x[5] );
    
    if( avalia_identificacao ( ident, bases, tipo ) == 1 )
      return 1;
    if( x[0] == -1 ) {
      printf( "\n ERRO cor incorrecta!\n" );
      return 1;
    }
    if( x[2] < LIMITE_MENOR_X || x[2] > LIMITE_MAIOR_X ) {
      printf( "\n ERRO coordenadas fora dos limites!\n" );
      return 1; 
    }
    if( x[3] < LIMITE_MENOR_Y || x[3] > LIMITE_MAIOR_Y ) {
      printf( "\n ERRO coordenadas fora dos limites!\n" );
      return 1; 
    }
    printf( "\n Corpo inserido com sucesso!\n" );
    return 0;
}

/**************************************************************************/

int iserir_elemento ( VECTOR_BASES bases[], int tipo, char v[] )
{
  ESTRUTURA * ap, * ap_aux;
  char nome[5], cor[MAX];
  int x[5];

    sscanf( v, "%s %s %d %d %d %d %d %d", nome, cor, &x[0], &x[1], &x[2], &x[3], &x[4], &x[5] );

    ap= ( ESTRUTURA * ) calloc ( 1, sizeof ( ESTRUTURA ) );
    if ( ap == ( ESTRUTURA * ) NULL ) {
      printf( " Erro ao alocar a memória!\n" );
      return 1;
    }
    strcpy( IDENTIFICACAO, nome );
    strcpy( COR, cor );
    ap->dado_util.cor_int= x[0];
    MASSA= x[1];
    COORDENADAS_X= x[2];
    COORDENADAS_Y= x[3];
    VEL_X= x[4];
    VEL_Y= x[5];
  
    ap_aux= ap;
    ap->prox= bases[tipo].corpos;
    ap->ant= NULL;
    bases[tipo].corpos= ap;
    if( ap->prox != NULL ) {
      ap= ap->prox;
      ap->ant= ap_aux;
    }  
    return 0;
}

/**************************************************************************/

void abre_janela_apoio ( char cor[] )
{
  int i, d=0, dev=0;
  char str[256];
  int cores[10]= { 0, 1, 3, 7, 9, 12, 18, 19, 22, 25 };

    dev= g2_open_X11( 200, 300 );
    d= g2_open_vd( );
    g2_attach( d, dev );
    g2_clear( d );
    g2_set_background ( dev, 1 );

    for( i=0; i<10; i++) {
      g2_pen( dev, cores[i] );
       g2_filled_rectangle( dev, 100, 30*i, 295, 30 + 30*i );
    }
    g2_pen( dev, 0 );
      g2_set_font_size( dev, 12 );
        sprintf( str, "  BRANCO " );
          g2_string( dev, 10, 7.5, str );
        sprintf( str, "  PRETO " );
          g2_string( dev, 10, 37.5, str );
        sprintf( str, "  AZUL " );
          g2_string( dev, 10, 67.5, str );
        sprintf( str, "  VERDE " );
          g2_string( dev, 10, 97.5, str );
        sprintf( str, "  CASTANHO " );
          g2_string( dev, 10, 127.5, str );
        sprintf( str, "  ROXO " );
          g2_string( dev, 10, 157.5, str );
        sprintf( str, "  CYAN " );
          g2_string( dev, 10, 187.5, str );
        sprintf( str, "  VERMELHO " );
          g2_string( dev, 10, 217.5, str );
        sprintf( str, "  LARANJA " );
          g2_string( dev, 10, 247.5, str );
        sprintf( str, "  AMARELO " );
          g2_string( dev, 10, 277.5, str );

    g2_flush( d );
    fscanf( stdin, "%s", cor );
    g2_close( d );
}

/**************************************************************************/

int avalia_identificacao ( char ident[], VECTOR_BASES bases[], int tipo )
{
  ESTRUTURA * ap;
  int i;

    for( i=0; ident[i] != '\0'; i++ );
    if( i > 8 ) {
      printf( "\n ERRO inserir identificação até 8 caracteres!\n" );
      return 1;
    } 
    for ( ap= bases[tipo].corpos; ap != NULL ; ap = ap->prox ) {
      if( strcmp( ident, IDENTIFICACAO ) == 0 ) {
        printf( "\n ERRO já existe um elemento com essa identificação!\n" );
        return 1;
      }
    }
    return 0;
}

/**************************************************************************/

void remove_ ( STATE *state, VECTOR_BASES bases[], DADOS *dados )
{
  char remov[MAX];
  int i=0;
  float zona[4];
  ESTRUTURA * ap= NULL;

    printf( "\n Em que zona deseja eleminar?\n" );
    printf( "\n Seleccione a zona com o rato:\n" );
    select_zona ( state, dados, zona );
    if( mostra_elementos ( bases, zona ) == 1 )
      return ;
    printf( "\n Que tipo de elemento quer eleminar?\n" );
    printf( "\n 0- Estrelas\n 1- Planetas\n 2- Asteroides\n 3- Fragmentos\n" );
    if( scanf( "%d", &i ) == 1 && i >= 0 && i <= 3 ) {
      if ( bases[i].corpos == NULL ) {
        fgets( remov, sizeof remov, stdin );
        printf("\n Não há %ss a eleminar! \n", bases[i].nome_corpo );
        return ;
      }
      printf( "\n Inserir identificação de %s a eleminar:\n", bases[i].nome_corpo );
      fscanf( stdin, "%s", remov );
      if( procura_corpo_celeste ( remov, bases[i].corpos, &ap ) == 1 ) {
        if( POS_PRINT_X >= zona[0] && POS_PRINT_X <= zona[1] ) {
          if( POS_PRINT_Y >= zona[3] && POS_PRINT_Y <= zona[2] ) 
            remove_corpo_celeste ( ap, &bases[i].corpos );
          return ;
        }
        else {
          printf( "\n Nenhum elemento com esta identificação nesta zona!\n" );
          return ;
        }
      } 
    }
    else {
      fgets( remov, sizeof remov, stdin );
      printf( "\n Caracter inválido! \n" );
      return ;
    }
}

/**************************************************************************/

int select_zona ( STATE *state, DADOS *dados, float zona[] )
{
  int sucesso= 0;
      
    do {
      captura_rato ( state, dados );
      if( BOT_RATO == 1 )
        if( XM > 0 && XM < JANX )
          if( YM > 0 && YM < JANY - 42 ) {
            zona[0]= XM;
            zona[2]= YM;
            sucesso= 1;
          }
    } while ( sucesso != 1 );
    while ( BOT_RATO == 1 ) {
      captura_rato ( state, dados );
      g2_filled_rectangle( DEV, zona[0], zona[2], XM, YM );
    }
      if( XM > 0 && XM < JANX )
        if( YM > 0 && YM < JANY - 42 ) {
          zona[1]= XM;
          zona[3]= YM;
        }
    XM=-1;
    return 0;
}

/**************************************************************************/

int mostra_elementos ( VECTOR_BASES bases[], float zona[] )
{
  ESTRUTURA * ap;
  int i, existe_elementos= 0;
  
  printf( "\n\n\t-Corpos celestes presentes no universo:\n" );
  for( i=0; i <= 3; i++)
   {
    printf( "\n %s\n", bases[i].nome_corpo ); 
    if ( bases[i].corpos == NULL )
      printf( "\n   Não há %s neste universo!\n", bases[i].nome_corpo );
    else
      for ( ap= bases[i].corpos; ap != NULL ; ap = ap->prox ) {
        if( POS_PRINT_X >= zona[0] && POS_PRINT_X <= zona[1] ) {
          if( POS_PRINT_Y >= zona[3] && POS_PRINT_Y <= zona[2] ) {
            mostra_corpo_celeste ( ap, i );
            existe_elementos++;
          }
        }
      }
    }   
  if( existe_elementos == 0 )
   return 1;

  return 0;
}

/**************************************************************************/

void mostra_corpo_celeste ( ESTRUTURA *ap, int i )
{

  printf( "\n    -Identificação: %s", IDENTIFICACAO );
  printf( " Cor: %s Massa: %d", COR, MASSA );
  printf( " Pos x: %d  Pos y: %d", COORDENADAS_X, COORDENADAS_Y );
  if( i == ESTRELA )
    printf( "\n" );
  else
    printf( " Vel vx: %d  Vel vy: %d\n", VEL_X, VEL_Y );
}

/**************************************************************************/

int procura_corpo_celeste ( char remov[], ESTRUTURA *base_do_tipo, ESTRUTURA **ap )
{
  for( *ap= base_do_tipo; *ap != NULL; *ap= (*ap)->prox )
     if( strcmp( remov, (*ap)->dado_util.ident ) == 0 )
       /*if( x_menos )*/
      return 1;
  printf( "\n Nenhum elemento com esta identificação!\n" );
  return 0;
}

/**************************************************************************/

void remove_corpo_celeste ( ESTRUTURA *ap_actual, ESTRUTURA **base_do_tipo )
{
  ESTRUTURA * ap_aux;

    if( ap_actual->ant == NULL )
      *base_do_tipo= ap_actual->prox;
    else {
      ap_aux= ap_actual->ant;
      ap_aux->prox= ap_actual->prox;
      }
      if( ap_actual->prox != NULL ) {
        ap_aux= ap_actual->prox;
        ap_aux->ant= ap_actual->ant;
      } 
    free( ap_actual ); 
    printf( "\n Corpo eleminado com sucesso!\n\n" );     
}

/**************************************************************************/

void actualiza_posicao ( VECTOR_BASES bases[] )
{
  int i;
  ESTRUTURA * ap;

    for( i=1; i < 4; i++) { 
      if ( bases[i].corpos != NULL ) {
        for ( ap= bases[i].corpos; ap != NULL ; ap = ap->prox ) {
          COORDENADAS_X= COORDENADAS_X + ap->dado_util.velocidade.vx;
          COORDENADAS_Y= COORDENADAS_Y + ap->dado_util.velocidade.vy;
        }
      }
    }  
}

/**************************************************************************/

void actualiza_pos_print ( VECTOR_BASES bases[], STATE state, DADOS *dados )
{
  int i;
  ESTRUTURA * ap;

    for( i=0; i < 4; i++) { 
      if ( bases[i].corpos != NULL ) {
        for ( ap= bases[i].corpos; ap != NULL ; ap = ap->prox ) {
          if( COORDENADAS_X < 0 )
            POS_PRINT_X= COORDENADAS_X * state.convert[0] + CENTRO_X;
          if( COORDENADAS_X >= 0 )
            POS_PRINT_X= COORDENADAS_X * state.convert[1] + CENTRO_X;
          if( COORDENADAS_Y < 0 )
            POS_PRINT_Y= COORDENADAS_Y * state.convert[2] + CENTRO_Y;
          if( COORDENADAS_Y >= 0 )
            POS_PRINT_Y= COORDENADAS_Y * state.convert[3] + CENTRO_Y;
        }
      }   
    }
}