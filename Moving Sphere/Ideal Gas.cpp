#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>

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

struct Vector
{
    float x;
    float y;
};


struct Sphere
{
    Vector local;
    Vector velocity;

    sf::Color color;

    int radius;

    float weight;
};


void drawSphere(sf::RenderWindow* window, Sphere sphere)
{
    sf::CircleShape shape(sphere.radius, 10);

    shape.setFillColor(sphere.color);
    shape.setPosition(sphere.local.x, sphere.local.y);
    window->draw(shape);
}


void moveSphere(Sphere* sphere, const float dt)
{
    sphere->local.x = sphere->local.x + sphere->velocity.x * dt;
    sphere->local.y = sphere->local.y + sphere->velocity.y * dt;
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
    if (sqrt(pow((sphere1.local.x - sphere2.local.x), 2) + pow((sphere1.local.y - sphere2.local.y), 2)) <= 2 * sphere1.radius)
    {
        return true;
    }
    return false;
}


void resolveCollision(Sphere* sphere1, Sphere* sphere2)
{
    float Vcx = ((sphere1->weight * (sphere1->velocity.x) + sphere2->weight * (sphere2->velocity.x)) / (sphere1->weight + sphere2->weight));
    float Vcy = ((sphere1->weight * (sphere1->velocity.y) + sphere2->weight * (sphere2->velocity.y)) / (sphere1->weight + sphere2->weight));

    sphere1->velocity.x = 2 * Vcx - sphere1->velocity.x;
    sphere1->velocity.y = 2 * Vcy - sphere1->velocity.y;
    sphere2->velocity.x = 2 * Vcx - sphere2->velocity.x;
    sphere2->velocity.y = 2 * Vcy - sphere2->velocity.y;
}



int main()
{
    srand(time(NULL));

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;

    const float DT = 0.01;

    const int NUMBER = 100;

    Sphere particles[NUMBER];

    for (int i = 0; i < NUMBER; i++)
    {
        Vector tmpLocal = { 300 + 50 + (60 * i) % (60 * 10), 300 + 50 + (i / 10) * 40 };    
        Vector tmpVelocity = { normal() * 10.f, normal() * 10.f };
        
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
            drawSphere(&window, particles[i]);
        }

        for (int i = 0; i < NUMBER; i++)
        {
            checkCollisionSphere(&particles[i], WINDOW_WIDTH, WINDOW_HEIGHT);
        }

        for (int i = 0; i < NUMBER; i++)
        {
            for (int j = i + 1; j < NUMBER; j++)
            {
                if (isCollidedTwoSphere(particles[i], particles[j]))
                {
                    resolveCollision(&particles[i], &particles[j]);
                }
            }
        }
        for (int i = 0; i < NUMBER; i++)
        {
            moveSphere(&particles[i], DT);
        }

        window.display();

    }
    return 0;
}