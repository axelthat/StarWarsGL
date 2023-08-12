#pragma once

#include <glm/glm.hpp>
#include <array>

#include "IObject.h"
#include "Texture.h"
#include "ShipBullet.h"

class Game;

class Ship: public IObject {
private:
	Texture* currentTexture;
	std::vector<ShipBullet> shipBullets;

	float elapsedTime = 0.0f;
	float animationSpeed = 0.1f;

	unsigned int animationTextureOffset = 0;
	unsigned int animationTextureIndex = 0;
	std::array<float, 28> animationTextureCoords = {
		0.0f, 0.5f, 0.25f, 0.75f,
		0.25f, 0.5f, 0.5f, 0.75f,
		0.5f, 0.5f, 0.75f, 0.75f,

		0.0f, 0.25f, 0.25f, 0.5f,
		0.25, 0.25f, 0.5, 0.5f,
		0.5f, 0.25f, 0.75f, 0.5f,
		0.75f, 0.25f, 1.0f, 0.5f
	};

public:
	Ship(Game& game);
	~Ship();

public:
	void OnUpdate(float ts) override;
	void OnRender() override;

private:
	void Animation(float ts);
	void Movement(float ts);
	void Fire(float ts);
};