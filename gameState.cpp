#include "gameState.hpp"
#include <cmath>

GameState::GameState(){

    screenWidht = 1280;
    screenHeight = 720;

    rightMouseHold = false;

    window = std::make_shared<sf::RenderWindow>(
        sf::VideoMode(screenWidht, screenHeight),
        "Balls Collision",
        sf::Style::Titlebar | sf::Style::Close
    );

    window->setPosition(sf::Vector2i(0, 0));
    window->setFramerateLimit(60);


    stateBalls = StateBalls();
    stateBalls.AddBall(stateBalls.getBalls()->size(), 200.f, 100.f, 20.f, 10.f, sf::Color::Red);
    stateBalls.AddBall(stateBalls.getBalls()->size(), 300.f, 300.f, 100.f, 10.f, sf::Color::Green);
    stateBalls.AddBall(stateBalls.getBalls()->size(), 400.f, 200.f, 50.f, 10.f, sf::Color::Blue);
    stateBalls.AddBall(stateBalls.getBalls()->size(), 500.f, 350.f, 20.f, 10.f, sf::Color::White);
    stateBalls.AddBall(stateBalls.getBalls()->size(), 700.f, 450.f, 30.f, 10.f, sf::Color::Yellow);
    stateBalls.AddBall(stateBalls.getBalls()->size(), 900.f, 600.f, 50.f, 10.f, sf::Color::Magenta);
    stateBalls.AddBall(stateBalls.getBalls()->size(), 1200.f, 720.f, 30.f, 10.f, sf::Color::Cyan);

}

void GameState::draw(){

    window->clear(sf::Color::Black);

    for(auto &ball : *(stateBalls.getBalls()))
        window->draw(ball.getShape());

    if(rightMouseHold)
        window->draw(cue, 2, sf::Lines);

    window->display();

}

void GameState::game(){

    updateBalls(clock.restart());
    overlapSolve();

}

void GameState::events(){
    
    auto e = std::make_shared<sf::Event>();
    while(window->pollEvent(*e)){

        switch(e->type){

            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                clickBall(e->mouseButton.x, e->mouseButton.y, e->mouseButton.button);           
                break;
            case sf::Event::MouseButtonReleased:
                if(stateBalls.getSelectedBall() != nullptr){
                    if(rightMouseHold){
                        rightMouseHold = false;
                        hitBall(e->mouseButton.x, e->mouseButton.y); 
                    }
                    stateBalls.setSelectedBall(nullptr);
                }
                break;
            case sf::Event::MouseMoved:
                if(stateBalls.getSelectedBall() != nullptr){
                    if(rightMouseHold)
                        createCue(e->mouseMove.x, e->mouseMove.y);
                    else
                        dragBall(e->mouseMove.x, e->mouseMove.y);
                }
                break;
            default:
                break;

        }

    }

}

void GameState::run(){

    while(window->isOpen()){
        events();
        game();
        draw();

    }

}

void GameState::clickBall(int mouseX, int mouseY, sf::Mouse::Button mouseButton){

    for(auto &ball : *(stateBalls.getBalls())){

        if( pow((ball.getPositionX() - mouseX), 2) + pow((ball.getPositionY() - mouseY), 2) < pow(ball.getRadius(), 2)){
            stateBalls.setSelectedBall(&ball);

            if(mouseButton == sf::Mouse::Right){
                rightMouseHold = true;
                createCue(mouseX, mouseY);
            }

            break;
        }

    }

}

void GameState::dragBall(int mouseX, int mouseY){
    
    stateBalls.getSelectedBall()->setPosition(mouseX, mouseY);

}

void GameState::createCue(int mouseX, int mouseY){

    cue[0] = sf::Vertex(sf::Vector2f(stateBalls.getSelectedBall()->getPositionX(), stateBalls.getSelectedBall()->getPositionY()));
    cue[1] = sf::Vertex(sf::Vector2f(mouseX, mouseY));
}


void GameState::hitBall(int mouseX, int mouseY){
    float acceleration = -200;

    float velocityX = 2 * (stateBalls.getSelectedBall()->getPositionX() - mouseX);
    float velocityY = 2 * (stateBalls.getSelectedBall()->getPositionY() - mouseY);
    
    float velocity = sqrt(pow(velocityX, 2) + pow(velocityY, 2));

    stateBalls.getSelectedBall()->setAcceleration(
        velocityX/velocity * acceleration,
        velocityY/velocity * acceleration
    );

    stateBalls.getSelectedBall()->setVelocity(
        velocityX,
        velocityY        
    );
    
}

void GameState::overlapSolve(){

    float distanceCircles{0.f}, overlapCircles{0.f};

    for(auto &ball : *(stateBalls.getBalls())){

        for(auto &targetBall : *(stateBalls.getBalls())){

            if(ball.getId() == targetBall.getId())
                break;
            //pitágoras
            distanceCircles = sqrt(pow((ball.getPositionX() - targetBall.getPositionX()), 2) + pow((ball.getPositionY() - targetBall.getPositionY()), 2));
            overlapCircles = distanceCircles - ball.getRadius() - targetBall.getRadius();

            if(overlapCircles < 0){
                //semelhança de triângulos
                float overlapX = overlapCircles * (ball.getPositionX() - targetBall.getPositionX())/(2 * distanceCircles);
                float overlapY = overlapCircles * (ball.getPositionY() - targetBall.getPositionY())/(2 * distanceCircles);
                ball.setPosition(ball.getPositionX() - overlapX, ball.getPositionY() - overlapY);
                targetBall.setPosition(targetBall.getPositionX() + overlapX, targetBall.getPositionY() + overlapY);

            }

        }

    }

}

void GameState::updateBalls(sf::Time elapsedTime){

    float timeToStop{0};

    for(auto &ball : *(stateBalls.getBalls())){

        if(ball.getVelocityX() == 0 && ball.getVelocityY() == 0)
            continue;
      
        timeToStop = -1 * ball.getVelocityX()/ball.getAccelerationX();

        if(timeToStop<=elapsedTime.asSeconds()){
            //ball stopping
            ball.setPosition(
                ball.getPositionX() + ball.getVelocityX() * timeToStop + ball.getAccelerationX() * pow(timeToStop, 2)/2,
                ball.getPositionY() + ball.getVelocityY() * timeToStop + ball.getAccelerationY() * pow(timeToStop, 2)/2
            );
            ball.setVelocity(0.f, 0.f);
            ball.setAcceleration(0.f, 0.f);
        }
        

        ball.setPosition(
            ball.getPositionX() + ball.getVelocityX() * elapsedTime.asSeconds() + ball.getAccelerationX() * pow(elapsedTime.asSeconds(), 2)/2,
            ball.getPositionY() + ball.getVelocityY() * elapsedTime.asSeconds() + ball.getAccelerationY() * pow(elapsedTime.asSeconds(), 2)/2
        );

        ball.setVelocity(
            ball.getVelocityX() + ball.getAccelerationX() * elapsedTime.asSeconds(),
            ball.getVelocityY() + ball.getAccelerationY() * elapsedTime.asSeconds()
        );

        if(ball.getPositionX() < 0) ball.setPosition(screenWidht, ball.getPositionY());
        if(ball.getPositionX() > screenWidht) ball.setPosition(0, ball.getPositionY());
        if(ball.getPositionY() < 0) ball.setPosition(ball.getPositionX(), screenHeight);
        if(ball.getPositionY() > screenHeight) ball.setPosition(ball.getPositionX(), 0);

    }

}