#include "vertex.h"
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;

/*Vertex::Vertex(int v, int vt, int vn) :
        m_v(v),
        m_vt(vt),
        m_vn(vn)
{
}*/

Vertex::Vertex(std::string s)
{
    vector<string> splited;
    boost::split(splited, s, [](char c) { return c == '/'; });
    m_v = stoi(splited[0]) - 1;
    m_vt = stoi(splited[1]) - 1;
    m_vn = stoi(splited[2]) - 1;
}
