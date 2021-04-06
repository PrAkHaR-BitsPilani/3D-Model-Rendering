#include "Mesh.h"
#include <iostream>

Mesh::Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	layout = new VertexBufferLayout();
	layout->push<float>(3);
	layout->push<float>(3);
	layout->push<float>(2);
	setupMesh();
}

void Mesh::Draw(Shader* shader , std::string uniformPrefix)
{
	unsigned int diffuseCount = 1;
	unsigned int specularCount = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + i));	//might create errors
		std::string number;
		std::string type = textures[i].type;
		if (type == "texture_diffuse")
			number = std::to_string(diffuseCount++);
		else if (type == "texture_specular")
			number = std::to_string(specularCount++);
		shader->setUniform1i((uniformPrefix+type + number).c_str(), i);
		GLCall(glBindTexture(GL_TEXTURE_2D, textures[i].id));
	}

	vertexArray->bind();
	GLCall(glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0));
	vertexArray->unbind();

	GLCall(glActiveTexture(GL_TEXTURE0));	//reset to default
}

void Mesh::setupMesh()
{
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(vertices.data(), vertices.size() * sizeof(vertex));
	vertexArray->addBuffer(*vertexBuffer, *layout);
	indexBuffer = new IndexBuffer(indices.data(), indices.size());
	vertexArray->unbind();
}

void Mesh::logData()
{
	std::cout << "Vertices{position,normal}\n";
	for (int i = 0; i < vertices.size(); i++)
	{
		glm::vec3 pos = vertices[i].position;
		glm::vec3 nor = vertices[i].normal;
		std::cout << pos.x << "," << pos.y << "," << pos.z << "," << nor.x << "," << nor.y << "," << nor.z << ",\n";
	}
	std::cout << "Indices\n";
	for (int i = 0; i < indices.size(); i++)
	{
		std::cout << indices[i] << ",\n";
	}
}
