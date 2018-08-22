#include "MetodosDeIntegracion.h"


MetodosDeIntegracion::MetodosDeIntegracion(){	
}

long double MetodosDeIntegracion::formTrapecio(vector<long double> vectInterpolado, long double intervaloMenor, long double intervaloMayor, long double distancia)
{
	/*
	int largo = vectInterpolado.size();
	int i;
	long double valorIntegral = 0.0;
	long double inicio = vectInterpolado[0];
	long double final = vectInterpolado[largo-1];
	long double valor = 0.0;

	for(i = 1; i < largo-1; i++)
	{
		if (vectInterpolado[i] > intervaloMayor)
			break;
		valor = valor + (vectInterpolado[i]*2.0);
	}

	valorIntegral = ((intervaloMayor-intervaloMenor) / (2*(largo-1)))*(inicio+valor+final);
	
	return valorIntegral;

	*/
	//cout<<"entre"<<endl;
	// Vector que tendra las posiciones de los intervalos 
	vector<long double> vectorPosicion = vectorX(distancia,intervaloMenor,intervaloMayor);

	//cout<<"largo vector posicion : "<< vectorPosicion.size()<<endl;
	
	//cout<<"Verificando : "<<vectorPosicion[4400]<<endl;
	
	//cout<<"entre1"<<endl;
	int largo = vectInterpolado.size() , i ,contador = 1;
	long double valores = 0.0 , valorIntegral = 0.0 , resultadoCompleto = 0.0;

	for(i = 1; i < largo-1; i++)
	{
		resultadoCompleto = intervaloMenor + intervaloMayor;
		//cout<<"largo"<<largo<<"i for : "<< i <<"i: "<< vectorPosicion[i] <<"- vector actual : "<< vectorPosicion[i] <<endl;
		if ( vectorPosicion[i] > intervaloMenor )
		{
			if (vectorPosicion[i] < intervaloMayor)
			{
				valores = valores + (2.0*vectInterpolado[i]);
			}
			contador++;
		}
		else
			break;
	}

	resultadoCompleto = resultadoCompleto + valores;
	
	valorIntegral = ((intervaloMayor-intervaloMenor) / (2*(largo-1)))*resultadoCompleto;

	return valorIntegral;
}

long double MetodosDeIntegracion::formSimpson13(vector<long double> vectInterpolado, long double intervaloMenor, long double intervaloMayor, long double distancia)
{

	// Vector que tendra las posiciones de los intervalos 
	vector<long double> vectorPosicion = vectorX(distancia,intervaloMenor,intervaloMayor);

	int largo = vectInterpolado.size() , i ,contador = 1;
	long double valoresImpares = 0.0 , valoresPares = 0.0 , valorIntegral = 0.0 , resultadoCompleto = 0.0;
/*	
	for (i = 1; i < (largo / 2) ; i++)
	{	
		if (vectInterpolado[i] < intervaloMayor)
			break;

		valoresPares = valoresPares + (2.0*vectInterpolado[i*2]);
		valoresImpares = valoresImpares +  (4.0*vectInterpolado[(i*2)-1]);
		
	}

	resultadoCompleto = valoresImpares + valoresPares;

	if(largo % 2 != 0)
	{
		resultadoCompleto = resultadoCompleto + (4.0*vectInterpolado[largo-2]);
	}

	valorIntegral = ((intervaloMayor-intervaloMenor)/(3.0*largo))*(inicial + resultadoCompleto + final);

	return valorIntegral;

*/

	for(i = 1; i < largo-1; i++)
	{
		resultadoCompleto = intervaloMenor + intervaloMayor;

		if ( vectorPosicion[i] > intervaloMenor )
		{
			if (vectorPosicion[i] < intervaloMayor)
			{
				if ( i % 2 == 0)
					valoresPares = valoresPares + (2.0*vectInterpolado[i]);
			
				else if (i % 2 != 0)
					valoresImpares = valoresImpares +  (4.0*vectInterpolado[i]);
			}
			contador++;
		}
		else
			break;
	}

	resultadoCompleto = resultadoCompleto + valoresImpares + valoresPares;
	
	valorIntegral = ((intervaloMayor-intervaloMenor)/(3.0*largo))*resultadoCompleto;

	return valorIntegral;
}

long double MetodosDeIntegracion::formSimpson38(vector<long double> vectInterpolado, long double intervaloMenor, long double intervaloMayor, long double distancia)
{

	// Vector que tendra las posiciones de los intervalos 
	vector<long double> vectorPosicion = vectorX(distancia,intervaloMenor,intervaloMayor);
	// int largoMatriz = largo-4;
	int largo = vectInterpolado.size() , i ,contador = 1, largoMatriz = largo;
	long double valores = 0.0 , valorIntegral = 0.0 , resultadoCompleto = 0.0;

	for(i = 1; i < largoMatriz-1; i++)
	{
		resultadoCompleto = intervaloMenor + intervaloMayor;

		if ( vectorPosicion[i] > intervaloMenor )
		{
			if (vectorPosicion[i] < intervaloMayor)
			{
				valores = valores + (3.0*vectInterpolado[i]);
			}
			contador++;
		}
		else
			break;
	}

	resultadoCompleto = resultadoCompleto + valores;
	
	valorIntegral = (3.0*(intervaloMayor-intervaloMenor)/( 8.0 * (largo-1)))*resultadoCompleto;

	return valorIntegral;
}

//Método de Interpolacion de los Minimos Cuadrados
vector<long double> MetodosDeIntegracion::minimosCuadrados(vector<long double> vectorX, vector<long double> vectorY, vector<long double> vectorXInterpolado_0_05, int grado)
{
	//	long double **matriz,*matriz2,*matriz3;
	int i,j,tamano=vectorX.size();
	int maxGrado = 2*grado;
	long double matrizSum[maxGrado];
	long double matrizY[maxGrado];
    vector<long double> FXresultante;
	int tamanoMatriz = grado+1;
	//cout<<"EL tamano es: "<<tamano<<endl;
	
	
	//matriz = (long double**)calloc((grado+1),sizeof(long double*));
   	//for (i = 0 ; i <= grado; ++i)
     	//matriz[i] = (long double*)calloc(grado+1,sizeof(long double));
    //matriz2 = (long double*)calloc((maxGrado),sizeof(long double));
    //matriz3 = (long double*)calloc((maxGrado),sizeof(long double));
    mat matriz = mat(tamanoMatriz,tamanoMatriz);
    mat matriz2 = mat(tamanoMatriz,1);
    vec matriz3;	 	
    //Creando las sumatorias
    
    for (i = 0; i < maxGrado; i++)
    {
    	matrizSum[i] = 0;
    	matrizY[i] = 0;
    }

    for (i = 0; i < maxGrado; i++)
    {
		for (j = 0; j < tamano; j++)
		{	
			//cout<<"El numeor a sumar es :"<<pow(vectorX[j],(long double)(i+1))<<endl;
			matrizSum[i] = matrizSum[i] + (long double)pow(vectorX[j],(long double)(i+1));
			//cout<<"El numero acumulado es: "<< matrizSum[i]<<endl;
		}   
		//cout<<"Termino la primera vuelta ----------------"<<endl; 	
   	}
   	
   	
   	//Revisando sumatorias
   	for (i = 0; i < maxGrado; i++)
   	{
   		//cout << "Resultado_" <<i<<":"<<matrizSum[i]<<endl;
   	}

   	//Rellenando matriz
   	for (i = 0; i < tamanoMatriz; i++)
   	{
   		for (j = 0; j < tamanoMatriz; j++)
   		{
   			if (i == 0 && j == 0)
   				matriz(i,j) = tamano;		
   			else
   				matriz(i,j) = matrizSum[i+j-1];
   		}	
   	}

   	//Revisando matriz
   	/*for (i = 0; i < tamanoMatriz; i++)
   	{
   		for (j = 0; j < tamanoMatriz; j++)
   		{
   			cout<<matriz(i,j)<<" - ";
   		}
   		cout<<endl;	
   	}*/

   	// Realizando matriz de Y

    for (i = 0; i < tamanoMatriz; i++)
    {
		for (j = 0; j < tamano; j++)
		{	
//			cout<<"El numeor a sumar es :"<<pow(vectorX[j],(long double)(i+1))<<endl;

//			cout<<"El numeor a vectorY[j] es :"<<vectorY[j]<<endl;

//			cout<<"El numeor a vectorY[j] es :"<<vectorY[j]*pow(vectorX[j],(long double)(i+1))<<endl;

			matrizY[i] = matrizY[i] + ( vectorY[j] * (long double)pow(vectorX[j],(long double) (i)) );
//			cout<<"El numero acumulado es: "<< matrizY[i]<<endl;
		}
		matriz2(i,0) = matrizY[i];

//		cout<<"Termino la primera vuelta ----------------"<<endl; 	
   	}

   	   	//Revisando matriz
   	for (i = 0; i < tamanoMatriz; i++)
   	{
   		//cout<<matriz2(i,0)<<endl;
   	}

   	//Mostrando vector Y
   	for (j = 0; j < tamanoMatriz; j++)
   	{
   		//cout << "Resultado_" <<i<<":"<<matriz2(j,0)<<endl;
   	}

    int tamano1 = vectorXInterpolado_0_05.size(); 
    long double yResultante = 0.0;

    mat L, U;
    lu(L, U, matriz);
    mat Y = inv(L)*matriz2;
    mat C = inv(U)*Y;

    for (i = 0; i < tamano1; i++)
    {
    	for (j = 0; j < tamanoMatriz; j++)
    	{
    		//cout<<"El vector a evaluar ahora es : "<<vectorXInterpolado_0_05[i]<<endl;
    		//cout<<"El C[" << j << "] :"<<C(j)<<endl;
    		//cout<<"El i : " << i << ", el j : " << j << endl;
    		yResultante = yResultante + ( C(j) * (long double) pow(vectorXInterpolado_0_05[i],(long double) j ) ) ;
    		//cout<<"El resultado acumulado es : " << yResultante<<endl;	
    	}
    	//cout << "El resultado final es : " << yResultante << endl;
    	//cout << "------------------ TERMINO ------------------" << endl;
        //yResultante = C(0) + C(1)*vectorXInterpolado_0_05[i] + C(2)* pow(vectorXInterpolado_0_05[i],2.0) + C(3) * pow(vectorXInterpolado_0_05[i],3.0);
        FXresultante.push_back(yResultante);
        yResultante = 0.0;
    }

    return FXresultante;	
}

// Funciones que evalua la funcion 1 con el valor ingresado
long double MetodosDeIntegracion::func1 (long double x)
{
	long double valor = exp2(x) - (3*x) ;
	return valor;
}

/*Funcion que retorna el vector que se forma para x, con la diferencia
que se ingresa como parametro*/
vector<long double> MetodosDeIntegracion::vectorX(long double distancia,int interMenor, int interMayor)
{
	vector<long double> vectorResultante;
	double i;
	
	//cout<<"entre"<<endl;
	// Iteracion de valores de x e y, segun el intervalo ingresado
	for(i = interMenor; i <= interMayor; i = i + distancia)
	{
	//cout<<"aca"<<endl;
		vectorResultante.push_back(i);
	}

	if (vectorResultante[vectorResultante.size() - 1 ] != 200.0)
	{
		vectorResultante.push_back(200.0);
	}
	
	//cout<<"sali"<<endl;
	return vectorResultante;
}


/*Funcion que retorna el vector que se forma para x, con la diferencia
que se ingresa como parametro*/
vector<long double> MetodosDeIntegracion::vectorY(vector<long double> vectorInterX)
{
	vector<long double> vectorResultante;
	long double valor = 0.0;
	int j;

	//para funcion1
	for(j = 0; j < vectorInterX.size(); j++)
	{
		//cout<<"El valor a evaluar : "<<vectorInterX[j]<<endl;
		valor = func1(vectorInterX[j]);
		vectorResultante.push_back(valor);
		valor = 0.0;
	}
	

	return vectorResultante;
}

long double MetodosDeIntegracion::errorRelativo(long double valorMedido, long double valorReal)
{
	long double error;
	long double absoluto;
	
	absoluto = valorReal-valorMedido;
	error = abs(absoluto)/valorReal;

	return error;
}

long double MetodosDeIntegracion::Tolerancia(int intervaloMenor, int intervaloMayor, long double tolerancia, vector<long double> vectInterpolado, long double distancia)
{
	/*
	long double resultado1 = formTrapecio(vectInterpolado,intervaloMenor,intervaloMayor,distancia);
	long double resultado2 = formTrapecio(vectInterpolado,intervaloMenor,( (intervaloMenor+intervaloMayor) / 2 ) , distancia ) ;
	long double resultado3 = formTrapecio(vectInterpolado,( (intervaloMenor+intervaloMayor) / 2 ), intervaloMayor, distancia);

	long double resultado1 = formSimpson13(vectInterpolado,intervaloMenor,intervaloMayor,distancia);
	long double resultado2 = formSimpson13(vectInterpolado,intervaloMenor,( (intervaloMenor+intervaloMayor) / 2 ) , distancia ) ;
	long double resultado3 = formSimpson13(vectInterpolado,( (intervaloMenor+intervaloMayor) / 2 ), intervaloMayor, distancia);
*/
	
	long double resultado1 = formSimpson38(vectInterpolado,intervaloMenor,intervaloMayor,distancia);
	long double resultado2 = formSimpson38(vectInterpolado,intervaloMenor,( (intervaloMenor+intervaloMayor) / 2 ) , distancia ) ;
	long double resultado3 = formSimpson38(vectInterpolado,( (intervaloMenor+intervaloMayor) / 2 ), intervaloMayor, distancia);

	long double valorRealF1 = 2.3183*pow(10,60);

	cout<<"El resultado1 es: "<<resultado1<<endl;
	cout<<"El resultado2 es: "<<resultado2<<endl;
	cout<<"El resultado3 es: "<<resultado3<<endl;

	long double errorFinal = abs(resultado1 - resultado2 - resultado3);

	cout<<"--------------"<<endl;
	cout<<"--------------"<<endl;
	cout<<" El error que llevamos es de : "<< errorFinal <<endl;
	cout<<"--------------"<<endl;
	cout<<"--------------"<<endl;

	long double errorRela = errorRelativo(errorFinal,valorRealF1);

	cout<<"--------------"<<endl;
	cout<<"--------------"<<endl;
	cout<<" El error relativo que llevamos es de : "<< errorRela <<endl;
	cout<<"--------------"<<endl;
	cout<<"--------------"<<endl;

	if (errorRela < tolerancia)
		return resultado1;
	else
		return ( Tolerancia( intervaloMenor , ((intervaloMenor+intervaloMayor) / 2 ) , tolerancia , vectInterpolado ,distancia ) + 
			Tolerancia( ( (intervaloMenor+intervaloMayor) / 2 ) , intervaloMayor , tolerancia , vectInterpolado ,distancia ) ) ;

	//return errorFinal;
}
