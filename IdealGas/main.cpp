#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdio>
#include <ctime>
#include "Vector2f.hpp"
#include "Sphere.hpp"


int randint(int randMin, int randMax)
{
    return randMin + (rand() % (randMax - randMin));
}

float uniform()
{
    return ((float)rand()) / ((float)RAND_MAX);
}

float normal()
{
    float u = uniform();
    float v = uniform();

    return sqrt(-2. * log(u)) * cos(2 * 3.14159 * v);
}

int main()
{
    srand(time(NULL));

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 700;

    const float DT = 0.01;

    const int NUMBER = 100;

    Sphere particles[NUMBER];

    for (int i = 0; i < NUMBER; i++)
    {
        Vector2f tmpLocal = { 350 + (60 * i) % (60 * 10), 150 + (i / 10) * 40 };    
        Vector2f tmpVelocity = { normal() * 10.f, normal() * 10.f };
        
        sf::Color tmpColor = sf::Color::Blue;

        Sphere tmpSphere = { tmpLocal, tmpVelocity, tmpColor, 10, 50 };

        particles[i] = tmpSphere;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "The Model of Ideal Gas");

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

        for (int i = 0; i < NUMBER; i++)
        {
            particles[i].drawSphere(&window);
        }

        for (int i = 0; i < NUMBER; i++)
        {
            particles[i].checkCollisionSphere(WINDOW_WIDTH, WINDOW_HEIGHT);
        }

        for (int i = 0; i < NUMBER; i++)
        {
            for (int j = i + 1; j < NUMBER; j++)
            {   
                Sphere sphere;
                if (particles[i].isCollidedTwoSphere(particles[j]))
                {
                    particles[i].resolveCollision(&particles[j], DT);
                }
            }
        }

        for (int i = 0; i < NUMBER; i++)
        {
            particles[i].moveSphere(DT);
        }

        window.display();
    }
    return 0;
}