all:
	g++ MetodosDeIntegracion.cpp main.cpp -o main.out -std=c++14 -larmadillo -llapack -lblas
