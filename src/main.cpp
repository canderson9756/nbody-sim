#include <SFML/Graphics.hpp>
#include "simulation.h"
#include <iostream>
#include "constants.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "N-body Simulation");
    Simulation sim;
    Body b1(- 50 * SCALE, 0.0, 0.0, 0.0, 1e20, 5e7);
    Body b2(50*SCALE, 0.0, 0.0, 0.0, 1E20, 6e7);
    // Body b3(50 * (1/SCALE), 0.0, 0.0, 10, 1e17, 6e7);
    sim.addBody(b1);
    sim.addBody(b2);
    // sim.addBody(b3);
    sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize()));
    view.zoom(10.0f);
    window.setView(view);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        
        window.clear();
        for (Body& body : sim.bodies){
            window.draw(body.shape);
        }
        window.display();
        sim.step(TIME_STEP);
        sim.printValues();
        // break;
    }
    return 0;
}