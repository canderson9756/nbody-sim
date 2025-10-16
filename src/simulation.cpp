#include "simulation.h"
#include "constants.h"
#include <iostream>
#include <fstream>

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