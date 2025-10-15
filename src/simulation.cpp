#include "simulation.h"
#include "constants.h"

void Simulation::addBody(const Body& body){
    bodies.push_back(body);
}

void Simulation::step(double dt){
    for (Body& body : bodies){
        body.resetForce();
    }

    for (int i = 0; i < bodies.size(); ++i) {
        for (int j = i + 1; j < bodies.size(); ++j) {
            bodies[i].addForce(bodies[j]);
            bodies[j].addForce(bodies[i]); // Newton's third law
        }
    }

    for (Body& body : bodies){
        body.update(dt);
    }
}