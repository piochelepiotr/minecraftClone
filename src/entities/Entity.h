#pragma once
#include "models/texturedModel.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
    public:
        Entity(glm::vec3 position, TexturedModel *model, float rotX, float rotY, float rotZ, float scale, int textureIndex);
        Entity();
        virtual ~Entity();

        glm::vec3 getposition() { return m_position; }
        void setposition(glm::vec3 position) { m_position = position; }
        TexturedModel *getmodel() { return m_model; }
        void setmodel(TexturedModel *model) { m_model = model; }
        float getrotX() { return m_rotX; }
        void setrotX(float rotX) { m_rotX = rotX; }
        float getrotY() { return m_rotY; }
        void setrotY(float rotY) { m_rotY = rotY; }
        float getrotZ() { return m_rotZ; }
        void setrotZ(float rotZ) { m_rotZ = rotZ; }
        float getscale() { return m_scale; }
        void setscale(float scale) { m_scale = scale; }
        void increasePosition(float dx, float dy, float dz);
        void increaseRotation(float dx, float dy, float dz);
        void move();

        int getTextureIndex() const;
        void setTextureIndex(int textureIndex);
        float getTextureXOffset();
        float getTextureYOffset();

protected:
        glm::vec3 m_position;
        TexturedModel *m_model;
        float m_rotX;
        float m_rotY;
        float m_rotZ;
        float m_scale;
        int m_textureIndex;
};

