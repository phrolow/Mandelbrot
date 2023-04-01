#include "Mandelbrot.hpp"

int main() {
    float x_min = - X_MAX_DEFAULT;
    float x_max =   X_MAX_DEFAULT;
    float y_min = - Y_MAX_DEFAULT;
    float y_max =   Y_MAX_DEFAULT;
    float scale = 0.125f;

    sf::Uint8* matrix = new sf::Uint8[WIDTH * HEIGHT * 4];

    render(matrix, scale * x_min, scale * x_max, scale * y_min, scale * y_max);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");

    sf::Texture fractal;
    fractal.create(WIDTH, HEIGHT);
    fractal.update(matrix);

    sf::Sprite sprite(fractal);

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

    float fps = NAN;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime;
    previousTime = clock.getElapsedTime();
    sf::Time currentTime;

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
                    scale *= SCALE_STEP;

                    break;
                
                case sf::Keyboard::Num2:
                    scale *= (1 / SCALE_STEP);

                    break;

                case sf::Keyboard::Up:
                    y_min -= scale;
                    y_max -= scale;

                    break;
                
                case sf::Keyboard::Down:
                    y_min += scale;
                    y_max += scale;

                    break;

                case sf::Keyboard::Right:
                    x_min += scale;
                    x_max += scale;

                    break;

                case sf::Keyboard::Left:
                    x_min -= scale;
                    x_max -= scale;

                    break;

                default:
                    break;
                }
            }
        }

        render (matrix, 
                x_min + (x_max - x_min) * (0.5f - scale), 
                x_max - (x_max - x_min) * (0.5f - scale), 
                y_min + (y_max - y_min) * (0.5f - scale), 
                y_max - (y_max - y_min) * (0.5f - scale));
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

    return 0;
}