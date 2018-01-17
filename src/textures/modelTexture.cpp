#include "modelTexture.h"

ModelTexture::ModelTexture(GLuint textID) :
    m_textID(textID),
    m_shineDamper(10),
    m_reflectivity(0),
    m_numberRows(1)
{

}

ModelTexture::ModelTexture(GLuint textID, int numberRows) :
    m_textID(textID),
    m_shineDamper(10),
    m_reflectivity(0),
    m_numberRows(numberRows)
{

}

float ModelTexture::getShineDamper() const
{
    return m_shineDamper;
}

void ModelTexture::setShineDamper(float shineDamper)
{
    m_shineDamper = shineDamper;
}

float ModelTexture::getReflectivity() const
{
    return m_reflectivity;
}

void ModelTexture::setReflectivity(float reflectivity)
{
    m_reflectivity = reflectivity;
}

int ModelTexture::getNumberRows() const
{
    return m_numberRows;
}

void ModelTexture::setNumberRows(int numberRows)
{
    m_numberRows = numberRows;
}
