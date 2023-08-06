#pragma once

#include <glm/glm.hpp>
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

class Renderer2D {
public:
	static void OnInit();
	static void OnShutdown();

	static void BeginScene(Camera& camera);
	static void EndScene();

	static void DrawQuad(glm::vec2 position, float rotation, glm::vec2 scale, glm::vec4 color);
	static void DrawTexture(glm::vec2 position, float rotation, glm::vec2 scale, Texture& texture);
};