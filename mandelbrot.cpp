#include "Mandelbrot.hpp"

void render(sf::Uint8 *matrix) {
    float R2 = R * R;

    float X0, Y0, X, Y, X2, Y2, XY;

    int x_range = WIDTH  / 2;
    int y_range = HEIGHT / 2;

    size_t matrix_counter = 0;

    for(int y = -y_range; y <= y_range; y++) {
        for(int x = -x_range; x <= x_range; x++) {
            X0 = x * XSCALE;
            Y0 = y * YSCALE;

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
            matrix[4 * matrix_counter + 2] = 255;
            matrix[4 * matrix_counter + 3] = !!n * 255;

            matrix_counter++;
        }
    }
}