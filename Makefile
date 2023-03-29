.PHONY: all
all:
	@gcc -c main.cpp mandelbrot.cpp
	@g++ main.o mandelbrot.o -o Mandelbrot -lsfml-graphics -lsfml-window -lsfml-system
