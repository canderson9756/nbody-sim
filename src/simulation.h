#pragma once
#include "body.h"
#include <vector>

class Simulation {
public:
    std::vector<Body> bodies;

    Simulation() = default;
    void addBody(const Body& body);
    void step(double dt);
};
