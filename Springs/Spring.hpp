#include <SFML/Graphics.hpp>
#include <iostream>

class Spring
{
    public:
        Vector2f length0Start;
        Vector2f length0End;

        Vector2f lengthStart;
        Vector2f lengthEnd;

        float stiffness; 

        sf::Color color;
        
        void drawSpring(Spring spring, sf::RenderWindow* window)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(spring.lengthStart.x, spring.lengthStart.y)),
                sf::Vertex(sf::Vector2f(spring.lengthEnd.x, spring.lengthEnd.y))
            };
            line -> color = color;
            
            window->draw(line, 2, sf::Lines);
        }
        
        
        /*Vector2f changeLength(Spring spring)
        {
            

            std::cout << deltaEnd.x << std::endl;

            return deltaStart, deltaEnd;
        }*/
};