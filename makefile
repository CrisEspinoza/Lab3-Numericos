all:
	g++ ../Integral/calcIntegral.cpp ../interpolacion/interpolacion.cpp main.cpp -o main.out -std=c++14 -larmadillo -llapack -lblas






#g++ ../interpolacion/interpolacion.cpp ../Integral/calcIntegral.cpp numericos.cpp -o main.out -std=c++14 -larmadillo -llapack -lblas
