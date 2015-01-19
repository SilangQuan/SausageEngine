#include "entity.h"


Entity::Entity()
{
	isLoaded = false;
}


Entity::~Entity()
{
}

Entity::Entity(ShaderProgram program)
{
	shaderProgram = program;
	isLoaded = false;
}

bool Entity::loadFromFile(const std::string& filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (!scene)
	{
		std::cout << "Couldn't load model, Error Importing Asset" << std::endl;
		return false;
	}

	meshEntries.resize(scene->mNumMeshes);
	textures.resize(scene->mNumMaterials);

	for (int i = 0; i<scene->mNumMeshes; i++)
	{
		aiMesh* paiMesh = scene->mMeshes[i];
		int iMeshFaces = paiMesh->mNumFaces;
		std::cout << "Mesh " << i << " faces:" << iMeshFaces << std::endl;
		initMesh(i, paiMesh);
	}
	std::cout << scene->mNumMaterials << std::endl;

	if (scene->mNumMaterials > 1)
	{
		initMaterial(scene, filepath);
	}

	aiMesh* paiMesh = scene->mMeshes[0];

	std::cout << "scene->mNumMeshes:" << scene->mNumMeshes << std::endl;
	std::cout << "scene->mNumMaterials:" << scene->mNumMaterials << std::endl;
	std::cout << "mesh0->mNumFaces:" << paiMesh->mNumFaces << std::endl;
	std::cout << "mesh0->mNumVertices:" << paiMesh->mNumVertices << std::endl;

	isLoaded = true;
	return true;
}

void Entity::render()
{
/*
	if (!isLoaded) return;
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	for (unsigned int i = 0; i < meshEntries.size(); i++) {
		glBindBuffer(GL_ARRAY_BUFFER, meshEntries[i].getVAO());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(sizeof(glm::vec3)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const GLvoid*)(sizeof(glm::vec2) + sizeof(glm::vec3)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshEntries[i].getEBO());

		const unsigned int materialIndex = meshEntries[i].getMaterialIndex();

		if (materialIndex < textures.size() && textures[materialIndex]) {
			textures[materialIndex]->bind(GL_TEXTURE0);
			//prog->setUniform("Tex2", 0);
			//cout<<"Draw "<<i<<endl;
		}


		glDrawElements(GL_TRIANGLES, meshEntries[i].getNumIndices(), GL_UNSIGNED_INT, 0);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);*/

	for (GLuint i = 0; i < this->meshEntries.size(); i++)
		this->meshEntries[i].draw(this->shaderProgram);
}


void Entity::initMesh(unsigned int index, const aiMesh* paiMesh)
{

	meshEntries[index].setMaterialIndex(paiMesh->mMaterialIndex);
	std::cout << "mesh" << index << "mMaterialIndex" << paiMesh->mMaterialIndex << std::endl;
	std::vector<VertexData> vertices;
	std::vector<unsigned int> indices;
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	vertices.reserve(paiMesh->mNumVertices);
	indices.reserve(paiMesh->mNumFaces);

	for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ?
			&(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		VertexData v(glm::vec3(pPos->x, pPos->y, pPos->z),
			glm::vec2(pTexCoord->x, pTexCoord->y),
			glm::vec3(pNormal->x, pNormal->y, pNormal->z)
			);
		// cout<<i<<": "<<v.m_tex.x<<v.m_tex.y<<endl;
		vertices.push_back(v);
	}

	for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
	{
		const aiFace& Face = paiMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0]);
		indices.push_back(Face.mIndices[1]);
		indices.push_back(Face.mIndices[2]);
	}

	meshEntries[index].init(vertices, indices);
}

bool Entity::initMaterial(const aiScene* pScene, const std::string& filePath)
{
	std::string::size_type slashIndex = filePath.find_last_of("/");
	std::string dir;

	if (slashIndex == std::string::npos) {
		dir = ".";
	}
	else if (slashIndex == 0) {
		dir = "/";
	}
	else {
		dir = filePath.substr(0, slashIndex);
	}


	bool Ret = true;
	// Initialize the materials
	for (unsigned int i = 1; i < pScene->mNumMaterials; i++)
	{
		const aiMaterial* pMaterial = pScene->mMaterials[i];
		textures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string fullPath = dir + "/" + path.data;
				textures[i] = new Texture(GL_TEXTURE_2D, fullPath.c_str());

				if (!textures[i]->load()) {
					printf("Error loading texture '%s'\n", fullPath.c_str());
					delete textures[i];
					textures[i] = NULL;
					Ret = false;
				}
				else {
					printf("Loaded texture '%s'\n", fullPath.c_str());
				}
			}
		}

		// Load a white texture in case the model does not include its own texture
		if (textures[i] == NULL) {
			textures[i] = new Texture(GL_TEXTURE_2D, "../assets/textures/white.png");
			Ret = textures[i]->load();
		}

	}

	return Ret;
}

void Entity::setShader(ShaderProgram shader)
{
	this->shaderProgram = shader;
}
