#include <SFML/Graphics.hpp>

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