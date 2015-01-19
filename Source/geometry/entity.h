#pragma once

#include "common.h"
#include <string>  
#include <vector>
#include <iostream>  
#include "shader/shaderprogram.h"
#include "geometry/smesh.h"
#include "texture/texture.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Entity
{
public:
	Entity();
	~Entity();
	Entity(ShaderProgram shaderProgram);
	void setShader(ShaderProgram shaderProgram);
	bool loadFromFile(const std::string& filepath);
	void render();

private:
	bool isLoaded;
	int numMaterial;
	ShaderProgram shaderProgram;
	std::vector<SMesh> meshEntries;
	std::vector<Texture*> textures;

	void initMesh(unsigned int index, const aiMesh* paiMesh);
	bool initMaterial(const aiScene* pScene, const std::string& filePath);
};

