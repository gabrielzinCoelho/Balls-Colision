#include "ball.hpp"

Ball::Ball(int id, float px, float py, float radius, float mass,sf::Color color) 
    : id(id), px(px), py(py), radius(radius), mass(mass), vx(0.f), vy(0.f), ax(0.f), ay(0.f) {

        shape = sf::CircleShape(radius);
        shape.setFillColor(color);
        shape.setPosition(px, py);
        shape.setOrigin(radius, radius);

    }

sf::CircleShape Ball::getShape() const {
    return shape;
}

float Ball::getPositionX() const {
    return px;
}

float Ball::getPositionY() const {
    return py;
}

float Ball::getRadius() const {
    return radius;
}

void Ball::setPosition(float px, float py){
    this->px = px;
    this->py = py;
    shape.setPosition(px, py);
}

int Ball::getId() const {
    return id;
}

float Ball::getVelocityX() const {
    return vx;
}
float Ball::getVelocityY() const {
    return vy;
}
float Ball::getAccelerationX() const {
    return ax;
}
float Ball::getAccelerationY() const {
    return ay;
}
void Ball::setVelocity(float vx, float vy){
    this->vx = vx;
    this->vy = vy;
}
void Ball::setAcceleration(float ax, float ay){
    this->ax = ax;
    this->ay = ay;
}