#pragma once

#include <glm/glm.hpp>

#include "IObject.h"
#include "Texture.h"

class Game;

class ShipBullet : public IObject {
private:
	bool active = false;

public:
	ShipBullet(glm::vec2& shipPosition);
	~ShipBullet();

public:
	void OnUpdate(float ts) override;
	void OnRender() override;

	void Reset(glm::vec2& shipPosition);

	bool IsActive() { return active; };

private:
	void Movement(float ts);
};