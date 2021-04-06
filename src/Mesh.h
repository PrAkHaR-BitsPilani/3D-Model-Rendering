#pragma once
#include "glm/glm.hpp"
#include "Shader.h"
#include <string>
#include <vector>
#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

struct vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	std::vector<vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<texture> textures;

	Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures);
	void Draw(Shader* shader , std::string uniformPrefix);
	void logData();

private:
	VertexArray* vertexArray;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	VertexBufferLayout* layout;

	void setupMesh();

};