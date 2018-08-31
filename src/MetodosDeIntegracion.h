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
		long double formTrapecio(long double intervaloMenor, long double intervaloMayor);
		long double formSimpson13(long double intervaloMenor, long double intervaloMayor);
		long double formSimpson38(long double intervaloMenor, long double intervaloMayor);
		long double func1 (long double x);
		long double ToleranciaTrapecio(long double intervaloMenor, long double intervaloMayor, long double tolerancia);
		long double ToleranciaSimpson13(long double intervaloMenor, long double intervaloMayor, long double tolerancia);
		long double ToleranciaSimpson38(long double intervaloMenor, long double intervaloMayor, long double tolerancia);
		int menu (long double intervaloMenor, long double intervaloMayor, long double tolerancia, double puntos , double te, double Radio, double constante);
		mat createMatrizA(double puntos);
		mat createMatrizB(double puntos, double c,double te, double dr);
		void escribirArchivo(char* archivo,mat temperaturas, double te);
};

#endif
