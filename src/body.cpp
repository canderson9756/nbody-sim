#include "body.h"
#include "constants.h"

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
 
