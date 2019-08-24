#pragma once
#include<string>
#include<glm.hpp>
#include<vector>
#include"shader.h"
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};
struct Texture {
	unsigned int id;
	std::string type;//可能是diffuse，或者specular
	std::string path;
};
class Mesh
{
public:
	Mesh();
	~Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices, std::vector<Texture>textures);
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	void Draw(shader shader);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

