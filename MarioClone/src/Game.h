#pragma once

#include <vector>
#include "Camera.h"
#include "IObject.h"
#include "Ship.h"
#include "Background.h"

class Game {
private:
	Camera camera;
	unsigned int width;
	unsigned int height;
	std::vector<IObject*> scene_objects;

	Ship* ship;
	Background* background;

public:
	Game(unsigned int width, unsigned int height);
	~Game();

public:
	void RegisterGameEvent(IObject& object);
	void UnRegisterGameEvent(IObject& object);

public:
	void onInit();
	void onUpdate(float ts);
	void onRender();

	void LoadAllShader();
	void LoadAllTexture();

	inline unsigned int GetWidth() { return width; }
	inline unsigned int GetHeight() { return height; }
};