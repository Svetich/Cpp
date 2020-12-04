#include "cmath"

class Vector2f
{
    public:
        float x;
        float y;
    
    public:    
        Vector2f()
        {
        }
        
        Vector2f(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        Vector2f operator+ (Vector2f v)
        {
            return Vector2f(x + v.x, this->y + v.y);
        }

        Vector2f operator- (Vector2f v)
        {
            return Vector2f(x - v.x, y - v.y);
        }

        Vector2f operator* (float N)
        {
            return Vector2f(x * N, y * N);
        }

        Vector2f operator/ (float N)
        {
            return Vector2f(x / N, y / N);
        }

        float operator* (Vector2f v)
        {
            return (x * v.x + y * v.y);
        }

        float length()
        {
            return sqrt(pow(x, 2) + pow(y, 2));
        }

        Vector2f normalize()
        {
            return Vector2f(x / length(), y / length());
        }
};




