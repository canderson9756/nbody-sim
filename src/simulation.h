#pragma once
#include "body.h"
#include "integrator2d.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Simulation {
    private:
        std::string saveFile;
    public:
        std::vector<Body> bodies;
        Integrator2d integrator;
        Simulation() = default;
        void addBody(const Body& body);
        void step(double dt);
        void printValues();
        void saveValues(int frequency, int stepN);
        void setSaveFile(std::string filename);
};
