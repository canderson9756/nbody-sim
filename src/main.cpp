#include <SFML/Graphics.hpp>
#include "simulation.h"
#include <iostream>
#include "constants.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "N-body Simulation");
    Simulation sim("configs/2body.YML");
    // Body b1(5e10, 0.0, 0.0, 2.2e4, 2e30, 1e10);
    // Body b2(-5e10, 0.0, 0.0,-1.8e4, 1E30, 1e10);
    // Body b3(-0.8e11, 0.0, 0.0, 2e4, 1e24, 6e9);
    // Body b4(1.5e11, 0.0, 0.0, -2.5e4, 5e24, 6e9);
    // sim.addBody(b1);
    // sim.addBody(b2);
    // sim.addBody(b3);
    // sim.addBody(b4);

    sim.setSaveFile("yamltest.csv");
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
        sim.calculateCenterOfMass();
        sf::View view(sf::Vector2f(sim.centerOfMass.x * (1/SCALE), sim.centerOfMass.y * (1/SCALE)), sf::Vector2f(window.getSize()));
        window.setView(view);
        window.display();
        sim.saveValues(10, count);
        count += 1;
        sim.step(TIME_STEP);
    }
    return 0;
}