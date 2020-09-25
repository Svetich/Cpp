#include "TXLib.h"
#include "iostream"
#include "cmath"


struct Param_Sphere
{
    int x;
    int y;

    int Vx;
    int Vy;

    float weight;
};


void drawSphere(Param_Sphere sphere, int R, int N, int red, int green, int blue)
{
    COLORREF color1 = txGetColor();
    COLORREF color2 = txGetFillColor();

    for(int i = 0; i < N; i++)
        {
            txSetFillColor(RGB(i * red / N, i * green / N, i * blue / N));
            txSetColor(RGB(i * red / N, i * green / N, i * blue / N));
            txCircle(sphere.x, sphere.y, R - R * i / N);
        }

    txSetColor(color1);
    txSetFillColor(color2);
}


void moveSphere(Param_Sphere *sphere, const int dt)
{
    (*sphere).x = (*sphere).x + (*sphere).Vx * dt;
    (*sphere).y = (*sphere).y + (*sphere).Vy * dt;
}


void checkCollisionSphere(Param_Sphere *sphere, int Radius)
{
    if (((*sphere).x >= 1300 - Radius) || ((*sphere).x <= Radius))
        {
            (*sphere).Vx = - (*sphere).Vx;
        }

    if (((*sphere).y >= 700 - Radius) || ((*sphere).y <= Radius))
        {
            (*sphere).Vy = - (*sphere).Vy;
        }
}


bool isCollidedTwoSphere(Param_Sphere sphere1, Param_Sphere sphere2, int Radius)
    {
    if (sqrt(pow((sphere1.x - sphere2.x), 2) + pow((sphere1.y - sphere2.y), 2)) <= 2 * Radius)
        {
        return true;
        }
    return false;
    }


void ifCollision(Param_Sphere *sphere1, Param_Sphere *sphere2)
{
    float Vcx = (((*sphere1).weight * ((*sphere1).Vx) + (*sphere2).weight * ((*sphere2).Vx)) / ((*sphere1).weight + (*sphere2).weight));
    float Vcy = (((*sphere1).weight * ((*sphere1).Vy) + (*sphere2).weight * ((*sphere2).Vy)) / ((*sphere1).weight + (*sphere2).weight));

    (*sphere1).Vx = 2 * Vcx - (*sphere1).Vx;
    (*sphere1).Vy = 2 * Vcy - (*sphere1).Vy;
    (*sphere2).Vx = 2 * Vcx - (*sphere2).Vx;
    (*sphere2).Vy = 2 * Vcy - (*sphere2).Vy;
}



int main()
{
    const int dt = 1;

    int Radius = 35;

    int N = 100;

    int x_catch = 300;
    int y_catch = 300;

    Param_Sphere sphere_run = {500, 200, 15, 15, 500};
    Param_Sphere sphere_walk1 = {260, 140, 20, 20, 200};
    Param_Sphere sphere_walk2 = {520, 280, 40, 40, 200};
    Param_Sphere sphere_walk3 = {780, 600, 30, 30, 200};



    txCreateWindow(1300, 700);

    txMessageBox("The goal of the game is to collide with the RED ball without hitting the GREEN ones.", "Rules");
    txMessageBox("Click in the upper left corner to start the game!", "Start");

    while (true)
    {
        txClear();

        Param_Sphere sphere_mouse = {txMouseX(), txMouseY(), 15, 15, 200};

        if (txMouseButtons() == 1)
        {
            txBegin();
            drawSphere(sphere_run, Radius, N, 255, 0, 0 );

            drawSphere(sphere_walk1, Radius, N, 0, 255, 0 );
            drawSphere(sphere_walk2, Radius, N, 0, 255, 0 );
            drawSphere(sphere_walk3, Radius, N, 0, 255, 0 );


            checkCollisionSphere(&sphere_run, Radius);
            checkCollisionSphere(&sphere_walk1, Radius);
            checkCollisionSphere(&sphere_walk2, Radius);
            checkCollisionSphere(&sphere_walk3, Radius);


            drawSphere(sphere_mouse, Radius, N, 0, 0, 128);

            bool collisionResult_win = isCollidedTwoSphere(sphere_run, sphere_mouse, Radius);


            if (collisionResult_win)
            {
                txMessageBox("WIN", "Message");
                break;
            }


            bool collisionResult_fail1 = isCollidedTwoSphere(sphere_walk1, sphere_mouse, Radius);
            bool collisionResult_fail2 = isCollidedTwoSphere(sphere_walk2, sphere_mouse, Radius);
            bool collisionResult_fail3 = isCollidedTwoSphere(sphere_walk3, sphere_mouse, Radius);



            if ((collisionResult_fail1) || (collisionResult_fail2) || (collisionResult_fail3))
            {

                txMessageBox("FAIL", "Message");
                break;
            }

            bool collisionResult_walk1 = isCollidedTwoSphere(sphere_run, sphere_walk1, Radius);
            bool collisionResult_walk2 = isCollidedTwoSphere(sphere_run, sphere_walk2, Radius);
            bool collisionResult_walk3 = isCollidedTwoSphere(sphere_run, sphere_walk3, Radius);


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


            bool collisionResult_walk1_2 = isCollidedTwoSphere(sphere_walk1, sphere_walk2, Radius);
            bool collisionResult_walk1_3 = isCollidedTwoSphere(sphere_walk1, sphere_walk3, Radius);
            bool collisionResult_walk2_3 = isCollidedTwoSphere(sphere_walk2, sphere_walk3, Radius);


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
