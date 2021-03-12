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

    public:
        Sphere()
        {
        }
        
        Sphere(Vector2f local, Vector2f velocity, sf::Color color, int radius, float weight)
        {
            this->local = local;
            this->velocity = velocity;
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

        bool isCollidedTwoSphere(Sphere sphere)
        {   
            Vector2f detlaX = local - sphere.local;
                      
            if (detlaX.length() <= 2 * radius)
            {
                return true;
            }
            return false;
        }

        void resolveCollision(Sphere *sphere, const float DT)
        {
            Vector2f delta = {sphere->local.x - local.x, sphere->local.y - local.y};
            float alpha = (sphere->local.x - local.x)/(sphere->local.y - local.y);
            
            sphere->local.x = sphere->local.x + (2 * radius - delta.length()) * cos(atan(alpha));
            sphere->local.y = sphere->local.y + (2 * radius - delta.length()) * sin(atan(alpha));
           
            Vector2f Vc = (velocity * weight + sphere->velocity * sphere->weight) / (weight + sphere->weight);
            
            velocity = Vc * 2 - velocity;
            sphere->velocity = Vc * 2- sphere->velocity;
        }
};
