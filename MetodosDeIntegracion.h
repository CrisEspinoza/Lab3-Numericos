#ifndef METODOSDEINTEGRACION_H
#define METODOSDEINTEGRACION_H


#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#define  ARMA_DONT_USE_WRAPPER
#define  ARMA_USE_LAPACK
#include <armadillo>

using namespace std;
using namespace arma;

class MetodosDeIntegracion
{
	public:
		MetodosDeIntegracion();
		long double formTrapecio(vector<long double> vectInterpolado, long double intervaloMenor, long double intervaloMayor,long double distanci);
		long double formSimpson13(vector<long double> vectInterpolado, long double intervaloMenor, long double intervaloMayor, long double distanci);
		long double formSimpson38(vector<long double> vectInterpolado, long double intervaloMenor, long double intervaloMayor, long double distanci);
		long double formSimpson(vector<long double> vectInterpolado, long double intervaloMenor, long double intervaloMayor);
		long double errorRelativo(long double valorMedido, long double valorReal);
		vector<long double> minimosCuadrados(vector<long double> vectorX, vector<long double> vectorY, vector<long double> vectorXInterpolado_0_05, int grado);
		long double func1 (long double x);
		vector<long double> vectorX(long double distancia,int interMenor, int interMayor);
		vector<long double> vectorY(vector<long double> vectorInterX);
		long double Tolerancia(int intervaloMenor, int intervaloMayor, long double tolerancia, vector<long double> vectInterpolado, long double distancia);
};

#endif