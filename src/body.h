#pragma once
#include <SFML/Graphics.hpp>

struct Vector2D {
    double x, y;

    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(double scalar) const;
    Vector2D& operator+=(const Vector2D& other);
};

class Body {
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D force;
    double mass;
    sf::CircleShape shape;

    Body(double x, double y, double vx, double vy, double m, double r);
    void resetForce();
    void addForce(const Body& other);
    void update();
};

