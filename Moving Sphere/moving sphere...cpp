#include "TXLib.h"
#include "iostream"
#include "cmath"

struct Vector
{
    int x;
    int y;
};


struct Param_Sphere
{
    Vector local;
    Vector speed;

    int Radius;

    float weight;
};


void drawSphere(Param_Sphere sphere, int N, int red, int green, int blue)
{
    COLORREF color1 = txGetColor();
    COLORREF color2 = txGetFillColor();

    for(int i = 0; i < N; i++)
        {
            txSetFillColor(RGB(i * red / N, i * green / N, i * blue / N));
            txSetColor(RGB(i * red / N, i * green / N, i * blue / N));
            txCircle(sphere.local.x, sphere.local.y, sphere.Radius - sphere.Radius * i / N);
        }

    txSetColor(color1);
    txSetFillColor(color2);
}


void moveSphere(Param_Sphere *sphere, const int dt)
{
    (*sphere).local.x = (*sphere).local.x + (*sphere).speed.x * dt;
    (*sphere).local.y = (*sphere).local.y + (*sphere).speed.y * dt;
}


void checkCollisionSphere(Param_Sphere *sphere)
{
    if (((*sphere).local.x >= 1300 - (*sphere).Radius) || ((*sphere).local.x <= (*sphere).Radius))
        {
            (*sphere).speed.x = - (*sphere).speed.x;
        }

    if (((*sphere).local.y >= 700 - (*sphere).Radius) || ((*sphere).local.y <= (*sphere).Radius))
        {
            (*sphere).speed.y = - (*sphere).speed.y;
        }
}


bool isCollidedTwoSphere(Param_Sphere sphere1, Param_Sphere sphere2)
    {
    if (sqrt(pow((sphere1.local.x - sphere2.local.x), 2) + pow((sphere1.local.y - sphere2.local.y), 2)) <= 2 * sphere1.Radius)
        {
        return true;
        }
    return false;
    }


void ifCollision(Param_Sphere *sphere1, Param_Sphere *sphere2)
{
    float Vcx = (((*sphere1).weight * ((*sphere1).speed.x) + (*sphere2).weight * ((*sphere2).speed.x)) / ((*sphere1).weight + (*sphere2).weight));
    float Vcy = (((*sphere1).weight * ((*sphere1).speed.y) + (*sphere2).weight * ((*sphere2).speed.y)) / ((*sphere1).weight + (*sphere2).weight));

    (*sphere1).speed.x = 2 * Vcx - (*sphere1).speed.x;
    (*sphere1).speed.y = 2 * Vcy - (*sphere1).speed.y;
    (*sphere2).speed.x = 2 * Vcx - (*sphere2).speed.x;
    (*sphere2).speed.y = 2 * Vcy - (*sphere2).speed.y;
}



int main()
{
    const int dt = 1;

    int N = 100;

 //   int x_catch = 300;
 //   int y_catch = 300;

    Param_Sphere sphere_run = {500, 200, 15, 15, 35, 500};
    Param_Sphere sphere_walk1 = {260, 140, 20, 20, 35, 200};
    Param_Sphere sphere_walk2 = {520, 280, 40, 40, 35, 200};
    Param_Sphere sphere_walk3 = {780, 600, 30, 30, 35, 200};



    txCreateWindow(1300, 700);

    txMessageBox("The goal of the game is to collide with the RED ball without hitting the GREEN ones.", "Rules");
    txMessageBox("Click in the upper left corner to start the game!", "Start");

    while (true)
    {
        txClear();

        Param_Sphere sphere_mouse = {txMouseX(), txMouseY(), 15, 15, 35, 200};

        if (txMouseButtons() == 1)
        {
            txBegin();
            drawSphere(sphere_run, N, 255, 0, 0 );

            drawSphere(sphere_walk1, N, 0, 255, 0 );
            drawSphere(sphere_walk2, N, 0, 255, 0 );
            drawSphere(sphere_walk3, N, 0, 255, 0 );


            checkCollisionSphere(&sphere_run);
            checkCollisionSphere(&sphere_walk1);
            checkCollisionSphere(&sphere_walk2);
            checkCollisionSphere(&sphere_walk3);


            drawSphere(sphere_mouse, N, 0, 0, 128);

            bool collisionResult_win = isCollidedTwoSphere(sphere_run, sphere_mouse);


            if (collisionResult_win)
            {
                txMessageBox("WIN", "Message");
                break;
            }


            bool collisionResult_fail1 = isCollidedTwoSphere(sphere_walk1, sphere_mouse);
            bool collisionResult_fail2 = isCollidedTwoSphere(sphere_walk2, sphere_mouse);
            bool collisionResult_fail3 = isCollidedTwoSphere(sphere_walk3, sphere_mouse);



            if ((collisionResult_fail1) || (collisionResult_fail2) || (collisionResult_fail3))
            {

                txMessageBox("FAIL", "Message");
                break;
            }

            bool collisionResult_walk1 = isCollidedTwoSphere(sphere_run, sphere_walk1);
            bool collisionResult_walk2 = isCollidedTwoSphere(sphere_run, sphere_walk2);
            bool collisionResult_walk3 = isCollidedTwoSphere(sphere_run, sphere_walk3);


            if (collisionResult_walk1)
            {
                ifCollision(&sphere_run, &sphere_walk1);
            }

            if (collisionResult_walk2)
            {
                ifCollision(&sphere_run, &sphere_walk2);
            }

            if (collisionResult_walk3)
            {
                ifCollision(&sphere_run, &sphere_walk3);
            }


            bool collisionResult_walk1_2 = isCollidedTwoSphere(sphere_walk1, sphere_walk2);
            bool collisionResult_walk1_3 = isCollidedTwoSphere(sphere_walk1, sphere_walk3);
            bool collisionResult_walk2_3 = isCollidedTwoSphere(sphere_walk2, sphere_walk3);


            if (collisionResult_walk1_2)
            {
                ifCollision(&sphere_walk1, &sphere_walk2);
            }

            if (collisionResult_walk1_3)
            {
                ifCollision(&sphere_walk1, &sphere_walk3);
            }

            if (collisionResult_walk2_3)
            {
                ifCollision(&sphere_walk2, &sphere_walk3);
            }


            moveSphere(&sphere_run, dt);
            moveSphere(&sphere_walk1, dt);
            moveSphere(&sphere_walk2, dt);
            moveSphere(&sphere_walk3, dt);


            txEnd();

        }


    }
    return 0;
}
