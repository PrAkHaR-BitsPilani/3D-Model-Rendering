#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Shader.h"
#include "Mesh.h"

class Model {
public:
	Model(std::string path);
	void Draw(Shader* shader , std::string uniformPrefix);
	void logData();

private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<texture> textures_cache;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string name);

};