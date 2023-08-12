#pragma once

#include <string>
#include "glm/glm.hpp"
#include "Input.h"

class IObject {
protected:
	glm::vec2 m_Position;
	float m_Rotation;
	glm::vec2 m_Scale;

public:
	virtual void OnUpdate(float ts) = 0;
	virtual void OnRender() = 0;

	inline glm::vec2 GetPosition() const { return m_Position; }
	inline float GetRotation() const { return m_Rotation; }
	inline glm::vec2 GetScale() const { return m_Scale; }
};