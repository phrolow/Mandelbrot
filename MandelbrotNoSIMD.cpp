#include "Mandelbrot.hpp"

void render(sf::Uint8 *matrix, const float x_min, const float x_max, const float y_min, const float y_max) {
    float R2 = R * R;

    float x_scale = ((float) (x_max - x_min)) / WIDTH;
    float y_scale = ((float) (y_max - y_min)) / HEIGHT;

    float Y0 = y_min;

    float X0, X, Y, X2, Y2, XY;

    size_t matrix_counter = 0;

    for(int y = 1; y <= HEIGHT; y++, Y0 += y_scale) {
        X0 = x_min;

        for(int x = 1; x <= WIDTH; x++, X0 += x_scale) {
            X = X0;
            Y = Y0;

            int n = 0;
            for(; n < N_MAX; n++) {
                X2 = X * X;
                Y2 = Y * Y;
                XY = X * Y;
                X = X2 - Y2 + X0;
                Y = 2 * XY  + Y0;
                if(X2 + Y2 > R2)
                    break;
            }
            matrix[4 * matrix_counter]     = 144;
            matrix[4 * matrix_counter + 1] = 255 - n;
            matrix[4 * matrix_counter + 2] = abs(101 - n);
            matrix[4 * matrix_counter + 3] = !!n * 255;
            matrix_counter++;
        }
    }
}