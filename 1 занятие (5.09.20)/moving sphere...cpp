#include "TXLib.h"

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



int main()
{
    const float dt = 1;

    int R = 100;
    int N = 1000;
    int x = 100;
    int y = 100;

    int red = 0;
    int green = 0;
    int blue = 128;

    float Vx = 10;
    float Vy = 10;

    txCreateWindow(800, 600);

    while (true)
    {
        txClear();

        txBegin();
        drawSphere(x, y, R, N, 0, 0, 128 );
        txEnd();

        x = x + Vx * dt;
        y = y + Vy * dt;

        if ((x >= 800 - R) || (x <= R))
        {
            Vx = -Vx;
        }
        if ((y >= 600 - R) || (y <= R))
        {

            Vy = -Vy;
        }
    }

    return 0;
}
