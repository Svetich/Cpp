#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Vector2f.hpp"
#include "Sphere.hpp"
#include "Spring.hpp"


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

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    const float DT = 0.01;

    const int NUMBALLS = 2;
    const int NUMSPRINGS = 1;

    Sphere balls[NUMBALLS];

    Spring springs[NUMSPRINGS];

    int table[NUMBALLS][NUMBALLS] = {{0, 1}, {1, 0}};

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Springs");

    for (int i = 0; i < NUMBALLS; i++)
        {
            Vector2f tmpLocal = {getRandomNumber(1., 1200.), getRandomNumber(1., 700.)};    
            Vector2f tmpVelocity = {0, 0};
            Vector2f tmpAcceleration = {0, 0};
            
            sf::Color tmpColor = sf::Color::Blue;

            Sphere tmpSphere = {tmpLocal, tmpVelocity, tmpAcceleration, tmpColor, 20, 50};

            balls[i] = tmpSphere;
        }

    for (int i = 0; i < NUMSPRINGS; i++)
    {
        Vector2f tmpLength = {0, 0};
        
        sf::Color tmpColor = sf::Color::White;

        Spring tmpSpring = {tmpLength, tmpLength, tmpLength, tmpLength, 50, tmpColor};

        springs[i] = tmpSpring;
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
        }

        for (int i = 0; i < NUMBALLS; i++)
        {
            for (int j = i; j < NUMBALLS; j++)
            {
                if (table[i][j] == 1)
                {
                    springs[i].length0Start = balls[j].local;
                    springs[i].length0End = balls[j].local;

                    springs[i].lengthStart = balls[j].local;
                    springs[i].lengthEnd = balls[j].local; 
                    
                    Spring spring; 
                    spring.drawSpring(springs[i], &window);
                }
            }
        }
        window.display();
    }
    return 0;
}
