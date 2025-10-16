#include "integrator2d.hpp"
#include "constants.h"
#include <cmath>
#include <iostream>

const double SOFTENING = 1e9;  // Try different values (1e4 to 1e6)

void Integrator2d::iterateBodies(){
    nBodies += 1;
}

void Integrator2d::update(std::vector<Body>& bodies, int flag){
    // Iterate through the number of objects in the sim
    for(int i = 0; i<nBodies; ++i){
        // Iterate through the dimensions
        if(flag==0){
            // Updating the position vector
            bodies[i].position.x = bodies[i].position.x + bodies[i].velocity.x * (TIME_STEP/2);
            bodies[i].position.y = bodies[i].position.y + bodies[i].velocity.y * (TIME_STEP/2);
        }
        else{
            // Updating the velocity vector
            bodies[i].velocity.x = bodies[i].velocity.x + bodies[i].acceleration.x * TIME_STEP;
            bodies[i].velocity.y = bodies[i].velocity.y + bodies[i].acceleration.y * TIME_STEP;
        }
    }
}

void Integrator2d::step(std::vector<Body>& bodies){
    update(bodies, 0);
    calcAcceleration(bodies);
    update(bodies,1);
    update(bodies, 0);
}

double Integrator2d::dist(std::vector<Body>& bodies, int i, int j){
    return sqrt((bodies[i].position.x-bodies[j].position.x)*(bodies[i].position.x-bodies[j].position.x) + (bodies[i].position.y-bodies[j].position.y)*(bodies[i].position.y-bodies[j].position.y) + SOFTENING*SOFTENING);
}

void Integrator2d::calcAcceleration(std::vector<Body>& bodies){
    // Reset the acceleration vectors
    for(int i = 0; i<nBodies; ++i){
        bodies[i].acceleration.x = 0;
        bodies[i].acceleration.y = 0;
    }

    // Loop through bodies
    for(int i = 0; i<nBodies; ++i){
        // Loop through bodies to find force on i from j
        for(int j = 0; j<nBodies; ++j){
            if(i!=j){
                bodies[i].acceleration.x-= (G*bodies[j].mass*(bodies[i].position.x-bodies[j].position.x)/(dist(bodies, i, j)*dist(bodies, i, j)*dist(bodies, i, j)));
                bodies[i].acceleration.y-= (G*bodies[j].mass*(bodies[i].position.y-bodies[j].position.y)/(dist(bodies, i, j)*dist(bodies, i, j)*dist(bodies, i, j)));
                }
         }
     }
}
