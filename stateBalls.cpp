#include "stateBalls.hpp"

StateBalls::StateBalls() : selectedBall(nullptr) {};

void StateBalls::AddBall(int id, float px, float py, float radius, float mass, sf::Color color){

    Ball ball = Ball(id, px, py, radius, mass, color);
    balls.push_back(ball);

}

std::vector<Ball> *StateBalls::getBalls(){
    return &balls;
}

Ball* StateBalls::getSelectedBall(){
    return selectedBall;
}

void StateBalls::setSelectedBall(Ball* selectedBall){
    this->selectedBall = selectedBall;
}