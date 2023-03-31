#include <immintrin.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

const size_t HEIGHT = 599;
const size_t WIDTH  = 599;

const unsigned N_MAX = 256;

const float X_MAX_DEFAULT = 3.0;
const float Y_MAX_DEFAULT = 3.0;
const float R = 10.0;

const int textSize = 24;

void display(sf::Uint8 *matrix);

void render(sf::Uint8 *matrix, const float x_min, const float x_max, const float y_min, const float y_max);