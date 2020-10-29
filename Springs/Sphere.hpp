#include <SFML/Graphics.hpp>

class Sphere
{
    public:
        Vector2f local;
        Vector2f velocity;
        Vector2f acceleration;

        sf::Color color;

        float radius;

        float weight; 
        
        void moveSphere(Sphere* sphere, const float DT)
        {   
            sphere->local = sphere->local + sphere->velocity * DT - sphere->acceleration * pow(DT, 2) / 2;
            sphere->velocity = sphere->velocity + sphere->acceleration * DT;
        }
        
        void checkCollisionSphere(Sphere* sphere, int width, int height)
        {
            if ((sphere->local.x + sphere->radius >= width - sphere->radius) || (sphere->local.x + sphere->radius <= sphere->radius))
            {
                sphere->velocity.x = -sphere->velocity.x;
            }

            if ((sphere->local.y + sphere->radius >= height - sphere->radius) || (sphere->local.y + sphere->radius <= sphere->radius))
            {
                sphere->velocity.y = -sphere->velocity.y;
            }
        }

        void drawSphere(Sphere sphere, sf::RenderWindow* window)
        {
            sf::CircleShape shape(sphere.radius, 10);

            //shape.sf::Transformable::setOrigin (sphere.local.x, sphere.local.y);

            shape.setFillColor(sphere.color);
            shape.setPosition(sphere.local.x, sphere.local.y);
            window->draw(shape);
        }
};