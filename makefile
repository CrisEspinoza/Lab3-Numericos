all:
	g++ src/MetodosDeIntegracion.cpp src/main.cpp -o obj/main.out -std=c++14 -larmadillo -llapack -lblas
