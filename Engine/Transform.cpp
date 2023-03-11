#include "pch.h"
#include "Transform.h"
#include <math.h>

/******************************************************************************
******************************************************************************/
Transform::Transform(
    Entity* owner,
    float posX,
    float posY,
    float rotation,
    float w,
    float h,
    float s
)
    : Component(owner)
    , m_position(glm::vec2(posX, posY))
    , m_width(w)
    , m_height(h)
    , m_scale(s)
    , m_rotation(rotation)
{}

/******************************************************************************
******************************************************************************/
glm::vec2 Transform::SetPosition(const glm::vec2& newPos)
{
    m_position = newPos;
    return m_position;
}

/******************************************************************************
******************************************************************************/
float Transform::SetRotation(float newRotation)
{
    if (newRotation < 0.0f) {
        newRotation += 360;
    }
    else if (newRotation > 360)
    {
        newRotation -= 360;
    }
    m_rotation = newRotation;
    return m_rotation;
}

/******************************************************************************
******************************************************************************/
std::string Transform::ToString()
{
    char buffer[256];
    snprintf(
        buffer,
        sizeof(buffer),
        "Transform on %s: posX: %f, posY: %f, w: %f, h: %f, s: %f\n",
        m_owner->m_name,
        m_position.x,
        m_position.y,
        m_width,
        m_height,
        m_scale
    );
    return buffer;
}

/******************************************************************************
******************************************************************************/
Transform::~Transform()
{
}
