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

void escribirArchivo(char* archivo,vector<long double> vectorX, vector<long double> vectorY)
{
  ofstream archivoSalida;
  archivoSalida.open(archivo,ios::out);
  int i,tamano = vectorY.size();

  int tamano1 = vectorX.size();

  //cout<<"1:"<<tamano<<"- 2:"<< tamano1<<endl; 

  for(i = 0; i < tamano; i++)
  {
    archivoSalida<<vectorX[i]<<" "<<vectorY[i]<<endl;
  }
  
  archivoSalida.close();
}


int menu (int intervaloMenor, int intervaloMayor, int tolerancia)
{
	int bandera = 0, bandera1 = 0;
  	int opcion , opcion1;

  	//Vector x interpolado en 0.5, 1, 5, 10
	vector<long double> vectorX_0_5, vectorX_1, vectorX_5, vectorX_10; 

  	//Vector f(x) donde x son los x interpolados antes. (Función 1)
  	vector<long double> vector1_Y_0_5, vector1_Y_1, vector1_Y_5, vector1_Y_10;

  	  //Vector para graficar escala logaritmica 
  	vector<long double> vectorXInterpolado_0_05;

  	 	// Metodo minimos cuadrados:
    //Variables a utilizar Funcion 1:
    vector<long double> difMinimosCuadrado1_0_5,difMinimosCuadrado1_1,difMinimosCuadrado1_5,difMinimosCuadrado1_10;
      long double errorMinimosCuadrado1_0_5,errorMinimosCuadrado1_1,errorMinimosCuadrado1_5,errorMinimosCuadrado1_10;
  	
  	// Valores reales de la integral
      long double integral_F1;


    // Funcion 1 :
    long double trapecio_F1_0_05,trapecio_F1_0_1,trapecio_F1_5,trapecio_F1_10;
    long double simpson13_F1_0_05,simpson13_F1_0_1,simpson13_F1_5,simpson13_F1_10;
    long double simpson38_F1_0_05,simpson38_F1_1,simpson38_F1_5,simpson38_F1_10;

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

              //Vector x interpolado en 0.5, 1, 5, 10 (Asignando valores)
              vectorX_0_5 = inter.vectorX(0.5,intervaloMenor,intervaloMayor);
              vectorX_1 = inter.vectorX(1,intervaloMenor,intervaloMayor);
              vectorX_5 = inter.vectorX(5,intervaloMenor,intervaloMayor);
              vectorX_10 = inter.vectorX(10,intervaloMenor,intervaloMayor);
              //Vector f(x) donde x son los x interpolados antes. (Función 1) (Asignando valores)
              vector1_Y_0_5 = inter.vectorY(vectorX_0_5);
              vector1_Y_1 = inter.vectorY(vectorX_1);
              vector1_Y_5 = inter.vectorY(vectorX_5);
              vector1_Y_10 = inter.vectorY(vectorX_10);

              //Vector para graficar escala logaritmica (Asignando valores)
              vectorXInterpolado_0_05 = inter.vectorX(0.05,intervaloMenor,intervaloMayor);

              // Valores reales de las funciones 1 
              integral_F1 = 2.3183*pow(10,60);

              // Interpolamos
              difMinimosCuadrado1_0_5 = inter.minimosCuadrados(vectorX_0_5,vector1_Y_0_5,vectorXInterpolado_0_05,24);
              escribirArchivo((char*)"Func1_0_5.txt",vectorXInterpolado_0_05,difMinimosCuadrado1_0_5);
             
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
                          trapecio_F1_0_05 = inter.formTrapecio(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          //trapecio_F1_0_1 = inter.formTrapecio(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          //trapecio_F1_5 = inter.formTrapecio(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          //trapecio_F1_10 = inter.formTrapecio(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          // Realizar el calculo ...
                          cout << "El resultado obtenido de 0.05 es: " << trapecio_F1_0_05 << endl;
                          //cout << "El resultado obtenido de 1 es: \n" << trapecio_F1_0_1 << endl;
                          //cout << "El resultado obtenido de 5 es: \n" << trapecio_F1_5 << endl;
                          //cout << "El resultado obtenido de 10 es: \n" << trapecio_F1_10 << endl;
                          errorMinimosCuadrado1_0_5 = inter.Tolerancia(intervaloMenor,intervaloMayor,0.8,difMinimosCuadrado1_0_5,0.05);
                          cout << "El error es : " << errorMinimosCuadrado1_0_5 << endl;
                          cout << "El resultado real es: " << integral_F1 << endl;
                          break;
                    
                    case 2 :
                    	  system("clear");
                          cout << "Esta utilizando la solucion por simpson 1/3 \n"<< endl;
                          simpson13_F1_0_05 = inter.formSimpson13(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          //simpson13_F1_0_1 = inter.formSimpson13(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          //simpson13_F1_5 = inter.formSimpson13(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          //simpson13_F1_10 = inter.formSimpson13(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          // Realizar el calculo ...
                          cout << "El resultado obtenido de 0-05 es: \n" << simpson13_F1_0_05 << endl;
                          //cout << "El resultado obtenido de 1 es: \n" << simpson13_F1_0_1 << endl;
                          //cout << "El resultado obtenido de 5 es: \n" << simpson13_F1_5 << endl;
                          //cout << "El resultado obtenido de 10 es: \n" << simpson13_F1_10 << endl;
                          cout << "El resultado real es: \n" << integral_F1 << endl;
                          break;
                    
                    case 3 :
                    	  system("clear");
                          cout << "Esta utilizando la solucion por simpson 3/8 \n"<< endl;                          
                          simpson38_F1_0_05 = inter.formSimpson38(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          //simpson38_F1_1 = inter.formSimpson38(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          //simpson38_F1_5 = inter.formSimpson38(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          //simpson38_F1_10 = inter.formSimpson38(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor,0.05);
                          // Realizar el calculo ...
                          cout << "El resultado obtenido de 0.05 es: \n" << simpson38_F1_0_05 << endl;
                          //cout << "El resultado obtenido de 1 es: \n" << simpson38_F1_1 << endl;
                          //cout << "El resultado obtenido de 5 es: \n" << simpson38_F1_5 << endl;
                          //cout << "El resultado obtenido de 10 es: \n" << simpson38_F1_10 << endl;
                          cout << "El resultado real es: \n" << integral_F1 << endl;
                          break;
                    
                    default : 
                    	  system("clear");
                          if (opcion1 != 4){
                            cout << "Esta opcion no esta permitida \n"<< endl;
                            //system("clear");
                          }
                          system("clear");
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