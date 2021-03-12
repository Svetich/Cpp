#include <SFML/Graphics.hpp>
#include "Spring.hpp"

class Sphere
{
    public:
        Vector2f local;
        Vector2f velocity;
        Vector2f acceleration;

        sf::Color color;

        float radius;

        float weight;

    public:
        Sphere()
        {
        }
        
        Sphere(Vector2f local, Vector2f velocity, Vector2f acceleration, sf::Color color, float radius, float weight)
        {
            this->local = local;
            this->velocity = velocity;
            this->acceleration = acceleration;
            this->color = color;
            this->radius = radius;
            this->weight = weight;
        }

        void drawSphere(sf::RenderWindow* window)
        {
            sf::CircleShape shape(radius, 10);

            shape.setFillColor(color);
            shape.setPosition(local.x, local.y);
            window->draw(shape);
        }

        void moveSphere(const float DT)
        {
            local = local + velocity * DT;       
        }

        void checkCollisionSphere(int width, int height)
        {
            if (local.x + radius >= width - radius)
            {
                velocity.x = -velocity.x;
                local.x = width - 2 * radius;
            }
            
            if (local.x + radius <= radius)
            {
                velocity.x = -velocity.x;
                local.x = 2 * radius;
            }

            if (local.y + radius >= height - radius)
            {
                velocity.y = -velocity.y;
                local.y = height - 2 * radius;
            }
            
            if (local.y + radius <= radius)
            {
                velocity.y = -velocity.y;
                local.y = 2 * radius;
            }
        }

        void calculationAcceleration(Spring *spring)
        {
            spring->lengthStart = local + Vector2f(radius, radius);
            spring->lengthEnd = local + Vector2f(radius, radius);

            Vector2f deltaStart = spring->lengthStart - spring->length0Start;
            Vector2f deltaEnd = spring->lengthEnd - spring->length0End;

            acceleration = acceleration + (deltaEnd - deltaStart) * 2 * spring->stiffness / weight;            
        }
};