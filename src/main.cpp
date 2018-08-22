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
  int c;
  long double tolerancia, intervaloMenor, intervaloMayor;

  while ((c = getopt (argc, argv, "t:a:b:")) != -1)
      switch (c)
        {
        case 't':
          sscanf(optarg, "%Lf",&tolerancia);
          break;
        case 'a':
          sscanf(optarg, "%Lf", &intervaloMenor);
          break;
        case 'b':
          sscanf(optarg, "%Lf", &intervaloMayor);
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

  cout<< "intervaloMenor: "<< intervaloMenor<<endl;
  cout<< "intervaloMayor: "<< intervaloMayor<<endl;
  cout<< "tolerancia: "<< tolerancia<<endl;

  menu (intervaloMenor,intervaloMayor,tolerancia);

  return 0;
}