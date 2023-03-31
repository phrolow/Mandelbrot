#include "Mandelbrot.hpp"

int main() {
    float x_min = - X_MAX_DEFAULT;
    float x_max =   X_MAX_DEFAULT;
    float y_min = - Y_MAX_DEFAULT;
    float y_max =   Y_MAX_DEFAULT;
    float scale = 1.f;

    sf::Uint8* matrix = new sf::Uint8[(WIDTH + 1) * (HEIGHT + 1) * 4];

    render(matrix, scale * x_min, scale * x_max, scale * y_min, scale * y_max);

    sf::RenderWindow window(sf::VideoMode(WIDTH + 1, HEIGHT + 1), "Mandelbrot");

    window.setFramerateLimit(60);

    sf::Texture fractal;
    fractal.create(WIDTH + 1, HEIGHT + 1);
    fractal.update(matrix);

    sf::Sprite sprite(fractal);

    float fps = NAN;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime;
    previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    sf::Font font;
    if(!font.loadFromFile("impact.ttf")) {
        printf("Font not found!\n");
    }

    char label[12] = {};

    sf::Text text;
    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code)
                {
                case sf::Keyboard::Num1:
                    scale *= 0.5f;

                    break;
                
                case sf::Keyboard::Num2:
                    scale *= 2.f;

                    break;

                case sf::Keyboard::Up:
                    y_min -= 1.f;
                    y_max -= 1.f;

                    break;
                
                case sf::Keyboard::Down:
                    y_min += 1.f;
                    y_max += 1.f;

                    break;

                case sf::Keyboard::Right:
                    x_min += 1.f;
                    x_max += 1.f;

                    break;

                case sf::Keyboard::Left:
                    x_min -= 1.f;
                    x_max -= 1.f;

                    break;

                default:
                    break;
                }
            }
        }

        render(matrix, scale * x_min, scale * x_max, scale * y_min, scale * y_max);
        fractal.update(matrix);

        currentTime = clock.getElapsedTime();
        fps = 1.f / (currentTime.asSeconds() - previousTime.asSeconds()); 
        previousTime = currentTime;

        sprintf(label, "FPS %.1f", fps);
        text.setString(label);

        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
    }

    __m128 test = _mm_cmple_ps(_mm_set1_ps(0), _mm_set1_ps(1));
    __m128i wtf = _mm_cvtps_epi32(_mm_and_ps(test, _mm_set_ps1(1)));

    printf("%x", *(&wtf));

    return 0;
}