#include "TXLib.h"
#include "iostream"
#include "cmath"


struct Vector
{
    int x;
    int y;
};

struct Color
{
    int red;
    int green;
    int blue;
};

struct Sphere
{
    Vector local;
    Vector velocity;

    Color color;

    int radius;

    float weight;
};


void drawSphere(Sphere sphere, int definition)
{
    COLORREF color1 = txGetColor();
    COLORREF color2 = txGetFillColor();

    for(int i = 0; i < definition; i++)
    {
        txSetFillColor(RGB(i * sphere.color.red / definition, i * sphere.color.green / definition, i * sphere.color.blue / definition));
        txSetColor(RGB(i * sphere.color.red / definition, i * sphere.color.green / definition, i * sphere.color.blue / definition));
        txCircle(sphere.local.x, sphere.local.y, sphere.radius - sphere.radius * i / definition);
    }

    txSetColor(color1);
    txSetFillColor(color2);
}


void moveSphere(Sphere *sphere, const int dt)
{
    sphere -> local.x = sphere -> local.x + sphere -> velocity.x * dt;
    sphere -> local.y = sphere -> local.y + sphere -> velocity.y * dt;
}


void checkCollisionSphere(Sphere *sphere)
{
    if ((sphere -> local.x >= 1300 - sphere -> radius) || (sphere -> local.x <= sphere -> radius))
    {
        sphere -> velocity.x = - sphere -> velocity.x;
        sphere -> local.x = sphere -> local.x + abs(sphere -> local.x - sphere -> radius);
    }

    if ((sphere -> local.y >= 700 - sphere -> radius) || (sphere -> local.y <= sphere -> radius))
    {
        sphere -> velocity.y = - sphere -> velocity.y;
        sphere -> local.y = sphere -> local.y + abs(sphere -> local.y - sphere -> radius);
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


void resolveCollision(Sphere *sphere1, Sphere *sphere2)
{
    float Vcx = ((sphere1 -> weight * (sphere1 -> velocity.x) + sphere2 -> weight * (sphere2 -> velocity.x)) / (sphere1 -> weight + sphere2 -> weight));
    float Vcy = ((sphere1 -> weight * (sphere1 -> velocity.y) + sphere2 -> weight * (sphere2 -> velocity.y)) / (sphere1 -> weight + sphere2 -> weight));

    sphere1 -> velocity.x = 2 * Vcx - sphere1 -> velocity.x;
    sphere1 -> velocity.y = 2 * Vcy - sphere1 -> velocity.y;
    sphere2 -> velocity.x = 2 * Vcx - sphere2 -> velocity.x;
    sphere2 -> velocity.y = 2 * Vcy - sphere2 -> velocity.y;
}


int main()
{
    const int dt = 1;

    int definition = 100;

    Sphere sphere_run = {500, 200, 15, 15, 255, 0, 0, 35, 500};
    Sphere sphere_walk1 = {260, 140, 20, 20, 0, 255, 0, 35, 200};
    Sphere sphere_walk2 = {520, 280, 40, 40, 0, 255, 0, 35, 200};
    Sphere sphere_walk3 = {780, 600, 30, 30, 0, 255, 0, 35, 200};

    txCreateWindow(1300, 700);

    txMessageBox("The goal of the game is to collide with the RED ball without hitting the GREEN ones.", "Rules");
    txMessageBox("Click in the upper left corner to start the game!", "Start");

    while (true)
    {
        txClear();

        Sphere sphere_mouse = {txMouseX(), txMouseY(), 15, 15, 0, 0, 128, 35, 200};

        if (txMouseButtons() == 1)
        {
            txBegin();

            drawSphere(sphere_run, definition);

            drawSphere(sphere_walk1, definition);
            drawSphere(sphere_walk2, definition);
            drawSphere(sphere_walk3, definition);
            drawSphere(sphere_mouse, definition);

            txEnd();

            checkCollisionSphere(&sphere_run);
            checkCollisionSphere(&sphere_walk1);
            checkCollisionSphere(&sphere_walk2);
            checkCollisionSphere(&sphere_walk3);


            if (isCollidedTwoSphere(sphere_run, sphere_mouse))
            {
                txMessageBox("WIN", "Message");
                break;
            }


            if ((isCollidedTwoSphere(sphere_walk1, sphere_mouse)) || (isCollidedTwoSphere(sphere_walk2, sphere_mouse)) || (isCollidedTwoSphere(sphere_walk3, sphere_mouse)))
            {

                txMessageBox("FAIL", "Message");
                break;
            }


            if (isCollidedTwoSphere(sphere_run, sphere_walk1))
            {
                resolveCollision(&sphere_run, &sphere_walk1);
            }

            if (isCollidedTwoSphere(sphere_run, sphere_walk2))
            {
                resolveCollision(&sphere_run, &sphere_walk2);
            }

            if (isCollidedTwoSphere(sphere_run, sphere_walk3))
            {
                resolveCollision(&sphere_run, &sphere_walk3);
            }


            if (isCollidedTwoSphere(sphere_walk1, sphere_walk2))
            {
                resolveCollision(&sphere_walk1, &sphere_walk2);
            }

            if (isCollidedTwoSphere(sphere_walk1, sphere_walk3))
            {
                resolveCollision(&sphere_walk1, &sphere_walk3);
            }

            if (isCollidedTwoSphere(sphere_walk2, sphere_walk3))
            {
                resolveCollision(&sphere_walk2, &sphere_walk3);
            }

            moveSphere(&sphere_run, dt);
            moveSphere(&sphere_walk1, dt);
            moveSphere(&sphere_walk2, dt);
            moveSphere(&sphere_walk3, dt);
        }
    }
    return 0;
}
