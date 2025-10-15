#include <SFML/Graphics.hpp>
#include "simulation.h"
#include <iostream>
#include "constants.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "N-body Simulation");
    Simulation sim;
    Body b1(500.0, 500.0, 0.0, 0.0, 1e20, 5e7);
    Body b2(1e9, 0.0, 0.0, 30000.0, 1e10, 6e6);
    Body b3(1e3, 0.0, 0.0, 0, 1e20, 6e7);
    sim.addBody(b1);
    sim.addBody(b2);
    sim.addBody(b3);
    sf::View view(window.getDefaultView());
    view.zoom(2.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        
        Body& target = sim.bodies[0];
        sf::Vector2f targetPos(target.position.x * SCALE, target.position.y * SCALE);
        view.setCenter(targetPos);
        window.setView(view);

        window.clear();
        for (Body& body : sim.bodies){
            window.draw(body.shape);
        }
        window.display();
        sim.step(TIME_STEP);
        // break;
    }
    return 0;
}