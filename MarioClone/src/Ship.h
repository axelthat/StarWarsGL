#pragma once

#include <glm/glm.hpp>

#include "IObject.h"
#include "Texture.h"

class Game;

class Ship: public IObject {
private:
	Texture* currentTexture;

public:
	Ship(Game& game);
	~Ship();

public:
	void OnUpdate(float ts) override;
	void OnRender() override;
};