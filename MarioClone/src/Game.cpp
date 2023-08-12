#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer2D.h"

Game::Game(unsigned int width, unsigned int height) :
	width(width), height(height), camera(0, width, 0, height), ship(nullptr), background(nullptr)
{

}

Game::~Game() {
	Renderer2D::OnShutdown();

	delete ship;
	delete background;

	ship = nullptr;
	background = nullptr;
}

void Game::onInit() {
	LoadAllShader();
	LoadAllTexture();

	Renderer2D::OnInit();

	background = new Background(*this);
	ship = new Ship(*this);
}

void Game::onUpdate(float ts) {
	for (int i = 0; i < scene_objects.size(); i++)
		scene_objects[i]->OnUpdate(ts);

	camera.SetPosition(camera.GetPosition());
}

void Game::onRender() {
	Renderer2D::BeginScene(camera);

	for (int i = 0; i < scene_objects.size(); i++)
		scene_objects[i]->OnRender();

	Renderer2D::EndScene();
}

void Game::LoadAllShader() {
	Shader::LoadShader("Sprite", "Shader/Sprite.vert.glsl", "Shader/Sprite.frag.glsl");
	Shader::LoadShader("Flat", "Shader/Flat.vert.glsl", "Shader/Flat.frag.glsl");
}

void Game::LoadAllTexture() {
	//Texture::LoadTexture("ShipFullHealth", "Texture/ship-full-health.png", true);
	//Texture::LoadTexture("ShipEngines", "Texture/ship-engines.png", true);
	Texture::LoadTexture("Sprite", "Texture/sprite.png", true);
	Texture::LoadTexture("Background", "Texture/background.png", true);
}

void Game::RegisterGameEvent(IObject& object)
{
	scene_objects.push_back(&object);
}

void Game::UnRegisterGameEvent(IObject& object)
{
	for (int i = 0; i < scene_objects.size(); i++)
	{
		if (scene_objects[i] == &object)
			scene_objects.erase(scene_objects.begin() + i);
	}
}