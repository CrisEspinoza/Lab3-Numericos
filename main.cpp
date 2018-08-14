#include "../interpolacion/interpolacion.h"
#include "../Integral/calcIntegral.h"

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include <cstdlib>

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

void escribirArchivoDatos(ofstream &archivoDatos,vector<long double> vectorX)
{

  for(int i = 0; i<vectorX.size(); i++)
  {
    archivoDatos<<vectorX[i]<<" "<<endl;
  }
  archivoDatos<< "-------------------------------------- TERMINO ----------------------------------------"<<endl;
}

int main()
{
  int opcion;
  int bandera = 0;
  Interpolacion inter;
  calcIntegral calInte;
  int intervaloMenor = -200 , intervaloMayor = 200;
  //calcIntegral calcIntegral;
  char func1[256] = "e^x+x-2";
  char func2[256] = "x^3+4*x^2-5*x+2";

  // Variables ocupadas para la parte 1 del enunciado;

  // Declaranco variables de archivos de salida.
  ofstream archivoSalidaParte1,archivoSalidaParte2,resultF1_0_05,resultF1_1,resultF1_5,resultF1_10, 
            resultF2_0_05,resultF2_1,resultF2_5,resultF2_10;
  archivoSalidaParte1.open("ErroresRMSEParte1.txt");
  archivoSalidaParte2.open("ErroresRMSEParte2.txt");
  ofstream archivoaux("Datos.ods");
  
  // Resultado de funciones reales
    //Funcion 1
  /*resultF1_0_05.open ("../ResultadosReales/real_0_05_F1.txt");
  resultF1_0_05.open ("../ResultadosReales/real_0_5_F1.txt");
  resultF1_1.open("../ResultadosReales/real_1_F1.txt");
  resultF1_5.open("../ResultadosReales/real_5_F1.txt");
  resultF1_10.open("../ResultadosReales/real_10_F1.txt");
    //Funcion 2
  resultF2_0_05.open("../ResultadosReales/real_0_05_F2.txt");
  resultF2_0_05.open("../ResultadosReales/real_0_5_F2.txt");
  resultF2_1.open("../ResultadosReales/real_1_F2.txt");
  resultF2_5.open("../ResultadosReales/real_5_F2.txt");
  resultF2_10.open("../ResultadosReales/real_10_F2.txt");
*/
  //Vector pruebas
  vector<long double> vectorX_50,vector1_Y_50;

  //Vector x interpolado en 0.5, 1, 5, 10
  vector<long double> vectorX_0_5, vectorX_1, vectorX_5, vectorX_10; 

  //Vector f(x) donde x son los x interpolados antes. (Función 1)
  vector<long double> vector1_Y_0_5, vector1_Y_1, vector1_Y_5, vector1_Y_10;
  
  //Vector f(x) donde x son los x interpolados antes. (Función 2)
  vector<long double> vector2_Y_0_5, vector2_Y_1, vector2_Y_5, vector2_Y_10;

  //Vector para graficar escala logaritmica 
  vector<long double> vectorXInterpolado_0_05, vector1_Y_Interpolado_0_05, vector2_Y_Interpolado_0_05;

  // Metodo 1:
    //Variables a utilizar Funcion 1:
    vector<long double> difDivididas1_0_5,difDivididas1_1,difDivididas1_5,difDivididas1_10;
      long double errorDivididos1_0_5,errorDivididos1_1,errorDivididos1_5,errorDivididos1_10;
    //Variables a utilizar Funcion 2:
    vector<long double> difDivididas2_0_5,difDivididas2_1,difDivididas2_5,difDivididas2_10;
      long double errorDivididos2_0_5,errorDivididos2_1,errorDivididos2_5,errorDivididos2_10;

  // Metodo 2:
    //Variables a utilizar Funcion 1:
    vector<long double> difFinitas1_0_5,difFinitas1_1,difFinitas1_5,difFinitas1_10;
    long double errorFinito1_0_5,errorFinito1_1,errorFinito1_5,errorFinito1_10;
    //Variables a utilizar Funcion 2:
    vector<long double> difFinitas2_0_5,difFinitas2_1,difFinitas2_5,difFinitas2_10;
    long double errorFinito2_0_5,errorFinito2_1,errorFinito2_5,errorFinito2_10;

  // Metodo 3:
    //Variables a utilizar Funcion 1:
    vector<long double> difMinimosCuadrado1_0_5,difMinimosCuadrado1_1,difMinimosCuadrado1_5,difMinimosCuadrado1_10;
      long double errorMinimosCuadrado1_0_5,errorMinimosCuadrado1_1,errorMinimosCuadrado1_5,errorMinimosCuadrado1_10;
  //Variables a utilizar Funcion 2:
    vector<long double> difMinimosCuadrado2_0_5,difMinimosCuadrado2_1,difMinimosCuadrado2_5,difMinimosCuadrado2_10;
      long double errorMinimosCuadrado2_0_5,errorMinimosCuadrado2_1,errorMinimosCuadrado2_5,errorMinimosCuadrado2_10;

  // Metodo 4:
    //Variables a utilizar Funcion 1:
      vector<long double> difSplineCubico1_0_5,difSplineCubico1_1,difSplineCubico1_5,difSplineCubico1_10;
      long double errordifSplineCubico1_0_5,errordifSplineCubico1_1,errordifSplineCubico1_5,errordifSplineCubico1_10;
    //Variables a utilizar Funcion 2:
      vector<long double> difSplineCubico2_0_5,difSplineCubico2_1,difSplineCubico2_5,difSplineCubico2_10;
      long double errorSplineCubico2_0_5,errorSplineCubico2_1,errorSplineCubico2_5,errorSplineCubico2_10;

  // Variables ocupadas para la parte 2 del enunciados:

      // Valores reales de la integral
      long double integral_F1,integral_F2;

      // Funcion 1 :
      long double trapecio_F1,simpson_F1,errorTrapecio_F1,errorSimpson_F1;

      // Funcion 2: 
      long double trapecio_F2,simpson_F2,errorTrapecio_F2,errorSimpson_F2;

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
                cout<<"Ya realiza la parte 1 del laboratorio prosiva con la parte numero dos "<<endl;
                break;
              }

              if(bandera == 2 )
              {
                cout<<"Ya realizo las dos opciones del programa, debe reiniciarlo (Opcion 3) "<<endl;
                break;
              }
              //Vector x interpolado en 0.5, 1, 5, 10 (Asignando valores)
              vectorX_0_5 = inter.vectorX(0.5,intervaloMenor,intervaloMayor);
              vectorX_1 = inter.vectorX(1,intervaloMenor,intervaloMayor);
              vectorX_5 = inter.vectorX(5,intervaloMenor,intervaloMayor);
              vectorX_10 = inter.vectorX(10,intervaloMenor,intervaloMayor);
              //Vector f(x) donde x son los x interpolados antes. (Función 1) (Asignando valores)
              vector1_Y_0_5 = inter.vectorY(vectorX_0_5,1);
              vector1_Y_1 = inter.vectorY(vectorX_1,1);
              vector1_Y_5 = inter.vectorY(vectorX_5,1);
              vector1_Y_10 = inter.vectorY(vectorX_10,1);

              //Vector f(x) donde x son los x interpolados antes. (Función 2) (Asignando valores)
              vector2_Y_0_5 = inter.vectorY(vectorX_0_5,2);
              vector2_Y_1 = inter.vectorY(vectorX_1,2);
              vector2_Y_5 = inter.vectorY(vectorX_5,2);
              vector2_Y_10 = inter.vectorY(vectorX_10,2);

              //Vector para graficar escala logaritmica (Asignando valores)
              vectorXInterpolado_0_05 = inter.vectorX(0.05,intervaloMenor,intervaloMayor);
              vector1_Y_Interpolado_0_05 = inter.vectorY(vectorXInterpolado_0_05,1);
              vector2_Y_Interpolado_0_05 = inter.vectorY(vectorXInterpolado_0_05,2);

              //Prueba

              vectorX_50 = inter.vectorX(50,intervaloMenor,intervaloMayor);
              vector1_Y_50 = inter.vectorY(vectorX_50,1);

              /* Probando separacion de verctores ...
              //escribirArchivoDatos(archivoaux,vectorXInterpolado_0_05);
              //escribirArchivoDatos(archivoaux,vectorX_0_5);
              //escribirArchivoDatos(archivoaux,vectorX_1);
              //escribirArchivoDatos(archivoaux,vectorX_5);
              */
              //escribirArchivoDatos(archivoaux,vectorXInterpolado_0_05);
              

              
              // Valores reales de las funciones 
                // Funcion 1
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_0_05_F1.txt",vectorXInterpolado_0_05,vector1_Y_Interpolado_0_05);
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_0_5_F1.txt",vectorX_0_5,vector1_Y_0_5);
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_1_F1.txt",vectorX_1,vector1_Y_1);
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_5_F1.txt",vectorX_5,vector1_Y_5);
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_10_F1.txt",vectorX_10,vector1_Y_10);
                // Funcion 2
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_0_05_F2.txt",vectorXInterpolado_0_05,vector2_Y_Interpolado_0_05);
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_0_5_F2.txt",vectorX_0_5,vector2_Y_0_5);
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_1_F2.txt",vectorX_1,vector2_Y_1);
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_5_F2.txt",vectorX_5,vector2_Y_5);
              escribirArchivo( (char*)"../../GraficarMatlab/ResultadosReales/real_10_F2.txt",vectorX_10,vector2_Y_10);
              
                // METODOS DE INTERPOLACION 

              //Metodo 1 : DIFERENCIAS FINITAS
              archivoSalidaParte1 << ""<< endl;
              archivoSalidaParte1 << "METODOS DE INTERPOLACION:" << endl;
              
              archivoSalidaParte1 << ""<< endl;
              archivoSalidaParte1 << "Diferencias divididas:" << endl;
              archivoSalidaParte1 << ""<< endl;
              archivoSalidaParte1 << "Funcion 1 :" << func1 << endl;
              archivoSalidaParte1 << ""<< endl;

                //METODO DIFERENCIAS DIVIDIDAS
              // Funcion 1

              difDivididas1_0_5 = inter.diferenciaDivididas(vectorX_0_5,vector1_Y_0_5,vectorXInterpolado_0_05,768);     
              errorDivididos1_0_5 = inter.RMSE(difDivididas1_0_5,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con X = 0.5: "<<errorDivididos1_0_5<<endl;
              
              difDivididas1_1 = inter.diferenciaDivididas(vectorX_1,vector1_Y_1,vectorXInterpolado_0_05,368);              
              errorDivididos1_1 = inter.RMSE(difDivididas1_1,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 1: "<<errorDivididos1_1<<endl;
              
              difDivididas1_5 = inter.diferenciaDivididas(vectorX_5,vector1_Y_5,vectorXInterpolado_0_05,46);
              errorDivididos1_5 = inter.RMSE(difDivididas1_5,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 5: "<<errorDivididos1_5<<endl;
              
              difDivididas1_10 = inter.diferenciaDivididas(vectorX_10,vector1_Y_10,vectorXInterpolado_0_05,15);
              errorDivididos1_10 = inter.RMSE(difDivididas1_10,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 10: "<<errorDivididos1_10<<endl;

              escribirArchivo((char*)"../../GraficarMatlab/DifDivididas/Func1_0_5.txt",vectorXInterpolado_0_05,difDivididas1_0_5);
              escribirArchivo((char*)"../../GraficarMatlab/DifDivididas/Func1_1.txt",vectorXInterpolado_0_05,difDivididas1_1);
              escribirArchivo((char*)"../../GraficarMatlab/DifDivididas/Func1_5.txt",vectorXInterpolado_0_05,difDivididas1_5);
              escribirArchivo((char*)"../../GraficarMatlab/DifDivididas/Func1_10.txt",vectorXInterpolado_0_05,difDivididas1_10);
              
              // Colocando salto de linea al archivo 
              archivoSalidaParte1<<endl;
              archivoSalidaParte1<<"**********************************************"<<endl;
              archivoSalidaParte1<<endl;

              // Comnezamos el proceso para la funcion 2
              archivoSalidaParte1 << "Funcion 2 :" << func2 << endl;
              archivoSalidaParte1 << ""<< endl;

              //Funcion 2              
              
              difDivididas2_0_5 = inter.diferenciaDivididas(vectorX_0_5,vector2_Y_0_5,vectorXInterpolado_0_05,800);
              errorDivididos2_0_5 = inter.RMSE(difDivididas2_0_5,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con X = 0.5: "<<errorDivididos2_0_5<<endl;
             
              difDivididas2_1 = inter.diferenciaDivididas(vectorX_1,vector2_Y_1,vectorXInterpolado_0_05,400);
              errorDivididos2_1 = inter.RMSE(difDivididas2_1,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 1: "<<errorDivididos2_1<<endl;
              
              difDivididas2_5 = inter.diferenciaDivididas(vectorX_5,vector2_Y_5,vectorXInterpolado_0_05,80);
              errorDivididos2_5 = inter.RMSE(difDivididas2_5,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 5: "<<errorDivididos2_5<<endl;
              
              difDivididas2_10 = inter.diferenciaDivididas(vectorX_10,vector2_Y_10,vectorXInterpolado_0_05,40);
              errorDivididos2_10 = inter.RMSE(difDivididas2_10,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 10: "<<errorDivididos2_10<<endl;
              
              escribirArchivo((char*)"../../GraficarMatlab/DifDivididas/Func2_0_5.txt",vectorXInterpolado_0_05,difDivididas2_0_5);
              escribirArchivo((char*)"../../GraficarMatlab/DifDivididas/Func2_1.txt",vectorXInterpolado_0_05,difDivididas2_1);
              escribirArchivo((char*)"../../GraficarMatlab/DifDivididas/Func2_5.txt",vectorXInterpolado_0_05,difDivididas2_5);
              escribirArchivo((char*)"../../GraficarMatlab/DifDivididas/Func2_10.txt",vectorXInterpolado_0_05,difDivididas2_10);
              

              // Colocando salto de linea al archivo 
              archivoSalidaParte1<<endl;
              archivoSalidaParte1<<"**********************************************"<<endl;
              archivoSalidaParte1<<endl;

              archivoSalidaParte1 << ""<< endl;
              archivoSalidaParte1 << "Minimos Cuadrado:" << endl;
              archivoSalidaParte1 << ""<< endl;
              archivoSalidaParte1 << "Funcion 1 :" << func1 << endl;
              archivoSalidaParte1 << ""<< endl; 

                // METODO MINIMOS CUADRADOS

              //Funcion 1
              
              difMinimosCuadrado1_0_5 = inter.minimosCuadrados(vectorX_0_5,vector1_Y_0_5,vectorXInterpolado_0_05,40);
              errorMinimosCuadrado1_0_5 = inter.RMSE(difMinimosCuadrado1_0_5,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 0.5: "<<errorMinimosCuadrado1_0_5<<endl;
              
              difMinimosCuadrado1_1 = inter.minimosCuadrados(vectorX_1,vector1_Y_1,vectorXInterpolado_0_05,40);
              errorMinimosCuadrado1_1 = inter.RMSE(difMinimosCuadrado1_1,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 1: "<<errorMinimosCuadrado1_1<<endl;
              
              difMinimosCuadrado1_5 = inter.minimosCuadrados(vectorX_5,vector1_Y_5,vectorXInterpolado_0_05,40);
              errorMinimosCuadrado1_5 = inter.RMSE(difMinimosCuadrado1_5,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 5: "<<errorMinimosCuadrado1_5<<endl;
              
              difMinimosCuadrado1_10 = inter.minimosCuadrados(vectorX_10,vector1_Y_10,vectorXInterpolado_0_05,40);  
              errorMinimosCuadrado1_10 = inter.RMSE(difMinimosCuadrado1_10,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 10: "<<errorMinimosCuadrado1_10<<endl;            

              escribirArchivo((char*)"../../GraficarMatlab/MinCuadrados/Func1_0_5.txt",vectorXInterpolado_0_05,difMinimosCuadrado1_0_5);
              escribirArchivo((char*)"../../GraficarMatlab/MinCuadrados/Func1_1.txt",vectorXInterpolado_0_05,difMinimosCuadrado1_1);
              escribirArchivo((char*)"../../GraficarMatlab/MinCuadrados/Func1_5.txt",vectorXInterpolado_0_05,difMinimosCuadrado1_5);
              escribirArchivo((char*)"../../GraficarMatlab/MinCuadrados/Func1_10.txt",vectorXInterpolado_0_05,difMinimosCuadrado1_10);


              // Colocando salto de linea al archivo 
              archivoSalidaParte1<<endl;
              archivoSalidaParte1<<"**********************************************"<<endl;
              archivoSalidaParte1<<endl;


              // Comnezamos el proceso para la funcion 2
              archivoSalidaParte1 << "Funcion 2 :" << func2 << endl;
              archivoSalidaParte1 << ""<< endl;

              //Funcion 2

              difMinimosCuadrado2_0_5 = inter.minimosCuadrados(vectorX_0_5,vector2_Y_0_5,vectorXInterpolado_0_05,15);
              errorMinimosCuadrado2_0_5 = inter.RMSE(difMinimosCuadrado2_0_5,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 0.5: "<<errorMinimosCuadrado2_0_5<<endl;
              
              difMinimosCuadrado2_1 = inter.minimosCuadrados(vectorX_1,vector2_Y_1,vectorXInterpolado_0_05,15);
              errorMinimosCuadrado2_1 = inter.RMSE(difMinimosCuadrado2_1,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 1: "<<errorMinimosCuadrado2_1<<endl;
              
              difMinimosCuadrado2_5 = inter.minimosCuadrados(vectorX_5,vector2_Y_5,vectorXInterpolado_0_05,15);
              errorMinimosCuadrado2_5 = inter.RMSE(difMinimosCuadrado2_5,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 5: "<<errorMinimosCuadrado2_5<<endl;
              
              difMinimosCuadrado2_10 = inter.minimosCuadrados(vectorX_10,vector2_Y_10,vectorXInterpolado_0_05,15);
              errorMinimosCuadrado2_10 = inter.RMSE(difMinimosCuadrado2_10,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 10: "<<errorMinimosCuadrado2_10<<endl;
              
              escribirArchivo((char*)"../../GraficarMatlab/MinCuadrados/Func2_0_5.txt",vectorXInterpolado_0_05,difMinimosCuadrado2_0_5);
              escribirArchivo((char*)"../../GraficarMatlab/MinCuadrados/Func2_1.txt",vectorXInterpolado_0_05,difMinimosCuadrado2_1);
              escribirArchivo((char*)"../../GraficarMatlab/MinCuadrados/Func2_5.txt",vectorXInterpolado_0_05,difMinimosCuadrado2_5);
              escribirArchivo((char*)"../../GraficarMatlab/MinCuadrados/Func2_10.txt",vectorXInterpolado_0_05,difMinimosCuadrado2_10);
              
              // Colocando salto de linea al archivo 
              archivoSalidaParte1<<endl;
              archivoSalidaParte1<<"**********************************************"<<endl;
              archivoSalidaParte1<<endl;


              archivoSalidaParte1 << ""<< endl;
              archivoSalidaParte1 << "Diferencias finitas:" << endl;
              archivoSalidaParte1 << ""<< endl;
              archivoSalidaParte1 << "Funcion 1 :" << func1 << endl;
              archivoSalidaParte1 << ""<< endl;

                // METODO SPLINE CUBICO 

              //Funcion 1
              
              difFinitas1_0_5 = inter.diferenciasFinitas(vectorX_0_5,vector1_Y_0_5,vectorXInterpolado_0_05,768);
              errorFinito1_0_5 = inter.RMSE(difFinitas1_0_5,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con X = 0.5: "<<errorFinito1_0_5<<endl;
              
              difFinitas1_1 = inter.diferenciasFinitas(vectorX_1,vector1_Y_1,vectorXInterpolado_0_05,368);
              errorFinito1_1 = inter.RMSE(difFinitas1_1,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 1: "<<errorFinito1_1<<endl;
              
              difFinitas1_5 = inter.diferenciasFinitas(vectorX_5,vector1_Y_5,vectorXInterpolado_0_05,46);
              errorFinito1_5 = inter.RMSE(difFinitas1_5,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 5: "<<errorFinito1_5<<endl;
              
              difFinitas1_10 = inter.diferenciasFinitas(vectorX_10,vector1_Y_10,vectorXInterpolado_0_05,15); 
              errorFinito1_10 = inter.RMSE(difFinitas1_10,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 10: "<<errorFinito1_10<<endl;             

              escribirArchivo((char*)"../../GraficarMatlab/DifFinitas/Func1_0_5.txt",vectorXInterpolado_0_05,difFinitas1_0_5);
              escribirArchivo((char*)"../../GraficarMatlab/DifFinitas/Func1_1.txt",vectorXInterpolado_0_05,difFinitas1_1);
              escribirArchivo((char*)"../../GraficarMatlab/DifFinitas/Func1_5.txt",vectorXInterpolado_0_05,difFinitas1_5);
              escribirArchivo((char*)"../../GraficarMatlab/DifFinitas/Func1_10.txt",vectorXInterpolado_0_05,difFinitas1_10);

              // Colocando salto de linea al archivo 
              archivoSalidaParte1<<endl;
              archivoSalidaParte1<<"**********************************************"<<endl;
              archivoSalidaParte1<<endl;


              // Comnezamos el proceso para la funcion 2
              archivoSalidaParte1 << "Funcion 2 :" << func2 << endl;
              archivoSalidaParte1 << ""<< endl;

              //Funcion 2

              difFinitas2_0_5 = inter.diferenciasFinitas(vectorX_0_5,vector2_Y_0_5,vectorXInterpolado_0_05,800);
              errorFinito2_0_5 = inter.RMSE(difFinitas2_0_5,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con X = 0.5: "<<errorFinito2_0_5<<endl;
              
              difFinitas2_1 = inter.diferenciasFinitas(vectorX_1,vector2_Y_1,vectorXInterpolado_0_05,400);
              errorFinito2_1 = inter.RMSE(difFinitas2_1,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 1: "<<errorFinito2_1<<endl;
              
              difFinitas2_5 = inter.diferenciasFinitas(vectorX_5,vector2_Y_5,vectorXInterpolado_0_05,80);
              errorFinito2_5 = inter.RMSE(difFinitas2_5,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 5: "<<errorFinito2_5<<endl;
              
              difFinitas2_10 = inter.diferenciasFinitas(vectorX_10,vector2_Y_10,vectorXInterpolado_0_05,40);
              errorFinito2_10 = inter.RMSE(difFinitas2_10,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 10: "<<errorFinito2_10<<endl;
              
              escribirArchivo((char*)"../../GraficarMatlab/DifFinitas/Func2_0_5.txt",vectorXInterpolado_0_05,difFinitas2_0_5);
              escribirArchivo((char*)"../../GraficarMatlab/DifFinitas/Func2_1.txt",vectorXInterpolado_0_05,difFinitas2_1);
              escribirArchivo((char*)"../../GraficarMatlab/DifFinitas/Func2_5.txt",vectorXInterpolado_0_05,difFinitas2_5);
              escribirArchivo((char*)"../../GraficarMatlab/DifFinitas/Func2_10.txt",vectorXInterpolado_0_05,difFinitas2_10);
              
              // Colocando salto de linea al archivo 
              archivoSalidaParte1<<endl;
              archivoSalidaParte1<<"**********************************************"<<endl;
              archivoSalidaParte1<<endl;

              //Metodo 4 : SPLINE CÚBICOS

              archivoSalidaParte1 << ""<< endl;
              archivoSalidaParte1 << "Spline Cubico:" << endl;
              archivoSalidaParte1 << ""<< endl;
              archivoSalidaParte1 << "Funcion 1 :" << func1 << endl;
              archivoSalidaParte1 << ""<< endl;

                // METODO DIFERENCIAS FINITAS

              //Funcion 1
              
              difSplineCubico1_0_5 = inter.splineCubico(vectorX_0_5,vector1_Y_0_5,vectorXInterpolado_0_05);
              errordifSplineCubico1_0_5 = inter.RMSE(difSplineCubico1_0_5,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 0.5: "<<errordifSplineCubico1_0_5<<endl;
              
              difSplineCubico1_1 = inter.splineCubico(vectorX_1,vector1_Y_1,vectorXInterpolado_0_05);
              errordifSplineCubico1_1 = inter.RMSE(difSplineCubico1_1,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 1: "<<errordifSplineCubico1_1<<endl;
              
              difSplineCubico1_5 = inter.splineCubico(vectorX_5,vector1_Y_5,vectorXInterpolado_0_05);
              errordifSplineCubico1_5 = inter.RMSE(difSplineCubico1_5,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 5: "<<errordifSplineCubico1_5<<endl;
              
              difSplineCubico1_10 = inter.splineCubico(vectorX_10,vector1_Y_10,vectorXInterpolado_0_05);
              errordifSplineCubico1_10 = inter.RMSE(difSplineCubico1_10,vector1_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 10: "<<errordifSplineCubico1_10<<endl;

              escribirArchivo((char*)"../../GraficarMatlab/SplineCubico/Func1_0_5.txt",vectorXInterpolado_0_05,difSplineCubico1_0_5);
              escribirArchivo((char*)"../../GraficarMatlab/SplineCubico/Func1_1.txt",vectorXInterpolado_0_05,difSplineCubico1_1);
              escribirArchivo((char*)"../../GraficarMatlab/SplineCubico/Func1_5.txt",vectorXInterpolado_0_05,difSplineCubico1_5);
              escribirArchivo((char*)"../../GraficarMatlab/SplineCubico/Func1_10.txt",vectorXInterpolado_0_05,difSplineCubico1_10);

        
              // Colocando salto de linea al archivo 
              archivoSalidaParte1<<endl;
              archivoSalidaParte1<<"**********************************************"<<endl;
              archivoSalidaParte1<<endl;


              // Comnezamos el proceso para la funcion 2
              archivoSalidaParte1 << "Funcion 2 :" << func2 << endl;
              archivoSalidaParte1 << ""<< endl;

              //Funcion 2

              difSplineCubico2_0_5 = inter.splineCubico(vectorX_0_5,vector2_Y_0_5,vectorXInterpolado_0_05);
              errorSplineCubico2_0_5 = inter.RMSE(difSplineCubico2_0_5,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 0.5: "<<errorSplineCubico2_0_5<<endl;
              
              difSplineCubico2_1 = inter.splineCubico(vectorX_1,vector2_Y_1,vectorXInterpolado_0_05);
              errorSplineCubico2_1 = inter.RMSE(difSplineCubico2_1,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 1: "<<errorSplineCubico2_1<<endl;
              
              difSplineCubico2_5 = inter.splineCubico(vectorX_5,vector2_Y_5,vectorXInterpolado_0_05);
              errorSplineCubico2_5 = inter.RMSE(difSplineCubico2_5,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 5: "<<errorSplineCubico2_5<<endl;
              
              difSplineCubico2_10 = inter.splineCubico(vectorX_10,vector2_Y_10,vectorXInterpolado_0_05);
              errorSplineCubico2_10 = inter.RMSE(difSplineCubico2_10,vector2_Y_Interpolado_0_05);
              archivoSalidaParte1<<"Error con x = 10: "<<errorSplineCubico2_10<<endl;

              escribirArchivo((char*)"../../GraficarMatlab/SplineCubico/Func2_0_5.txt",vectorXInterpolado_0_05,difSplineCubico2_0_5);
              escribirArchivo((char*)"../../GraficarMatlab/SplineCubico/Func2_1.txt",vectorXInterpolado_0_05,difSplineCubico2_1);
              escribirArchivo((char*)"../../GraficarMatlab/SplineCubico/Func2_5.txt",vectorXInterpolado_0_05,difSplineCubico2_5);
              escribirArchivo((char*)"../../GraficarMatlab/SplineCubico/Func2_10.txt",vectorXInterpolado_0_05,difSplineCubico2_10);

              // Finalizando el archivo
              archivoSalidaParte1<<endl;
              archivoSalidaParte1.close();
              
              // Liberando opcion 2
              bandera = 1;

              break;

       case 2: 
              if(bandera == 0 )
              {
                cout << "Primero tiene que realizar la opcion 1, para poder pasar a la segunda parte del laboratorio" ;
                break;
              }

              if(bandera == 2 )
              {
                cout << "Ya realizo esta opcion, para volver a realizar debe reiniciar el programa (Opcion 3) " ;
                break;
              }
              // Valores reales de las funciones 1 y 2.
              integral_F1 = 7.2260*pow(10,86);
              integral_F2 = 2.1334*pow(10,7);

              /* El metodo con menor error fue el de minimos cuadrados, asi que sera
              el que ocupemos para el analizes de la parte 2 del laboratorio */

              // Funcion 1
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<" Integración: "<<endl;
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"Valor Real de las funciones: "<<endl;
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"Funcion 1: "<<integral_F1<<endl;
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"Funcion 2: "<<integral_F2<<endl;
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"**********************************************"<<endl;
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"VALOR CALCULADO: ";
              archivoSalidaParte2<<"Funcion 1: "<< func1 <<endl;
              archivoSalidaParte2<<endl;
              
              //Realizamos los calculos de las integrales
              trapecio_F1 = calInte.formTrapecio(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor);
              simpson_F1 = calInte.formSimpson(difMinimosCuadrado1_0_5,intervaloMenor,intervaloMayor);
              
              //Escribimos en el archivo
              archivoSalidaParte2<<"Calculo Integral Trapecio: "<<trapecio_F1<<endl;
              archivoSalidaParte2<<"Calculo Integral Simpson: "<<simpson_F1<<endl;
              
              //Realizamos la separacion
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"**********************************************"<<endl;
              archivoSalidaParte2<<endl;

              // Empezamos a ecribir la funcion 2              
              archivoSalidaParte2<<"VALOR CALCULADO: ";
              archivoSalidaParte2<<"Funcion 2: "<< func2 <<endl;
              archivoSalidaParte2<<endl;
              
              //Realizamos los caluclos de la funcion 2
              trapecio_F2 = calInte.formTrapecio(difMinimosCuadrado2_0_5,intervaloMenor,intervaloMayor);
              simpson_F2 = calInte.formSimpson(difMinimosCuadrado2_0_5,intervaloMenor,intervaloMayor);
              
              //Escribimos en el archivo los resultado de la funcion 2
              archivoSalidaParte2<<"Calculo Integral Trapecio: "<<trapecio_F2<<endl;
              archivoSalidaParte2<<"Calculo Integral Simpson: "<<simpson_F2<<endl;
              
              //Realizamos los saltos en el archivo
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"**********************************************"<<endl;
              archivoSalidaParte2<<endl;
              
              //Escribimos los errores en el archivo
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"ERRORES RELATIVOS: "<<endl;
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"Funcion 1: "<< func1 <<endl;
              archivoSalidaParte2<<endl;
              
              //Realizamos los calculos de los errores de la funcion 1
              errorTrapecio_F1 = calInte.errorRelativo(trapecio_F1,integral_F1);
              errorSimpson_F1 = calInte.errorRelativo(simpson_F1,integral_F1);
              
              // Escribimos en e archivo los errores de la funcion 1
              archivoSalidaParte2<<"Error F1 con Trapecio: "<<errorTrapecio_F1<<endl;
              archivoSalidaParte2<<"Error F1 con Simpson: "<<errorSimpson_F1<<endl;
              
              // Realizamos un salto de lines
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"**********************************************"<<endl;
              archivoSalidaParte2<<endl;
              
              // Realizamos la escritura de la funcion 2 
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"Funcion 2: "<< func2 <<endl;
              archivoSalidaParte2<<endl;
              
              //Realizamos los calculos para la funcion 2
              errorTrapecio_F2 = calInte.errorRelativo(trapecio_F2,integral_F2);
              errorSimpson_F2 = calInte.errorRelativo(simpson_F2,integral_F2);
              
              // Escribimos en el archivo los resultados de los errores de la funcion 2
              archivoSalidaParte2<<"Error F2 con Trapecio: "<<errorTrapecio_F2<<endl;
              archivoSalidaParte2<<"Error F2 con Simpson: "<<errorSimpson_F2<<endl;
              
              // Realizamos el termino del archivo 
              archivoSalidaParte2<<endl;
              archivoSalidaParte2<<"**********************************************"<<endl;
              archivoSalidaParte2<<endl;

              // Cerramos el archivo
              archivoSalidaParte2.close();

              // Aumentamos bandera
              bandera = 2;

              break;

       case 3: cout<< " * Programa Reinciado * \n ";
               bandera = 0;
               break;

       case 4: cout <<" * Autor: Cristian Espinoza \n "<< endl;
               cout <<" * Universidad santiago de chile \n"<< endl;
               break;
       default:
               if(opcion != 5)
               cout <<"Esta opcion no esta permitida.\n"<< endl;
               break;
      }

    }while(opcion!=5);


  return 0;
}