#include "Background.h"
#include "Game.h"
#include "Constants.h"
#include "Renderer2D.h"

Background::Background(Game& game) : currentTexture(nullptr) {
	m_Position = glm::vec2(K_GAME_WIDTH / 2, K_GAME_HEIGHT / 2);
	m_Rotation = 0.0f;
	m_Scale = glm::vec2(K_GAME_WIDTH, K_GAME_WIDTH);

	game.RegisterGameEvent(*this);

	currentTexture = &Texture::GetTexture("Background");
}

Background::~Background() {

}

void Background::OnUpdate(float ts) {
	yOffset = yOffset + speed * ts;
}

void Background::OnRender() {
	Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *currentTexture, 0.0f, yOffset, 1.0f, yOffset + 1.0f);
}