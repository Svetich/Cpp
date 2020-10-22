#include <SFML/Graphics.hpp>
#include "Vector2f.hpp"



class Sphere
{
    public:
        Vector2f local;
        Vector2f velocity;
        Vector2f acceleration;

        sf::Color color;

        int radius;

        float weight; 
        
        void moveSphere(Sphere* sphere, const float DT)
        {
            sphere->local = sphere->local + sphere->velocity * DT + sphere->acceleration * pow(DT, 2) / 2;
            sphere->velocity = sphere->velocity + sphere->acceleration * DT;
        }
        void drawSphere(Sphere sphere, sf::RenderWindow* window)
        {
            sf::CircleShape shape(sphere.radius, 10);

            shape.setFillColor(sphere.color);
            shape.setPosition(sphere.local.x, sphere.local.y);
            window->draw(shape);
        }
};

class Spring
{
    public:
        Vector2f length0Start;
        Vector2f length0End;

        Vector2f lengthStart;
        Vector2f lengthEnd;

        float conctant;

        sf::Color color;

        

//window.draw(line, 2, sf::Lines);
        
        void drawSpring(Spring spring, sf::RenderWindow* window)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(spring.lengthStart.x, spring.lengthStart.y)),
                sf::Vertex(sf::Vector2f(spring.lengthEnd.x, spring.lengthEnd.y))
            };
            window->draw(line, 2, sf::Lines);
        }

        /*void changeLength()
        {

        }*/



};


int main()
{
    srand(time(NULL));

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    const float DT = 0.01;

    const int NUMBALLS = 2;
    const int NUMSPRINGS = 1;

    Sphere balls[NUMBALLS];
    // Spring springs[NUMSPRINGS];

    Spring table[NUMBALLS][NUMBALLS];

    for (int i; i < NUMBALLS; i++)
    {
        Vector2f tmpLocal = {300 + 50 + (60 * i) % (60 * 10, 300 + 50 + (i / 10) * 40)};    
        Vector2f tmpVelocity = {0, 0};
        Vector2f tmpAcceleration = {0, 0};
        
        sf::Color tmpColor = sf::Color::Black;

        Sphere tmpSphere = {tmpLocal, tmpVelocity, tmpAcceleration, tmpColor, 20, 50};

        balls[i] = tmpSphere;
    }
    
   /* for (int i; i < NUMSPRINGS; i++)
    {
        Vector2f tmpLengthSt = {}
    } */

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
        
     
        for (int i = 0; i < NUMBALLS; i++)
        {
            Sphere sphere;
            sphere.drawSphere(balls[i], &window);      
        }


        for (int i = 0; i < NUMBALLS; i++)
        {
            for (int j = 0; j < NUMBALLS; i++)
            {
                Vector2f tmpLengthStart = balls[i].local;
                Vector2f tmpLengthEnd = balls[j].local;

                sf::Color tmpColorSpring = sf::Color::White;

                Spring tmpSpring = {tmpLengthStart, tmpLengthEnd, tmpLengthStart, tmpLengthEnd, 20, tmpColorSpring};

                //table[i][j] = tmpSpring;

                tmpSpring.drawSpring(tmpSpring, &window);
            }
        }


        window.display();


    }
    return 0;
}
