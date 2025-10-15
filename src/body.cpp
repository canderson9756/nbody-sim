#include "body.h"
#include "constants.h"

#include <cmath>

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return {x+other.x, y+other.y};
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return {x-other.x, y-other.y};
}
Vector2D Vector2D::operator*(double scalar) const {
    return {x*scalar, y*scalar};
}
Vector2D& Vector2D::operator+=(const Vector2D& other){
    x += other.x;
    y += other.y;
    return *this;
}

Body::Body(double x, double y, double vx, double vy, double m) : position{x,y},velocity{vx,vy},mass{m},force{0,0} {}
 
void Body::resetForce(){
    force = {0, 0};
}

void Body::addForce(const Body& other){
    Vector2D delta = other.position - position;
    double dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    double F = G * mass * other.mass / (dist * dist);
    Vector2D direction = delta * (1/dist);
    force += direction * F;
}

void Body::update(double dt) {
    Vector2D acceleration = force * (1.0 / mass);
    velocity += acceleration * dt;
    position += velocity * dt;
}