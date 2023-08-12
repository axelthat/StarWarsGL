#include "Renderer2D.h"

struct RenderData {
	unsigned int vao;
	unsigned int ibo;
	unsigned int vbo;
	Shader* spriteShader;
	Shader* flatShader;
};

static RenderData* r_Data = nullptr;

void Renderer2D::OnInit() {
	r_Data = new RenderData();
	r_Data->spriteShader = &Shader::GetShader("Sprite");
	r_Data->flatShader = &Shader::GetShader("Flat");

	float vertices[] = {
		-0.5f, -0.5f, 0.f, 0.f,
		-0.5f,  0.5f, 0.f, 1.f,
		 0.5f,  0.5f, 1.f, 1.f,
		 0.5f, -0.5f, 1.f, 0.f
	};

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0
	};

	glGenVertexArrays(1, &r_Data->vao);
	glBindVertexArray(r_Data->vao);

	glGenBuffers(1, &r_Data->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, r_Data->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &r_Data->ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r_Data->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)0);

	r_Data->spriteShader->Bind();
	r_Data->spriteShader->SetInt("u_Tex", 0);
}

void Renderer2D::OnShutdown() {
	glDeleteVertexArrays(1, &r_Data->vao);
	glDeleteBuffers(1, &r_Data->ibo);
	glDeleteBuffers(1, &r_Data->vbo);

	delete r_Data;
	r_Data = nullptr;
}

void Renderer2D::BeginScene(Camera& camera) {
	r_Data->spriteShader->Bind();
	r_Data->spriteShader->SetMatrix4("u_View", camera.GetView());
	r_Data->spriteShader->SetMatrix4("u_Projection", camera.GetProjection());

	r_Data->flatShader->Bind();
	r_Data->flatShader->SetMatrix4("u_View", camera.GetView());
	r_Data->flatShader->SetMatrix4("u_Projection", camera.GetProjection());
}

void Renderer2D::EndScene() {

}

void Renderer2D::DrawQuad(glm::vec2 position, float rotation, glm::vec2 scale, glm::vec4 color) {
	r_Data->flatShader->Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1), { position.x, position.y, 0 }) *
		glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0, 0, 1)) *
		glm::scale(glm::mat4(1), { scale.x, scale.y, 0 });

	r_Data->flatShader->SetMatrix4("u_Model", transform);
	r_Data->flatShader->SetVector4("u_Color", color);

	glBindVertexArray(r_Data->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r_Data->ibo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer2D::DrawTexture(glm::vec2 position, float rotation, glm::vec2 scale, Texture& texture, float u1, float v1, float u2, float v2) {
	r_Data->spriteShader->Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1), { position.x, position.y, 0 }) *
		glm::rotate(glm::mat4(1), glm::radians(rotation), glm::vec3(0, 0, 1)) *
		glm::scale(glm::mat4(1), { scale.x, scale.y, 0 });

	r_Data->spriteShader->SetMatrix4("u_Model", transform);

	// Adjust the UV coordinates
	float vertices[] = {
		-0.5f, -0.5f, u1, v1,
		-0.5f,  0.5f, u1, v2,
		 0.5f,  0.5f, u2, v2,
		 0.5f, -0.5f, u2, v1
	};

	glBindBuffer(GL_ARRAY_BUFFER, r_Data->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	texture.Bind();
	glBindVertexArray(r_Data->vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r_Data->ibo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}