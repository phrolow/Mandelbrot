#include <immintrin.h>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

const size_t HEIGHT = 800;
const size_t WIDTH  = 800;

const unsigned N_MAX = 256;

const float SCALE_STEP = 0.5f;
const float X_MAX_DEFAULT = 3.0f;
const float Y_MAX_DEFAULT = 3.0f;
const float R = 10.0;

const int textSize = 24;

void display(sf::Uint8 *matrix);

void render(sf::Uint8 *matrix, const float x_min, const float x_max, const float y_min, const float y_max);