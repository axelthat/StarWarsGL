#include "Ship.h"
#include "Game.h"
#include "Renderer2D.h"
#include <GLFW/glfw3.h>
#include "Constants.h"

static const unsigned int SHIP_HEIGHT = 48.0f;
static const unsigned int SHIP_WIDTH = 48.0f;

Ship::Ship(Game& game) : currentTexture(nullptr) {
	m_Position = glm::vec2((K_GAME_WIDTH - SHIP_WIDTH) / 2, SHIP_HEIGHT);
	m_Rotation = 0.0f;
	m_Scale = glm::vec2(150.0f, 150.0f);

	game.RegisterGameEvent(*this);

	currentTexture = &Texture::GetTexture("ShipFullHealth");
}

Ship::~Ship() {

}

void Ship::OnUpdate(float ts) {
	Movement(ts);
	Fire(ts);

	for (auto& shipBullet : shipBullets) {
		if (shipBullet.IsActive()) {
			shipBullet.OnUpdate(ts);
		}
	}
}

void Ship::OnRender() {
	for (auto &shipBullet : shipBullets) {
		if (shipBullet.IsActive()) {
			shipBullet.OnRender();
		}
	}

	Renderer2D::DrawTexture(m_Position, m_Rotation, m_Scale, *currentTexture);
}

void Ship::Movement(float ts) {
	const float speed = 300.0f;

	glm::vec2 newPosition = m_Position;

	if (Input::GetKey(GLFW_KEY_W)) {
		newPosition.y = newPosition. y + speed * ts;
	}

	if (Input::GetKey(GLFW_KEY_S)) {
		newPosition.y = newPosition.y - speed * ts;
	}

	if (Input::GetKey(GLFW_KEY_A)) {
		newPosition.x = newPosition.x - speed * ts;
	}

	if (Input::GetKey(GLFW_KEY_D)) {
		newPosition.x = newPosition.x + speed * ts;
	}

	if (newPosition.y < SHIP_HEIGHT / 2) {
		newPosition.y = SHIP_HEIGHT / 2;
	}

	m_Position = newPosition;
}

void Ship::Fire(float ts) {
	if (!Input::GetKeyDown(GLFW_KEY_SPACE)) {
		return;
	}

	auto existingShipBullet = std::find_if(
		shipBullets.begin(),
		shipBullets.end(),
		[](ShipBullet& shipBullet) { return !shipBullet.IsActive(); }
	);
	if (existingShipBullet != shipBullets.end()) {
		existingShipBullet->Reset(m_Position);
	}
	else {
		shipBullets.emplace_back(m_Position);
	}
}