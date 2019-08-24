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
#include "camera.h"
#include"Model.h"
const float halfLength=78.5f;//板的一班长度
class Board
{
public:
	Board();
	~Board();
	void init(std::string const &path);
	void draw(shader shader);
	void update();
	void again();
private:
	float posZA;
	float posZB;
	Model modelA;
	Model modelB;
	bool work;//work是true代表A在视野中，否则B在视野中
	


};

