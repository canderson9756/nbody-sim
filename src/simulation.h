#pragma once
#include "body.h"
#include "integrator2d.hpp"
#include <vector>

class Simulation {
public:
    std::vector<Body> bodies;
    Integrator2d integrator;

    Simulation() = default;
    void addBody(const Body& body);
    void step(double dt);
    void printValues();
};
