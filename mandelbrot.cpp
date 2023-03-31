#include "Mandelbrot.hpp"

void render(sf::Uint8 *matrix, const float x_min, const float x_max, const float y_min, const float y_max) {
    float r2 = R * R;
    __m256 R2 = _mm256_set1_ps(r2);
    
    float x_scale = ((float) (x_max - x_min)) / WIDTH;
    float y_scale = ((float) (y_max - y_min)) / HEIGHT;

    __m256 X_SCALE = _mm256_set1_ps(x_scale);
    __m256 Y_SCALE = _mm256_set1_ps(y_scale);

    __m256 X_SCALE_X4 = _mm256_mul_ps(_mm256_set1_ps(8.f), X_SCALE);

    __m256 GRADATION = _mm256_set_ps(7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);

    __m256 Y0 = _mm256_set1_ps(y_min);
    __m256 X_MIN = _mm256_add_ps(_mm256_set1_ps(x_min), _mm256_mul_ps(GRADATION, X_SCALE));

    __m256 X0, X, Y, X2, Y2, XY, L2, CONDITION;

    size_t matrix_counter = 0;

    for(int y = 0; y <= HEIGHT; y++, Y0 = _mm256_add_ps(Y0, Y_SCALE)) {
        X0 = X_MIN;

        for(int x = 0; x <= WIDTH / 8; x++, X0 = _mm256_add_ps(X0, X_SCALE_X4)) {
            X = X0;
            Y = Y0;

            union 
            {
                __m256i N;
                int n_int_array[8];
            };

            N = _mm256_setzero_si256();

            for(int n = 0; n < N_MAX; n++) {
                X2 = _mm256_mul_ps(X, X);
                Y2 = _mm256_mul_ps(Y, Y);

                L2 = _mm256_add_ps(X2, Y2);

                CONDITION = _mm256_cmp_ps(L2, R2, _CMP_LT_OQ);
                int less = _mm256_movemask_ps(CONDITION);

                if(!less)
                    break;
                
                XY = _mm256_mul_ps(X, Y);

                X = _mm256_sub_ps(X2, Y2);
                X = _mm256_add_ps(X, X0);

                Y = _mm256_add_ps(XY, XY);
                Y = _mm256_add_ps(Y, Y0);
                
                N = _mm256_add_epi32(N, _mm256_cvtps_epi32(_mm256_and_ps(_mm256_set1_ps(1), CONDITION)));
            }
            
            for(int i = 0; i < 8; i++) {
                matrix[matrix_counter]     = 144;
                matrix[matrix_counter + 1] = 255 - n_int_array[i];
                matrix[matrix_counter + 2] = abs(101 - n_int_array[i]);
                matrix[matrix_counter + 3] = !!(n_int_array[i]) * 255;

                matrix_counter += 4;
            }
        }
    }
}