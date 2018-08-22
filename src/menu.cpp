#include "MetodosDeIntegracion.h"

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#define  ARMA_DONT_USE_WRAPPER
#define  ARMA_USE_LAPACK

#define  ARMA_DONT_USE_WRAPPER
#define  ARMA_USE_LAPACK

#include <armadillo>

using namespace std;
using namespace arma; 

int menu (long double intervaloMenor, long double intervaloMayor, long double tolerancia)
{
	int bandera = 0, bandera1 = 0;
  	int opcion , opcion1;

    long double resultado1,resultado2,resultado3;

    // Funcion 1 :
    long double trapecio_F1,simpson13_F1 ,simpson38_F1;

    MetodosDeIntegracion inter;

   // Menu (UX)
   do
   {
    cout <<"\n   1. Comenzar parte 1 del laboratorio" << endl;
    cout <<"\n   2. Comenzar parte 2 del laboratorio" << endl;
    cout <<"\n   3. Reiniciar programa" << endl;
    cout <<"\n   4. Creditos" << endl;
    cout <<"\n   5. Salir" << endl;
    cout <<"\n   Introduzca opcion (1-5): "; 

    scanf( "%d", &opcion );

    /* Inicio del anidamiento */

    switch ( opcion )
       {
       case 1:
              if(bandera == 1 )
              {
                cout<<"Ya realiza la parte 1 del laboratorio, debe reiniciar el programa para volver hacerlo "<<endl;
                break;
              }

              bandera = 1; 

              system("clear");
              
              do {
                  cout <<"\n   1. Ocupar Trapecio" << endl;
                  cout <<"\n   2. Ocupar simpson 1/3 " << endl;
                  cout <<"\n   3. Ocupar simpson 3/8 " << endl;
                  cout <<"\n   4. Salir" << endl;
                  cout <<"\n   Introduzca opcion (1-4): "; 

                  scanf( "%d", &opcion1 );
              

                  switch (opcion1) 
                  {
                    case 1 : 
                    	  system("clear");
                          cout << "Esta utilizando la solucion por Trapecio\n"<< endl;
                          // Realizar el calculo ...
                          resultado1 = inter.ToleranciaTrapecio(intervaloMenor,intervaloMayor,tolerancia);

                          cout << "El resultado es : " << resultado1 << endl;
                          break;
                    
                    case 2 :
                    	  system("clear");
                          cout << "Esta utilizando la solucion por simpson 1/3 \n"<< endl;
                          // Realizar el calculo ...  
                          resultado2 = inter.ToleranciaSimpson13(intervaloMenor,intervaloMayor,tolerancia);

                          cout << "El resultado es : " << resultado2 << endl;
                          break;
                    
                    case 3 :
                    	  system("clear");
                          cout << "Esta utilizando la solucion por simpson 3/8 \n"<< endl;                          
                          // Realizar el calculo ...
                          resultado3 = inter.ToleranciaSimpson38(intervaloMenor,intervaloMayor,tolerancia);

                          cout << "El resultado es : " << resultado3 << endl;
                          break;
                    
                    default : 
                    	  system("clear");
                          if (opcion1 != 4){
                            cout << "Esta opcion no esta permitida \n"<< endl;
                          }
                          break;
                  } 

              }while(opcion1!=4);

              break;

       case 2:
              system("clear");
              if(bandera1 == 1 )
              {
                cout<<"Ya realiza la parte 2 del laboratorio, debe reiniciar el programa para volver hacerlo "<<endl;
                break;
              }

              cout<< "Entre a la parte 2 del lab " << endl;
              
              bandera1 = 1;

              break;

       case 3: 
               system("clear");
               if(bandera == 0 && bandera1 == 0)
               {
                  cout<<"Debe ocupar al menos en una oportunidad el programa para poder reiniciarlo"<<endl;
                  break;
               }
               
               cout<< " * Programa Reinciado * \n ";
               bandera = 0;
               bandera1 = 0;
               break;

       case 4: 
               system("clear");
               cout <<" * Autor: Cristian Espinoza \n "<< endl;
               cout <<" * Universidad santiago de chile \n"<< endl;
               break;

       default:
               system("clear");
               if(opcion != 5){
                cout <<"Esta opcion no esta permitida.\n"<< endl;}
               
               break;
      }

    }while(opcion!=5);

    return 0 ;

}