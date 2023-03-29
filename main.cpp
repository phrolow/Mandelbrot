#include "Mandelbrot.hpp"

int main() {
    sf::Uint8* matrix = new sf::Uint8[(WIDTH + 1) * (HEIGHT + 1) * 4];

    render(matrix);

    sf::RenderWindow window(sf::VideoMode(WIDTH + 1, HEIGHT + 1), "Mandelbrot");

    window.setFramerateLimit(60);

    sf::Texture fractal;
    fractal.create(WIDTH + 1, HEIGHT + 1);
    fractal.update(matrix);

    sf::Sprite sprite(fractal);

    float fps = NAN;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime;
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
                case sf::Keyboard::F:
                    previousTime = clock.getElapsedTime();

                    render(matrix);
                    fractal.update(matrix);

                    currentTime = clock.getElapsedTime();
                    fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); 
                    printf("%g\n", fps); 
                    previousTime = currentTime;

                    break;
                
                default:
                    break;
                }
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}