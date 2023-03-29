#include <emmintrin.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

const size_t HEIGHT = 600;
const size_t WIDTH  = 600;

const unsigned N_MAX = 256;

const float X_MAX = 3.0;
const float Y_MAX = 3.0;
const float R = 10.0;

const float XSCALE = X_MAX / WIDTH;
const float YSCALE = Y_MAX / HEIGHT;

void display(sf::Uint8 *matrix);

void render(sf::Uint8 *matrix);