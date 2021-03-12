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
        
    public:
        Spring()
        {
        }

        Spring(Vector2f length0Start, Vector2f length0End, Vector2f lengthStart, Vector2f lengthEnd, float stiffness, sf::Color color)
        {
            this->length0Start = length0Start;
            this->length0End = length0End;
            this->lengthStart = lengthStart;
            this->lengthEnd = lengthEnd;

            this->stiffness = stiffness;

            this->color = color;
        }

        void drawSpring(sf::RenderWindow* window)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(lengthStart.x, lengthStart.y)),
                sf::Vertex(sf::Vector2f(lengthEnd.x, lengthEnd.y))
            };
            line -> color = color;
            
            window->draw(line, 2, sf::Lines);
        }

};