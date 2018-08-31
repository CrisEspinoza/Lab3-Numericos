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

// Variable global

int contadorIteraciones = 0;

MetodosDeIntegracion::MetodosDeIntegracion(){	
}

long double MetodosDeIntegracion::formTrapecio(long double intervaloMenor, long double intervaloMayor)
{
	long double valorIntegral = ( (intervaloMayor-intervaloMenor) / 2.0 ) * ( func1(intervaloMenor) + func1(intervaloMayor) ) ;

	return valorIntegral;
}

long double MetodosDeIntegracion::formSimpson13(long double intervaloMenor, long double intervaloMayor)
{

	long double punto1 = (intervaloMayor+intervaloMenor) / 2.0  ;

	long double valorIntegral = ((intervaloMayor-intervaloMenor) / 6.0 ) * ( func1(intervaloMenor) + (4.0 * func1 (punto1) ) + func1(intervaloMayor) );

	return valorIntegral;
}

long double MetodosDeIntegracion::formSimpson38(long double intervaloMenor, long double intervaloMayor)
{
	long double distancia = ( (intervaloMayor-intervaloMenor)/3.0) ;
	long double punto1 = intervaloMenor + distancia;
	long double punto2 = intervaloMenor + ( 2 * distancia );

	long double valorIntegral = ( (intervaloMayor-intervaloMenor) / 8.0 ) * ( func1(intervaloMenor) + (3.0 * ( func1 (punto1)  + func1 (punto2) ) ) + func1(intervaloMayor) ) ;

	return valorIntegral;
}


// Funciones que evalua la funcion 1 con el valor ingresado
long double MetodosDeIntegracion::func1 (long double x)
{
	long double valor = pow(2,x)-2*x;
	return valor;
}

long double MetodosDeIntegracion::ToleranciaTrapecio(long double intervaloMenor, long double intervaloMayor, long double tolerancia)
{
	long double resultado1, resultado2, resultado3, medio;
	contadorIteraciones++;
	medio = ( (intervaloMayor+intervaloMenor) / 2.0 ) ;
	resultado1 = formTrapecio(intervaloMenor,intervaloMayor);
	resultado2 = formTrapecio(intervaloMenor,medio);
	resultado3 = formTrapecio( medio, intervaloMayor);
	
	cout << "El error que llevamos es: " << 10*(resultado1 - resultado2 - resultado3) << endl;

	if ( 10*(resultado1 - resultado2 - resultado3) < tolerancia)
	{
		return resultado1;
	}
	else{
		return ( ToleranciaTrapecio( intervaloMenor ,medio, tolerancia) + ToleranciaTrapecio(medio, intervaloMayor , tolerancia ) ) ;
	}
}

long double MetodosDeIntegracion::ToleranciaSimpson13(long double intervaloMenor, long double intervaloMayor, long double tolerancia)
{

	long double resultado1, resultado2, resultado3, medio ;
	contadorIteraciones++;
	medio = ( (intervaloMayor+intervaloMenor) / 2.0 ) ;
	resultado1 = formSimpson13(intervaloMenor,intervaloMayor);
	resultado2 = formSimpson13(intervaloMenor,medio);
	resultado3 = formSimpson13( medio, intervaloMayor);

	cout << "El error que llevamos es: " << 10*(resultado1 - resultado2 - resultado3) << endl;

	if (10*(resultado1 - resultado2 - resultado3) < tolerancia)
	{
		return resultado1;
	}
	else{
		return ( ToleranciaSimpson13( intervaloMenor ,medio, tolerancia) + ToleranciaSimpson13(medio, intervaloMayor , tolerancia ) ) ;
	}
}

long double MetodosDeIntegracion::ToleranciaSimpson38(long double intervaloMenor, long double intervaloMayor, long double tolerancia)
{

	long double resultado1, resultado2, resultado3, medio; 
	contadorIteraciones++;
	medio = ( (intervaloMayor+intervaloMenor) / 2.0 ) ;
	resultado1 = formSimpson38(intervaloMenor,intervaloMayor);
	resultado2 = formSimpson38(intervaloMenor,medio);
	resultado3 = formSimpson38(medio, intervaloMayor);

	cout << "El error que llevamos es: " << 10*(resultado1 - resultado2 - resultado3) << endl;
	
	if (10*(resultado1 - resultado2 - resultado3) < tolerancia)
	{
		return resultado1;
	}
	else{
		return ( ToleranciaSimpson38( intervaloMenor ,medio, tolerancia) + ToleranciaSimpson38(medio, intervaloMayor , tolerancia ) ) ;
	}
}

mat MetodosDeIntegracion::createMatrizA(double puntos)
{
	double p = puntos; // p-> cantidad de puntos, p=n+1
	double n = p-1; //n -> numero de intervalos, n=p-1
	mat  a = zeros<mat>(p,p);
	a(0,0) = -1;
	a(0,1) = 1;
	a(n,n-1) = n;
	a(n,n) = -((2*(n))+1);

	for(int i = 1; i<n;i++ ){
		a(i,i-1) = i;
		a(i,i) = -((2*i)+1);
		a(i,i+1) = i+1;
	}
	return a;
}

mat MetodosDeIntegracion::createMatrizB(double puntos, double c,double te, double dr)
{
	double p = puntos;
	double n = puntos - 1.0; //n -> numero de intervalos
	mat b = zeros<mat>(p,1);

	double A = c*pow(dr,2);
	b(0,0) = (A/2.0);
	b(n,0) = ((n*A) - ((n+1)*te)); 
	for(int i = 1; i < (n-1) ;i++){
		b(i,0) = i*A;
	}
	return b;
}

void MetodosDeIntegracion::escribirArchivo(char* archivo,mat temperaturas, double te)
{
  ofstream archivoSalida;
  archivoSalida.open(archivo,ios::out);

  int i;

  for(i = 0; i < temperaturas.size(); i++)
  {
    archivoSalida<<temperaturas[i]<<" "<<endl;
  }
  
  //archivoSalida<<te<<" "<<endl;

  archivoSalida.close();
}

int MetodosDeIntegracion::menu (long double intervaloMenor, long double intervaloMayor, long double tolerancia, double pto , double t_inicial, double Radio, double constante)
{
	int bandera = 0, bandera1 = 0;
  	int opcion , opcion1;

  			// Parte 1 :

    long double resultado1,resultado2,resultado3;

    // Funcion 1 :
    long double trapecio_F1,simpson13_F1 ,simpson38_F1;

    MetodosDeIntegracion inter;

    		// Parte 2 :

    int p,i,j;
	double te,puntos,c,intervalos,radio,dr;
	mat a , b , x ;

	ofstream archivoSalidaParte2;
    archivoSalidaParte2.open("Temperaturas.txt");

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
                          resultado1 = ToleranciaTrapecio(intervaloMenor,intervaloMayor,tolerancia);

                          cout << "El resultado con " << contadorIteraciones << " iteraciones es : " << resultado1 << endl;
                          contadorIteraciones = 0;
                          break;
                    
                    case 2 :
                    	  system("clear");
                          cout << "Esta utilizando la solucion por simpson 1/3 \n"<< endl;
                          // Realizar el calculo ...  
                          resultado2 = ToleranciaSimpson13(intervaloMenor,intervaloMayor,tolerancia);

                          cout << "El resultado con " << contadorIteraciones << " iteraciones es : " << resultado1 << endl;
                          contadorIteraciones = 0;
                          break;
                    
                    case 3 :
                    	  system("clear");
                          cout << "Esta utilizando la solucion por simpson 3/8 \n"<< endl;                          
                          // Realizar el calculo ...
                          resultado3 = ToleranciaSimpson38(intervaloMenor,intervaloMayor,tolerancia);

                          cout << "El resultado con " << contadorIteraciones << " iteraciones es : " << resultado1 << endl;
                          contadorIteraciones = 0;
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

              puntos = pto;
			  c = constante;
			  te = t_inicial;
			  intervalos = puntos - 1.0;
			  radio = Radio;
			  dr = radio/intervalos;

			  a = createMatrizA(puntos);
			  b = createMatrizB(puntos,c,te,dr);
			  x = solve(a,b);

			  /*cout << "Mostrando resultados de la matriz" << endl;
			  for (i = 0; i< puntos; i++)
			  {
				cout << x(i,0) << endl;
			  }
			
			  cout << "Mostrando resultado de la matriz B" << endl;

			  for (i = 0; i< puntos; i++)
			  {
				cout << b(i,0) << endl;
			  }
			
			  cout << "Mostrando resultados de la matriz A" << endl;

			  for (i = 0; i< puntos; i++)
			  {
				for (j = 0; j< puntos; j++)
				{
					cout  << a(i,j) << ", ";
				}
				cout << endl;
			  }*/

			  escribirArchivo( (char*)"../GraficarMatlab/temperaturas.txt" , x, t_inicial);

              //cout<< "Entre a la parte 2 del lab " << endl;
              
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