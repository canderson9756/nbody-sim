#include "simulation.h"
#include "constants.h"
#include <iostream>

void Simulation::addBody(const Body& body){
    bodies.push_back(body);
    integrator.iterateBodies();
}

void Simulation::step(double dt){
    integrator.step(bodies);
}

void Simulation::printValues(){
    int bodyNum = 1;
    for(Body& body : bodies){
        std::cout << "Position of body " << bodyNum <<":    " << body.position.x << ", " << body.position.y << std::endl;
        std::cout << "velocity of body " << bodyNum <<":    " << body.velocity.x << ", " << body.velocity.y << std::endl;
        std::cout << "acceleration of body " << bodyNum <<":    " << body.acceleration.x << ", " << body.acceleration.y << std::endl;
        bodyNum += 1;
    }
}