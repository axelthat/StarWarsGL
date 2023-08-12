#include "ShipBullet.h"
#include "Game.h"
#include "Renderer2D.h"
#include "Constants.h"

static const unsigned int SHIP_BULLET_HEIGHT = 50.0f;
static const unsigned int SHIP_BULLET_WIDTH = 15.0f;

ShipBullet::ShipBullet(glm::vec2& shipPosition) {
	Reset(shipPosition);
}

ShipBullet::~ShipBullet() {

}

void ShipBullet::OnUpdate(float ts) {
	if (!active) {
		return;
	}
	Movement(ts);
}

void ShipBullet::OnRender() {
	if (!active) {
		return;
	}
	Renderer2D::DrawQuad(m_Position, m_Rotation, m_Scale, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

void ShipBullet::Reset(glm::vec2& shipPosition) {
	m_Position = glm::vec2(shipPosition.x, shipPosition.y + SHIP_BULLET_HEIGHT);
	m_Rotation = 0.0f;
	m_Scale = glm::vec2(SHIP_BULLET_WIDTH, SHIP_BULLET_HEIGHT);
	active = true;
}

void ShipBullet::Movement(float ts) {
	m_Position.y = m_Position.y + 200.0f * ts;
	if (m_Position.y > K_GAME_HEIGHT + SHIP_BULLET_HEIGHT) {
		active = false;
	}
}