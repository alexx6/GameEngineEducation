#include "ControllableCube.h"

ControllableCube::ControllableCube(InputHandler* ih) : m_inputHandler(ih) {}

void ControllableCube::update(float deltaTime)
{
    float velocity = 0.0f;
    if (m_inputHandler->GetInputState().test(eIC_GoLeft))
        velocity -= 3.0f;
    if (m_inputHandler->GetInputState().test(eIC_GoRight))
        velocity += 3.0f;

    m_vPosition[0] += velocity * deltaTime;
    m_pRenderProxy->SetPosition(m_vPosition);
};
