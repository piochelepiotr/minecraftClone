#include "p.h"
#include "math.h"

P::P(int x, int y, int z) :
    x(x),
    y(y),
    z(z)
{

}

bool operator<(P const& p1, P const& p2)
{
    if(p1.x < p2.x)
    {
        return true;
    }
    else if(p1.x == p2.x)
    {
        if(p1.y < p2.y)
        {
            return true;
        }
        else if(p1.y == p2.y)
        {
            if(p1.z < p2.z)
            {
                return true;
            }
        }
    }
    return false;
}

P operator+(P const p, double offset)
{
    return P(p.x + offset, p.y + offset, p.z + offset);
}

P operator*(P const p, double t)
{
    return P(p.x * t, p.y * t, p.z * t);
}

std::ostream& operator <<( std::ostream & flux, P const& p)
{
    flux << "[" << p.x << ";" << p.z << ";" << p.z << "]";
    return flux;
}

double distance(double x1, double y1, double z1, double x2, double y2, double z2)
{
    return sqrt(pow(x1-x2,2) + pow(y1 - y2, 2) + pow(z1 - z2, 2));
}

double distance(P const& p1, P const& p2)
{
    return distance(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
}

double distance(P const& p1, glm::vec3 const& p2)
{
    return distance(p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
}
