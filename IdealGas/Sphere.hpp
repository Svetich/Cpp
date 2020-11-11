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

        Sphere sphere(Vector2f local, Vector2f velocity, sf::Color color, int radius, float weight)
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


        /*bool isCollidedTwoSphere(Sphere sphere1, Sphere sphere2)
        {   
            Vector2f detlaX = sphere1.local - sphere2.local;
            
            Vector2f vector;
            
            if (vector.length(detlaX) <= 2 * sphere1.radius)
            {
                return true;
            }
            return false;
        }*/


        /*void resolveCollision(Sphere* sphere1, Sphere* sphere2, const float DT)
        {
            Vector2f Vc = (sphere1->velocity * sphere1->weight + sphere2->velocity * sphere2->weight) / (sphere1->weight + sphere2->weight);
            

            sphere1->velocity = Vc * 2- sphere1->velocity;
            sphere2->velocity = Vc * 2- sphere2->velocity;
        }*/
};
