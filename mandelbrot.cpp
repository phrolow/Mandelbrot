#include "Mandelbrot.hpp"

void render(sf::Uint8 *matrix, const float x_min, const float x_max, const float y_min, const float y_max) {
    float r2 = R * R;
    __m128 R2 = _mm_set_ps1(r2);
    
    float x_scale = ((float) (x_max - x_min)) / WIDTH;
    float y_scale = ((float) (y_max - y_min)) / HEIGHT;

    //__m128 X_SCALE_V = _mm_set_ps(3.f * x_scale, 2.f * x_scale, 1.f * x_scale, 0.f);
    //__m128 Y_SCALE_V = _mm_set_ps(3.f * y_scale, 2.f * y_scale, 1.f * y_scale, 0.f);

    const __m128 X_SCALE = _mm_set_ps1(x_scale);
    const __m128 Y_SCALE = _mm_set_ps1(y_scale);

    const __m128 X_SCALE_X4 = _mm_mul_ps(_mm_set_ps1(4.f), X_SCALE);
    //const __m128 Y_SCALE_X4 = _mm_mul_ps(_mm_set_ps1(4.f), Y_SCALE);

    __m128 GRADATION = _mm_set_ps(3.f, 2.f, 1.f, 0.f);

    //float Y0 = y_min;
    __m128 Y0 = _mm_set_ps1(y_min);
    const __m128 X_MIN = _mm_add_ps(_mm_set_ps1(x_min), _mm_mul_ps(GRADATION, X_SCALE));

    __m128 X0, X, Y, X2, Y2, XY, L2, CONDITION;

    size_t matrix_counter = 0;

    for(int y = 0; y <= HEIGHT; y++, Y0 = _mm_add_ps(Y0, Y_SCALE)) {
        X0 = X_MIN;

        for(int x = 0; x <= WIDTH / 4; x++, X0 = _mm_add_ps(X0, X_SCALE_X4)) {
            X = X0;
            Y = Y0;

            union 
            {
                __m128i N = _mm_set1_epi32(0);
                int n_int_array[4];
            };

            for(int n = 0; n < N_MAX; n++) {
                //X2 = X * X;
                //Y2 = Y * Y;
                //XY = X * Y;

                //X = X2 - Y2 + X0;
                //Y = 2 * XY  + Y0;

                // if(X2 + Y2 > R2)
                //     break;

                X2 = _mm_mul_ps(X, X);
                Y2 = _mm_mul_ps(Y, Y);

                L2 = _mm_add_ps(X2, Y2);

                CONDITION = _mm_cmple_ps(L2, R2);
                int less = _mm_movemask_ps(CONDITION);

                if(!less)
                    break;
                
                XY = _mm_mul_ps(X, Y);

                X = _mm_sub_ps(X2, Y2);
                X = _mm_add_ps(X, X0);

                Y = _mm_add_ps(XY, XY);
                Y = _mm_add_ps(Y, Y0);
                
                N = _mm_add_epi32(N, _mm_cvtps_epi32(_mm_and_ps(_mm_set1_ps(1), CONDITION)));
            }
            
            for(int i = 0; i < 4; i++) {
                matrix[matrix_counter]     = 144;
                matrix[matrix_counter + 1] = 255 - n_int_array[i];
                matrix[matrix_counter + 2] = abs(101 - n_int_array[i]);
                matrix[matrix_counter + 3] = !!(n_int_array[i]) * 255;

                matrix_counter += 4;
            }
        }
    }
}