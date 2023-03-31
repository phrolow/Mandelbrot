.PHONY: all
all:
	@gcc -c main.cpp mandelbrot.cpp -msse4.1 -mavx2
	@g++ main.o mandelbrot.o -o Mandelbrot -lsfml-graphics -lsfml-window -lsfml-system
