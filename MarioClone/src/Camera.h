#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

class Camera {
private:
	glm::vec2 m_Position;
	glm::mat4 m_View;
	glm::mat4 m_Projection;

public:
	Camera(float left, float right, float bottom, float top);

public:
	inline void SetPosition(glm::vec2 position) {
		m_Position = position;
		ReCaculateViewMatrix();
	}

	inline const glm::vec2& GetPosition() const { return m_Position; };
	inline const glm::mat4& GetView() const { return m_View; };
	inline const glm::mat4& GetProjection() const { return m_Projection; };

private:
	void ReCaculateViewMatrix();
};