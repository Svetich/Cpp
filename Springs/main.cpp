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

    int Radius = 20;

    Sphere ball1 = {{640, 50}, {0.1, 0}, {0, 0}, sf::Color::Blue, Radius, 50};
    Sphere ball2 = {{760, 50}, {-0.2, 0}, {0, 0}, sf::Color::Blue, Radius, 50};

    Sphere balls[NUMBALLS] = {ball1, ball2};

    Spring springs[NUMSPRINGS];

    int table[NUMBALLS][NUMBALLS] = {{0, 1}, {1, 0}};

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Springs");


    for (int i = 0; i < NUMBALLS; i++)
    {
        for (int j = i + 1; j < NUMBALLS; j++)
        {
            Vector2f tmpLengthStart = balls[i].local;
            Vector2f tmpLengthEnd = balls[j].local;

            std::cout << tmpLengthEnd.x << std::endl;
        
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
            Sphere sphere;
            sphere.drawSphere(balls[i], &window); 

            //sphere.moveSphere(&balls[i], DT);    
        }

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
            sphere.checkCollisionSphere(&balls[i], WINDOW_WIDTH, WINDOW_HEIGHT);

            sphere.moveSphere(&balls[i], DT);
        }
;
        /*for (int i = 0; i < NUMBALLS; i++)
        {
            for (int j = i + 1; j < NUMBALLS; j++)
            {
                if (table[i][j] == 1)
                {
                    springs[i].lengthStart = balls[i].local;
                    springs[i].lengthEnd = balls[j].local;

                    Spring spring; 

                    //Vector2f detla = spring.changeLength(springs[i]);
                }
            }
        }*/
        

        for (int i = 0; i < NUMBALLS; i++)
        {
            for (int j = i + 1; j < NUMBALLS; j++)
            {
                if (table[i][j] == 1)
                {
                    springs[i].lengthStart = balls[j].local;
                    springs[i].lengthEnd = balls[i].local;

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

                    //Vector2f vector;
                    
                    /*if (balls[i].velocity.x == 0)
                    {
                        balls[i].acceleration.x = balls[i].acceleration.x * (-1);
                        std::cout << "ix" << std::endl;

                    }

                    if (balls[i].velocity.y == 0)
                    {
                        balls[i].acceleration.y = balls[i].acceleration.y * (-1);
                        std::cout << "iy" << std::endl;
                    }

                    if (balls[j].velocity.x == 0)
                    {
                        balls[j].acceleration.x = balls[j].acceleration.x * (-1);
                        std::cout << "jx" << std::endl;
                    }

                    if (balls[j].velocity.y == 0)
                    {
                        balls[j].acceleration.y = balls[j].acceleration.y * (-1);
                        std::cout << "jy" << std::endl;
                    }*/
                }
            }
        }
        window.display();
    }
    return 0;
}
