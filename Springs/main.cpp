#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Vector2f.hpp"
#include "Sphere.hpp"
#include "Spring.hpp"
#include <iostream>


double getRandomNumber(double minimum, double maximum)
{
    double randZeroOne = rand() / static_cast<double>(RAND_MAX);
    double randInterval = randZeroOne * (maximum - minimum);
    double randMinMax = randInterval + minimum;
    return randMinMax;
}


int main()
{
    srand(static_cast<unsigned int>(time(0)));

    const int WINDOW_WIDTH = 1200;
    const int WINDOW_HEIGHT = 700;

    const float DT = 0.01;

    const int NUMBALLS = 2;
    const int NUMSPRINGS = 1;

    float radius = 20;

    Vector2f radiusVector = {radius, radius};

    Sphere ball1 = {{640, 550}, {0.1, 0.5}, {0, 0}, sf::Color::Blue, radius, 50};
    Sphere ball2 = {{960, 350}, {-0.2, -0.7}, {0, 0}, sf::Color::Blue, radius, 50};

    Sphere balls[NUMBALLS] = {ball1, ball2};

    Spring springs[NUMSPRINGS];

    int table[NUMBALLS][NUMBALLS] = {{0, 1}, {1, 0}};

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Springs");


    for (int i = 0; i < NUMBALLS; i++)
    {
        for (int j = i + 1; j < NUMBALLS; j++)
        {
            Vector2f tmpLengthStart = balls[i].local + radiusVector;
            Vector2f tmpLengthEnd = balls[j].local + radiusVector;
        
            sf::Color tmpColor = sf::Color::White;

            Spring tmpSpring = {tmpLengthStart, tmpLengthEnd, tmpLengthStart, tmpLengthEnd, 0.0001, tmpColor};

            springs[i] = tmpSpring;
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
                    Spring spring;
                    spring.drawSpring(springs[i], &window);
                }
            }
        }

        for (int i = 0; i < NUMBALLS; i++)
        {
            Sphere sphere;
            sphere.drawSphere(balls[i], &window);    
        }

        for (int i = 0; i < NUMBALLS; i++)
        {
            Sphere sphere; 
            sphere.checkCollisionSphere(&balls[i], WINDOW_WIDTH, WINDOW_HEIGHT);

            sphere.moveSphere(&balls[i], DT);
        }

        for (int i = 0; i < NUMBALLS; i++)
        {
            for (int j = i + 1; j < NUMBALLS; j++)
            {
                if (table[i][j] == 1)
                {
                    springs[i].lengthStart = balls[j].local + radiusVector;
                    springs[i].lengthEnd = balls[i].local + radiusVector;

                    //std::cout << springs[i].lengthEnd.x << std::endl; 
                    
                    //std::cout << "ok" << std::endl;

                    //Spring spring; 
                    //Vector2f deltaStart, deltaEnd = spring.changeLength(springs[i]);

                    /*std::cout << deltaStart.x << std::endl;
                    std::cout << deltaStart.y << std::endl;
                    std::cout << deltaEnd.x << std::endl;
                    std::cout << deltaEnd.y << std::endl;*/

                    Vector2f deltaStart = springs[i].lengthStart - springs[i].length0Start;
                    Vector2f deltaEnd = springs[i].lengthEnd - springs[i].length0End;

                    balls[i].acceleration = balls[i].acceleration + deltaStart  * 2 *springs[i].stiffness / balls[i].weight;
                    balls[j].acceleration = balls[j].acceleration + deltaEnd * 2 * springs[i].stiffness / balls[i].weight;
                }
            }
        }
        window.display();
    }
    return 0;
}
