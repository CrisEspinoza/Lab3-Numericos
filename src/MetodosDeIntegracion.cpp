#include "MetodosDeIntegracion.h"


MetodosDeIntegracion::MetodosDeIntegracion(){	
}

long double MetodosDeIntegracion::formTrapecio(long double intervaloMenor, long double intervaloMayor)
{
	long double valorIntegral = ( (intervaloMayor-intervaloMenor) / 2.0 ) * ( func1(intervaloMenor) + func1(intervaloMayor) ) ;

	return valorIntegral;
}

long double MetodosDeIntegracion::formSimpson13(long double intervaloMenor, long double intervaloMayor)
{

	long double punto1 = intervaloMenor + ( (intervaloMenor+intervaloMayor) / 3.0) ;

	long double valorIntegral = ((intervaloMayor-intervaloMenor) / 3.0 ) * ( func1(intervaloMenor) + (4.0 * func1 (punto1) ) + func1(intervaloMayor) );

	return valorIntegral;
}

long double MetodosDeIntegracion::formSimpson38(long double intervaloMenor, long double intervaloMayor)
{
	long double distancia = ( (intervaloMenor+intervaloMayor)/4.0) ;
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

	medio = ( (intervaloMayor+intervaloMenor) / 2.0 ) ;
	resultado1 = formTrapecio(intervaloMenor,intervaloMayor);
	resultado2 = formTrapecio(intervaloMenor,medio);
	resultado3 = formTrapecio( medio, intervaloMayor);

	if (resultado1 - resultado2 - resultado3 < tolerancia)
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

	medio = ( (intervaloMayor+intervaloMenor) / 2.0 ) ;
	resultado1 = formSimpson13(intervaloMenor,intervaloMayor);
	resultado2 = formSimpson13(intervaloMenor,medio);
	resultado3 = formSimpson13( medio, intervaloMayor);

	if (resultado1 - resultado2 - resultado3 < tolerancia)
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

	medio = ( (intervaloMayor+intervaloMenor) / 2.0 ) ;
	resultado1 = formSimpson38(intervaloMenor,intervaloMayor);
	resultado2 = formSimpson38(intervaloMenor,medio);
	resultado3 = formSimpson38(medio, intervaloMayor);		
	
	if (resultado1 - resultado2 - resultado3 < tolerancia)
	{
		return resultado1;
	}
	else{
		return ( ToleranciaSimpson38( intervaloMenor ,medio, tolerancia) + ToleranciaSimpson38(medio, intervaloMayor , tolerancia ) ) ;
	}
}