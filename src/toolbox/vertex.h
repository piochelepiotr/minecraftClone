#ifndef VERTEX_H
#define VERTEX_H

#include <string>

class Vertex
{
public:
    //Vertex(int v, int vt, int vn);
    Vertex(std::string s);
    int v() const { return m_v; }
    int vt() const { return m_vt; }
    int vn() const { return m_vn; }
private:
    int m_v;
    int m_vt;
    int m_vn;
};

#endif // VERTEX_H
