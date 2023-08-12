#pragma once

#include <glm/glm.hpp>

#include "IObject.h"
#include "Texture.h"
#include "ShipBullet.h"

class Game;

class Ship: public IObject {
private:
	Texture* currentTexture;
	std::vector<ShipBullet> shipBullets;

public:
	Ship(Game& game);
	~Ship();

public:
	void OnUpdate(float ts) override;
	void OnRender() override;

private:
	void Movement(float ts);
	void Fire(float ts);
};