#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top) {
	m_Position = glm::vec2(0.0f);
	m_View = glm::mat4(1.0f);
	m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
}

void Camera::ReCaculateViewMatrix() {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { m_Position.x, m_Position.y, 0.0f });
	// inverse??
	m_View = transform;
}