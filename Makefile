.PHONY: all
all:
	@gcc -c main.cpp mandelbrot.cpp -mavx2 -O3
	@g++ main.o mandelbrot.o -o Mandelbrot -lsfml-graphics -lsfml-window -lsfml-system

nosimd:
	@gcc -c main.cpp MandelbrotNoSIMD.cpp -mno-sse2 -O3
	@g++ main.o MandelbrotNoSIMD.o -o Mandelbrot -lsfml-graphics -lsfml-window -lsfml-system