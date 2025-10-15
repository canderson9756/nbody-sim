#include <SFML/Graphics.hpp>
#include "simulation.h"
#include <iostream>
#include "constants.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "N-body Simulation");
    Simulation sim;
    sim.addBody(Body(0, 0, 0, 0, 1e20));
    sim.addBody(Body(1e11, 0, 0, 30000, 1e10));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        sim.step(TIME_STEP);

        // Print positions
        for (const auto& body : sim.bodies) {
            std::cout << body.position.x << " " << body.position.y << "\n";
        }
        std::cout << "\n";
    }
    return 0;
}