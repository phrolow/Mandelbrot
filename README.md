# Вступление #
Добрейшего дня всем, кто читает!
Этот проект - моя попытка оптимизировать рендер фрактала Мандельброта. У меня есть два варианта функции '''render()''', подсчитывающей картинку для фрактала: с SIMD-инструкциями (в данном проекте использован набор инструкций AVX2) и без. Также использован флаг компилятора -O3 для оптимизации.
# Компиляция #
- make - для компиляции с SIMD-инструкциями
- make nosimd - для компиляции без SIMD-инструкций
# Сравнение #
Сначала я написал код без использования SIMD-инструкций (рис. 1). Он представлен в файле MandelbrotNoSIMD.cpp. Затем, оставшись недовольным показателем FPS, я вкурил документацию по SIMD-инструкциям и переписал рендер с ними (рис. 2). Полученное соотношение приятно удивило.
![No SIMD](no_simd.png)
![SIMD](simd.png)
