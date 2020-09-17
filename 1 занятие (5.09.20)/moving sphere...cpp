#include "TXLib.h"
#include "iostream"
using namespace std;
#include "cmath"


void drawSphere(int x, int y, int R, int N, int red, int green, int blue )
{
    COLORREF color1 = txGetColor();
    COLORREF color2 = txGetFillColor();

    for(int i = 0; i < N; i++)
        {
            txSetFillColor(RGB(i * red / N, i * green / N, i * blue / N));
            txSetColor(RGB(i * red / N, i * green / N, i * blue / N));
            txCircle(x, y, R - R * i / N);
        }

    txSetColor(color1);
    txSetFillColor(color2);
}


void moveSphere(int *x, int *y, int Vx, int Vy, const float dt)
{
    *x = *x + Vx * dt;
    *y = *y + Vy * dt;
}


void checkCollisionSphere(int x, int y, int Radius, float *Vx, float *Vy)
{
    if ((x >= 1300 - Radius) || (x <= Radius))
        {
            *Vx = -*Vx;
        }

    if ((y >= 700 - Radius) || (y <= Radius))
        {
            *Vy = -*Vy;
        }
}


bool isCollidedTwoSphere(int x1, int y1, int x2, int y2, int Radius)
    {
    if (sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) <= 2 * Radius)
        {
        return true;
        }
    return false;
    }


void ifCollision(bool collisionResult, float *Vx_run, float *Vy_run,
                float *Vx_walk, float *Vy_walk, float weight_run, float weight_walk)
{
    float Vcx = ((weight_run * (*Vx_run) + weight_walk * (*Vx_walk)) / (weight_run + weight_walk));
    float Vcy = ((weight_run * (*Vy_run) + weight_walk * (*Vy_walk)) / (weight_run + weight_walk));
    if (collisionResult)
    {
        *Vx_run = 2 * Vcx - (*Vx_run);
        *Vy_run = 2 * Vcy - (*Vy_run);
        *Vx_walk = 2 * Vcx - (*Vx_walk);
        *Vy_walk = 2 * Vcy - (*Vy_walk);
    }
}


int main()
{
    const float dt = 1;

    int Radius = 35;
    int N = 100;

    float weight_run = 500;
    float weight_walk = 200;

    int x_run = 500;
    int y_run = 200;
    int x_catch = 300;
    int y_catch = 300;

    int x_walk1 = 260;
    int y_walk1 = 140;
    int x_walk2 = 520;
    int y_walk2 = 280;
    int x_walk3 = 780;
    int y_walk3 = 600;


    float Vx_run = 15;
    float Vy_run = 15;

    float Vx_walk1 = 20;
    float Vy_walk1 = 20;
    float Vx_walk2 = 40;
    float Vy_walk2 = 40;
    float Vx_walk3 = 30;
    float Vy_walk3 = 30;


    txCreateWindow(1300, 700);

    txMessageBox("The goal of the game is to collide with the RED ball without hitting the GREEN ones.", "Rules");
    txMessageBox("Click in the upper left corner to start the game!", "Start");

    while (true)
    {
        txClear();

        if (txMouseButtons() == 1)
        {
            txBegin();
            drawSphere(x_run, y_run, Radius, N, 255, 0, 0 );

            drawSphere(x_walk1, y_walk1, Radius, N, 0, 255, 0 );
            drawSphere(x_walk2, y_walk2, Radius, N, 0, 255, 0 );
            drawSphere(x_walk3, y_walk3, Radius, N, 0, 255, 0 );


            checkCollisionSphere(x_run, y_run, Radius, &Vx_run, &Vy_run);
            checkCollisionSphere(x_walk1, y_walk1, Radius, &Vx_walk1, &Vy_walk1);
            checkCollisionSphere(x_walk2, y_walk2, Radius, &Vx_walk2, &Vy_walk2);
            checkCollisionSphere(x_walk3, y_walk3, Radius, &Vx_walk3, &Vy_walk3);


            drawSphere(txMouseX(), txMouseY(), Radius, N, 0, 0, 128);

            bool collisionResult_win = isCollidedTwoSphere(x_run, y_run, txMouseX(), txMouseY(), Radius);

            if (collisionResult_win)
            {
                txMessageBox("WIN", "Message");
                break;
            }

            bool collisionResult_fail1 = isCollidedTwoSphere(x_walk1, y_walk1, txMouseX(), txMouseY(), Radius);
            bool collisionResult_fail2 = isCollidedTwoSphere(x_walk2, y_walk2, txMouseX(), txMouseY(), Radius);
            bool collisionResult_fail3 = isCollidedTwoSphere(x_walk3, y_walk3, txMouseX(), txMouseY(), Radius);


            if ((collisionResult_fail1) || (collisionResult_fail2) || (collisionResult_fail3))
            {
                txMessageBox("FAIL", "Message");
                break;
            }

            bool collisionResult_walk1 = isCollidedTwoSphere(x_run, y_run, x_walk1, y_walk1, Radius);
            bool collisionResult_walk2 = isCollidedTwoSphere(x_run, y_run, x_walk2, y_walk2, Radius);
            bool collisionResult_walk3 = isCollidedTwoSphere(x_run, y_run, x_walk3, y_walk3, Radius);

            ifCollision(collisionResult_walk1, &Vx_run, &Vy_run, &Vx_walk1, &Vy_walk1, weight_run, weight_walk);
            ifCollision(collisionResult_walk2, &Vx_run, &Vy_run, &Vx_walk2, &Vy_walk2, weight_run, weight_walk);
            ifCollision(collisionResult_walk3, &Vx_run, &Vy_run, &Vx_walk3, &Vy_walk3, weight_run, weight_walk);


            bool collisionResult_walk1_2 = isCollidedTwoSphere(x_walk1, y_walk1, x_walk2, y_walk2, Radius);
            bool collisionResult_walk1_3 = isCollidedTwoSphere(x_walk1, y_walk1, x_walk3, y_walk3, Radius);
            bool collisionResult_walk2_3 = isCollidedTwoSphere(x_walk2, y_walk2, x_walk3, y_walk3, Radius);

            ifCollision(collisionResult_walk1_2, &Vx_walk1, &Vy_walk1, &Vx_walk2, &Vy_walk2, weight_run, weight_walk);
            ifCollision(collisionResult_walk1_3, &Vx_walk1, &Vy_walk1, &Vx_walk3, &Vy_walk3, weight_run, weight_walk);
            ifCollision(collisionResult_walk2_3, &Vx_walk2, &Vy_walk2, &Vx_walk3, &Vy_walk3, weight_run, weight_walk);


            moveSphere(&x_run, &y_run, Vx_run, Vy_run, dt);
            moveSphere(&x_walk1, &y_walk1, Vx_walk1, Vy_walk1, dt);
            moveSphere(&x_walk2, &y_walk2, Vx_walk2, Vy_walk2, dt);
            moveSphere(&x_walk3, &y_walk3, Vx_walk3, Vy_walk3, dt);



            txEnd();

        }


    }
    return 0;
}
