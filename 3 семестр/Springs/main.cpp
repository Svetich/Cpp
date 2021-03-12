#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Vector2f.hpp"
#include "Sphere.hpp"
//#include "Spring.hpp"
#include <iostream>


int main()
{
    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 700;

    const float DT = 0.01;
    const int NUMBALLS = 2;

    float radius = 20;

    Vector2f radiusVector = {radius, radius};

    Sphere ball1 = {{340, 550}, {10, 5}, {0, 0}, sf::Color::Blue, radius, 50};
    Sphere ball2 = {{460, 350}, {-20, -7}, {0, 0}, sf::Color::Blue, radius, 50};
    Sphere ball3 = {{580, 250}, {-0.4, 0.8}, {0, 0}, sf::Color::Blue, radius, 50};

    Sphere balls[NUMBALLS] = {ball1, ball2};

    Spring springs[NUMBALLS][NUMBALLS];

    int table[NUMBALLS][NUMBALLS] = {{0, 1}, {1, 0}};

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Springs");


    for (int i = 0; i < NUMBALLS; i++)
    {
        for (int j = i + 1; j < NUMBALLS; j++)
        {
            Vector2f tmpLengthStart = balls[i].local + radiusVector;
            Vector2f tmpLengthEnd = balls[j].local + radiusVector;

            Spring tmpSpring = {tmpLengthStart, tmpLengthEnd, tmpLengthStart, tmpLengthEnd, 0.0001, sf::Color::White};
            springs[i][j] = tmpSpring;
        }        
    }
    
    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (evnt.key.code == sf::Keyboard::Space)
                    window.close();
                break;
            }
        }
        window.clear(); 

        for (int i = 0; i < NUMBALLS; i++)
        {
            for (int j = i + 1; j < NUMBALLS; j ++)
            {
                if (table[i][j] == 1)
                {
                    springs[i][j].drawSpring(&window);
                    std::cout << springs[i][j].lengthEnd.x << std::endl;
                    std::cout << springs[i][j].lengthEnd.y << std::endl;
                    balls[i].drawSphere(&window);
                    balls[j].drawSphere(&window);
                }
            }
        }

        for (int i = 0; i < NUMBALLS; i++)
        {
            balls[i].checkCollisionSphere(WINDOW_WIDTH, WINDOW_HEIGHT);
            balls[i].moveSphere(DT);
        }

        for (int i = 0; i < NUMBALLS; i++)
        {
            for (int j = i + 1; j < NUMBALLS; j++)
            {
                if (table[i][j] == 1)
                {   
                    balls[i].calculationAcceleration(&springs[i][j]);
                    balls[j].calculationAcceleration(&springs[i][j]);
                }
            }
        }
        window.display();
    }
    return 0;
}