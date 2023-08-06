#include "Ship.h"
#include "Game.h"
#include "Renderer2D.h"

static const unsigned int SHIP_HEIGHT = 48.0f;
static const unsigned int SHIP_WIDTH = 48.0f;

Ship::Ship(Game& game) {
	m_Position = glm::vec2(0.0f, SHIP_HEIGHT / 2);
	m_Rotation = 0.0f;
	m_Scale = glm::vec2(150.0f, 150.0f);

	game.RegisterGameEvent(*this);

	currentTexture = &Texture::GetTexture("ShipFullHealth");
}

Ship::~Ship() {

}

void Ship::OnUpdate(float ts) {

}

void Ship::OnRender() {
	Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *currentTexture);
}