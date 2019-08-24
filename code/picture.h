#pragma once
#include<string>
#include<iostream>
#include<vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"shader.h"
class picture
{
public:
	picture();
	void init(const char* path,float xbegin=-1.0f, float ybegin=1.0f, float width=2.0f, float height=2.0f );
	void Draw(shader pictureShader);
	~picture();
	unsigned int texture_Picture;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
private:
	

};
unsigned int TextureFromFile2(const char *path, bool gamma = false);
