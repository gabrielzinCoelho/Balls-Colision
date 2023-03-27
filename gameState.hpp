#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "stateBalls.hpp"

class GameState{

    std::shared_ptr<sf::RenderWindow> window;

    protected:
        void draw();
        void events();
        void game();
        void dragBall(int mouseX, int mouseY);
        void clickBall(int mouseX, int mouseY, sf::Mouse::Button mouseButton);
        void hitBall(int mouseX, int mouseY);
        void createCue(int mouseX, int mouseY);
        void overlapSolve();
        void updateBalls(sf::Time elapsedTime);

    private:
        StateBalls stateBalls;
        sf::Clock clock;
        unsigned int screenWidht, screenHeight;
        bool rightMouseHold;
        sf::Vertex cue[2];

    public:
        GameState();
        void run();

};