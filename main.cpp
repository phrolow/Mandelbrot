#include "Mandelbrot.hpp"

int main() {
    sf::Uint8* matrix = new sf::Uint8[(WIDTH + 1) * (HEIGHT + 1) * 4];

    render(matrix);

    sf::RenderWindow window(sf::VideoMode(WIDTH + 1, HEIGHT + 1), "Mandelbrot");

    sf::Texture fractal;
    fractal.create(WIDTH + 1, HEIGHT + 1);
    fractal.update(matrix);

    sf::Sprite sprite(fractal);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}