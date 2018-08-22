#include <iostream>
#include <cstdlib>

#define  ARMA_DONT_USE_WRAPPER
#define  ARMA_USE_LAPACK

#include <armadillo>
#include "menu.cpp"

using namespace std;
using namespace arma; 


int main(int argc, char *argv[])
{
  int intervaloMenor, intervaloMayor, tolerancia, c;

  while ((c = getopt (argc, argv, "t:a:b:")) != -1)
      switch (c)
        {
        case 't':
          sscanf(optarg, "%d", &tolerancia);
          break;
        case 'a':
          sscanf(optarg, "%d", &intervaloMenor);
          break;
        case 'b':
          sscanf(optarg, "%d", &intervaloMayor);
          break;
          break;
        case '?':
          if (optopt == 't' || optopt == 'a' || optopt == 'b')
              fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
          else if (isprint (optopt))
              fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
          else
              fprintf (stderr,
                   "Opcion con caracter desconocido `\\x%x'.\n",
                   optopt);
          return 1;
        default:
          abort ();
        }

  printf("intervaloMenor : %d \n", intervaloMenor);
  printf("intervaloMayor : %d \n", intervaloMayor);
  printf("tolerancia : %d \n", tolerancia);

  menu (intervaloMenor,intervaloMayor,tolerancia);

  return 0;
}