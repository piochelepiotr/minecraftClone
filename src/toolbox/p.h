#pragma once

#include <glm/glm.hpp>
#include <ostream>

class P
{
public:
    P(int x, int y, int z);
    int x;
    int y;
    int z;
};

bool operator<(P const& p1, P const& p2);
P operator+(P const p, double offset);
P operator*(P const p, double t);
std::ostream & operator <<( std::ostream & flux, P const& p);

double distance(P const& p1, P const& p2);
double distance(P const& p1, glm::vec3 const& p2);
double distance(double x1, double y1, double z1, double x2, double y2, double z2);

