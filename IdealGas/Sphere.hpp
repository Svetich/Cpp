#include <SFML/Graphics.hpp>
#include <cmath>

class Sphere
{
    public:
        Vector2f local;
        Vector2f velocity;

        sf::Color color;

        int radius;

        float weight;

    void drawSphere(sf::RenderWindow* window, Sphere sphere)
    {
        sf::CircleShape shape(sphere.radius, 10);

        shape.setFillColor(sphere.color);
        shape.setPosition(sphere.local.x, sphere.local.y);
        window->draw(shape);
    }

    void moveSphere(Sphere* sphere, const float DT)
    {
        sphere->local = sphere->local + sphere->velocity * DT;       
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


    bool isCollidedTwoSphere(Sphere sphere1, Sphere sphere2)
    {   
        Vector2f detlaX = sphere1.local - sphere2.local;
        if (length(detlaX) <= 2 * sphere1.radius)
        {
            return true;
        }
        return false;
    }


    void resolveCollision(Sphere* sphere1, Sphere* sphere2)
    {
        Vector2f Vc = ((sphere1->weight * (sphere1->velocity) + sphere2->weight * (sphere2->velocity)) / (sphere1->weight + sphere2->weight));
        
        sphere1->velocity = 2 * Vc - sphere1->velocity;
        sphere2->velocity = 2 * Vc - sphere2->velocity;
    }
};
