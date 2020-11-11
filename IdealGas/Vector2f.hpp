#include "cmath"

class Vector2f
{
    public:
        float x;
        float y;
    
        
    Vector2f Vector(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2f operator+ (Vector2f v)
    {
        return Vector(x + v.x, y + v.y);
    }

    Vector2f operator- (Vector2f v)
    {
        return Vector(x - v.x, y - v.y);
    }

    Vector2f operator* (float N)
    {
        return Vector(x * N, y * N);
    }

    Vector2f operator/ (float N)
    {
        return Vector(x / N, y / N);
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
        return Vector(x / length(v), y / length(v));
    }
};




