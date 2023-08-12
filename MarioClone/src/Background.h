#pragma once

#include <glm/glm.hpp>
#include <array>

#include "IObject.h"
#include "Texture.h"

class Game;

class Background : public IObject {
private:
	Texture* currentTexture;
	float yOffset = 0.0f;
	float speed = 0.05f;

public:
	Background(Game& game);
	~Background();

public:
	void OnUpdate(float ts) override;
	void OnRender() override;
};