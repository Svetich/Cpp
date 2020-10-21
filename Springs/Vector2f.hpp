#include "cmath"

class Vector2f
{
    public:
        float x;
        float y;
    
        
    Vector2f Vector2f_ctor (float x, float y)
    {
        Vector2f v = {x, y};
        return v;
    }

    Vector2f operator+ (Vector2f v)
    {
        return Vector2f_ctor(x + v.x, y + v.y);
    }

    Vector2f operator- (Vector2f v)
    {
        return Vector2f_ctor(x - v.x, y - v.y);
    }

    Vector2f operator* (float N)
    {
        return Vector2f_ctor(x * N, y * N);
    }

    Vector2f operator/ (float N)
    {
        return Vector2f_ctor(x / N, y / N);
    }

    float operator* (Vector2f v)
    {
        return (x * v.x + y * v.y);
    }

    float length(Vector2f v)
    {
        return sqrt(pow(v.x, 2) + pow(v.y, 2));
    }

    Vector2f normalize(Vector2f v)
    {
        return Vector2f_ctor(x / length(v), y / length(v));
    }
};




