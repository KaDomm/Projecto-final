#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "le_ficheiro.h"
#include "lista.h"

int main( int argc, char *argv[] )
{
  int end= 0;
  VECTOR_BASES bases[4];
  DADOS dados;
  STATE state;
 
    inicia_estrutura_state ( &state, argv );

    inicia_vector_bases ( bases, dados );

    if( avalia_ficheiro ( argv, &dados, &state, bases ) == 1 )
      return 1;
  
    abre_janela ( &dados );

    while ( end != 1 ) {

      actualiza_ecran ( &dados, &state, bases );

      captura_rato ( &state, &dados );

      end= avalia_so_1_clique ( &state, &dados, bases );

      actualiza_posicao ( bases );

      pixel_ref ( &dados, &state );

      actualiza_pos_print ( bases, state, &dados );

      /*verifica_colisões ( bases );*/

      usleep ( 100000 );
    }

    return 0;
}