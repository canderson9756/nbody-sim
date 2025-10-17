#include "simulation.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

Simulation::Simulation(std::string filename) : configParser(filename){
    configParser.readYAML(this);
}

void Simulation::addBody(const Body& body){
    bodies.push_back(body);
    integrator.iterateBodies();
}

void Simulation::step(double dt){
    integrator.step(bodies);
    for (Body& body : bodies){
        body.update();
    }
}

void Simulation::printValues(){
    int bodyNum = 1;
    for(Body& body : bodies){
        std::cout << "Position of body " << bodyNum <<":    " << body.position.x << ", " << body.position.y << std::endl;
        std::cout << "scaled Position of body " << bodyNum <<":    " << body.position.x * (1/SCALE) << ", " << body.position.y * (1/SCALE) << std::endl;
        std::cout << "velocity of body " << bodyNum <<":    " << body.velocity.x << ", " << body.velocity.y << std::endl;
        std::cout << "acceleration of body " << bodyNum <<":    " << body.acceleration.x << ", " << body.acceleration.y << std::endl;
        bodyNum += 1;
    }
}

void Simulation::saveValues(int frequency, int stepN){
    if (stepN==0){
        std::ofstream csvFile;
        csvFile.open(saveFile);
        csvFile << "Timestamp";
        for(int i=0;i<bodies.size();++i){
            csvFile<<", Body "<<i;
        }
        csvFile<<"\n";
        csvFile.close();
        return;
    }
    if(stepN%frequency!=0){
        return;
    }
    std::ofstream csvFile;
    csvFile.open(saveFile, std::ios::app);
    csvFile << stepN * TIME_STEP;
    for(Body& body : bodies){
        csvFile << ", " << body.position.x << "," << body.position.y;
    }
    csvFile << "\n";
    csvFile.close();
}

void Simulation::setSaveFile(std::string filename){
    saveFile = filename;
}

void Simulation::calculateCenterOfMass(){
    double numerator_x = 0;
    double numerator_y = 0;
    double denomenator = 0;
    for(Body& body : bodies){
        numerator_x += body.mass * body.position.x;
        numerator_y += body.mass * body.position.y;
        denomenator += body.mass;
    }
    centerOfMass = {numerator_x/denomenator, numerator_y/denomenator};
}

void Simulation::setIntegratorType(std::string integrator){
    integratorType = integrator;
}

Simulation::Parser::Parser(std::string configFile) : filename(configFile){}

void Simulation::Parser::readYAML(Simulation *sim){
    YAML::Node config = YAML::LoadFile(filename);
    if(config["integrator"]){
        sim->setIntegratorType(config["integrator"].as<std::string>());
    }
    if (config["bodies"]) {
        YAML::Node bodies = config["bodies"];

        if (!bodies.IsSequence()) {
            std::cerr << "'bodies' is not a list!" << std::endl;
            return;
        }
        
        for (const auto& bodyNode : bodies) {
            double x_pos = bodyNode["x_position"].as<double>();
            double y_pos = bodyNode["y_position"].as<double>();
            double x_vel = bodyNode["x_velocity"].as<double>();
            double y_vel = bodyNode["y_velocity"].as<double>();
            double mass  = bodyNode["mass"].as<double>();
            double radius = bodyNode["radius"].as<double>();
            std::cout << "Parsed body:\n";
            std::cout << "  Position: (" << x_pos << ", " << y_pos << ")\n";
            std::cout << "  Velocity: (" << x_vel << ", " << y_vel << ")\n";
            std::cout << "  Mass: " << mass << "\n";
            std::cout << "  Radius: " << radius << "\n";

            // Create and add the body
            Body b(x_pos, y_pos, x_vel, y_vel, mass, radius);
            sim->addBody(b);
        }
    }
}
