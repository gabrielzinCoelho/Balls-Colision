#pragma once
#include "ball.hpp"
#include <vector>
#include <memory>

class StateBalls{
    private:
        std::vector<Ball> balls;
        Ball *selectedBall;
    public:
        StateBalls();
        void AddBall(int id, float px, float py, float radius, float mass, sf::Color color);
        std::vector<Ball> *getBalls();
        Ball *getSelectedBall();
        void setSelectedBall(Ball* selectedBall = nullptr);

};