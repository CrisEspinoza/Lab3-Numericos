#include <iostream>
#include <cstdlib>

#define  ARMA_DONT_USE_WRAPPER
#define  ARMA_USE_LAPACK
#include <armadillo>

using namespace std;
using namespace arma; 


int main()
{

  int bandera = 0;
  int opcion;

   // Menu (UX)
   do
   {
    cout <<"\n   1. Comenzar parte 1 del laboratorio" << endl;
    cout <<"\n   2. Reiniciar programa" << endl;
    cout <<"\n   3. Creditos" << endl;
    cout <<"\n   4. Salir" << endl;
    cout <<"\n   Introduzca opcion (1-4): "; 

    scanf( "%d", &opcion );

    /* Inicio del anidamiento */

    switch ( opcion )
       {
       case 1:
              if(bandera == 1 )
              {
                cout<<"Ya realiza la parte 1 del laboratorio prosiva con la parte numero dos "<<endl;
                break;
              }
              
              // Liberando opcion 2
              bandera = 1;

              break;

       case 2: 
               if(bandera == 0 )
               {
                  cout<<"Debe ocupar al menos en una oportunidad el programa para poder reiniciarlo"<<endl;
                  break;
               }
               
               cout<< " * Programa Reinciado * \n ";
               bandera = 0;
               break;

       case 3: cout <<" * Autor: Cristian Espinoza \n "<< endl;
               cout <<" * Universidad santiago de chile \n"<< endl;
               break;
       default:
               if(opcion != 4)
               cout <<"Esta opcion no esta permitida.\n"<< endl;
               break;
      }

    }while(opcion!=4);


  return 0;
}