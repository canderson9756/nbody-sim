#include "body.h"

class Integrator2d{
    private:
        int nBodies = 0;
    public:
        void update(std::vector<Body>& bodies, int flag);
        void step(std::vector<Body>& bodies);
        double dist(std::vector<Body>& bodies, int i, int j);
        void calcAcceleration(std::vector<Body>& bodies);
        void iterateBodies();
};