#include <SFML/Graphics.hpp>
#include "simulation.h"
#include <iostream>
#include "constants.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "N-body Simulation");
    Simulation sim;
    Body b1(5e10, 0.0, 0.0, 2e4, 1e30, 1e10);
    Body b2(-5e10, 0.0, 0.0,-2e4, 1E30, 1e10);
    Body b3(-1e11, 0.0, 0.0, 2e4, 1e24, 6e9);
    sim.addBody(b1);
    sim.addBody(b2);
    sim.addBody(b3);

    sim.setSaveFile("data.csv");
    sf::View view(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize()));
    window.setView(view);

    int count = 0;

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
        sim.saveValues(10, count);
        count += 1;
        sim.step(TIME_STEP);
    }
    return 0;
}