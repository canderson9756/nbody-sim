#include "body.h"
#include "constants.h"

#include <cmath>
#include <iostream>

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

Body::Body(double x, double y, double vx, double vy, double m, double r) : position{x,y},velocity{vx,vy},mass{m},force{0,0} {
    shape.setRadius(r*(1/SCALE));
    shape.setPosition(x*(1/SCALE),y*(1/SCALE));
    shape.setFillColor(sf::Color::White);  // So it's visible
    // shape.setOrigin(shape.getRadius(), shape.getRadius());
}
 
void Body::resetForce(){
    force = {0, 0};
}

void Body::addForce(const Body& other){
    Vector2D delta = other.position - position;
    double dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    double F = G * mass * other.mass / (dist * dist                               );
    Vector2D direction = delta * (1/dist);
    force += direction * F;
}

void Body::update() {
    shape.setPosition(position.x * (1/SCALE), position.y * (1/SCALE));
}
