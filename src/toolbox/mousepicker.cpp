#include "mousepicker.h"
#include "toolbox/maths.h"
#include <SFML/Window.hpp>
#include <iostream>

MousePicker::MousePicker(Camera *camera, World *world, glm::mat4 const& projectionMatrix, double windowX, double windowY) :
    m_camera(camera),
    m_world(world),
    m_projectionMatrix(projectionMatrix),
    m_windowX(windowX),
    m_windowY(windowY)
{
    m_invertProjectionMatrix = glm::inverse(m_projectionMatrix);
}

void MousePicker::createViewMatrix()
{
    m_viewMatrix = Maths::createViewMatrix(*m_camera);
}

void MousePicker::updateWindowSize(double windowX, double windowY)
{
    m_windowX = windowX;
    m_windowY = windowY;
}

glm::vec3 MousePicker::currentRay() const
{
    return m_currentRay;
}

void MousePicker::update()
{
    //createViewMatrix();
    computeMouseRay();
}

void MousePicker::computeMouseRay()
{
    glm::mat4 mat(1.0);
    mat = glm::rotate   (mat, m_camera->yaw(), glm::vec3(0, 1, 0));
    mat = glm::rotate   (mat, m_camera->pitch(), glm::vec3(1, 0, 0));
    //mat = glm::rotate   (mat, m_camera->roll(), glm::vec3(0, 0, 1));
    glm::vec4 xray(0,0,-1, 1);
    //xray = glm::rotate(xray, m_camera->yaw(), glm::vec3(0,1,0));
    xray = mat * xray;
    m_currentRay = glm::vec3(-xray.x, -xray.y, xray.z);
    //double x = m_windowX / 2;
    //double y = m_windowY / 2;
    //glm::vec2 coor = getNormalizedCoord(x, y);
    //std::cout << coor.x << ";" << coor.y << std::endl;
    //glm::vec2 coor(0,0);
    //glm::vec4 clipCoord(coor.x, coor.y, -1, 1);
    //glm::vec4 eyeCoord = toEyeCoord(clipCoord);
    //m_currentRay = toWorldCoord(eyeCoord);
}

glm::vec2 MousePicker::getNormalizedCoord(double x, double y)
{
    return glm::vec2((2*x)/m_windowX - 1, -((2*y)/m_windowY -1));
}

glm::vec4 MousePicker::toEyeCoord(glm::vec4 const& clipCoord)
{
    glm::vec4 eyeCoord = clipCoord * m_invertProjectionMatrix;
    return glm::vec4(eyeCoord.x, eyeCoord.y, -1, 0);
}

glm::vec3 MousePicker::toWorldCoord(glm::vec4 const& eyeCoord)
{
    glm::mat4 inverseViewMatrix = glm::inverse(m_viewMatrix);
    glm::vec4 worldCoord = eyeCoord * inverseViewMatrix;
    glm::vec3 mouseRay(worldCoord.x, worldCoord.y, worldCoord.z);
    mouseRay = glm::normalize(mouseRay);
    return mouseRay;
}

double MousePicker::getNextBlock(double & x_i, double & y_i, double & z_i, glm::vec3 const& dir,
                  int & x, int & y, int & z)
{
    double x_s = x_i;
    double y_s = y_i;
    double z_s = z_i;
    double x_b = x;
    double y_b = y;
    double z_b = z;
    double x_e = x_b + 1;
    double y_e = y_b + 1;
    double z_e = z_b + 1;
    //std::cout << "start : " << x_s << ";" << y_s <<";" << z_s << std::endl;
    //std::cout << "begin : " << x_b << ";" << y_b <<";" << z_b << std::endl;
    //std::cout << "end : " << x_e << ";" << y_e <<";" << z_e << std::endl;
    //up face
    if(dir.y > 0)
    {
        y_i = y_e;
        double t = (y_i - y_s) / dir.y;
        x_i = x_s + t*dir.x;
        z_i = z_s + t*dir.z;
        if(
                z_i >= z_b && z_i <= z_e &&
                x_i >= x_b && x_i <= x_e
                )
        {
            //std::cout << "TOP" << std::endl;
            y++;
            return sqrt(pow(x_i-x_s, 2) + pow(y_i-y_s, 2) + pow(z_i-z_s, 2));
        }
    }
    //bottom face
    if(dir.y < 0)
    {
        y_i = y_b;
        double t = (y_i - y_s) / dir.y;
        x_i = x_s + t*dir.x;
        z_i = z_s + t*dir.z;
        if(
                z_i >= z_b && z_i <= z_e &&
                x_i >= x_b && x_i <= x_e
                )
        {
            //std::cout << "BOTTOM" << std::endl;
            y--;
           return sqrt(pow(x_i-x_s, 2) + pow(y_i-y_s, 2) + pow(z_i-z_s, 2));
        }
    }
    //right face
    if(dir.x > 0)
    {
        x_i = x_e;
        double t = (x_i - x_s) / dir.x;
        y_i = y_s + t*dir.y;
        z_i = z_s + t*dir.z;
        if(
                z_i >= z_b && z_i <= z_e &&
                y_i >= y_b && y_i <= y_e
                )
        {
            //std::cout << "RIGHT" << std::endl;
            x++;
            return sqrt(pow(x_i-x_s, 2) + pow(y_i-y_s, 2) + pow(z_i-z_s, 2));
        }
    }
    //left face
    if(dir.x < 0)
    {
        x_i = x_b;
        double t = (x_i - x_s) / dir.x;
        y_i = y_s + t*dir.y;
        z_i = z_s + t*dir.z;
        if(
                z_i >= z_b && z_i <= z_e &&
                y_i >= y_b && y_i <= y_e
                )
        {
            //std::cout << "LEFT" << std::endl;
            x--;
            return sqrt(pow(x_i-x_s, 2) + pow(y_i-y_s, 2) + pow(z_i-z_s, 2));
        }
    }
    //front face
    if(dir.z > 0)
    {
        z_i = z_e;
        double t = (z_i - z_s) / dir.z;
        x_i = x_s + t*dir.x;
        y_i = y_s + t*dir.y;
        if(
                x_i >= x_b && x_i <= x_e &&
                y_i >= y_b && y_i <= y_e
                )
        {
            //std::cout << "FRONT" << std::endl;
            z++;
            return sqrt(pow(x_i-x_s, 2) + pow(y_i-y_s, 2) + pow(z_i-z_s, 2));
        }
    }
    //back face
    if(dir.z < 0)
    {
        z_i = z_b;
        double t = (z_i - z_s) / dir.z;
        x_i = x_s + t*dir.x;
        y_i = y_s + t*dir.y;
        if(
                x_i >= x_b && x_i <= x_e &&
                y_i >= y_b && y_i <= y_e
                )
        {
            //std::cout << "BACK" << std::endl;
            z--;
            return sqrt(pow(x_i-x_s, 2) + pow(y_i-y_s, 2) + pow(z_i-z_s, 2));
        }
    }
    std::cout << "problem : no face to get out of the cube" << std::endl;
    return 0;
}

bool MousePicker::getAimedBlock(int & x, int & y, int & z)
{
    update();
    glm::vec3 startPoint = m_camera->position();
    double px = startPoint.x;
    double py = startPoint.y;
    double pz = startPoint.z;
    x = (int)floor(px);
    y = (int)floor(py);
    z = (int)floor(pz);
    for(int i = 0; i < MAX_DISTANCE_BLOCK; i++)
    {
        if(m_world->block(x, y, z) != Block::AIR)
        {
            return true;
        }
        getNextBlock(px, py, pz, m_currentRay, x, y, z);
    }
    return false;
}

double MousePicker::placeInFront(double x_s, double y_s, double z_s, glm::vec3 const& dir)
{
    double dist = 0;
    double px = x_s;
    double py = y_s;
    double pz = z_s;
    int x = (int)floor(px);
    int y = (int)floor(py);
    int z = (int)floor(pz);
    for(int i = 0; i < 5; i++)
    {
        //std::cout << "POS : " << x << ";"<<y<<";"<<z<<std::endl;
        if(m_world->block(x, y, z) != Block::AIR)
        {
            return dist;
        }
        dist += getNextBlock(px, py, pz, dir, x, y, z);
    }
    return dist;
}
