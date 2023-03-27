#pragma once
#include <SFML/Graphics.hpp>

class Ball{

    private:
        int id;
        float px, py;
        float vx, vy;
        float ax, ay;
        float radius, mass;
        sf::CircleShape shape;

    public:
        Ball(int id, float px, float py, float radius, float mass, sf::Color color);
        sf::CircleShape getShape() const;
        float getPositionX() const;
        float getPositionY() const;
        float getRadius() const;
        void setPosition(float px, float py);
        int getId() const;
        float getVelocityX() const;
        float getVelocityY() const;
        float getAccelerationX() const;
        float getAccelerationY() const;
        void setVelocity(float vx, float vy);
        void setAcceleration(float ax, float ay);

};