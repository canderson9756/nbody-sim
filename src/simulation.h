#pragma once
#include "body.h"
#include "integrator2d.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

class Simulation {
    public:
        class Parser{
            private:
                std::string filename;
                std::vector<double[5]> bodies;
                std::string integrator;
            public:
                Parser(std::string configFile);
                void readYAML(Simulation *sim);
        };
    private:
        std::string saveFile;
        Parser configParser;
    public:
        std::string integratorType;
        std::vector<Body> bodies;
        Integrator2d integrator;
        Vector2D centerOfMass;
        Simulation(std::string filename);
        void addBody(const Body& body);
        void step(double dt);
        void printValues();
        void saveValues(int frequency, int stepN);
        void setSaveFile(std::string filename);
        void calculateCenterOfMass();
        void parseConfig();
        void setIntegratorType(std::string integrator);
};
