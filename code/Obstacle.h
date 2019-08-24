#pragma once
#include<vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"shader.h"
#include "camera.h"
#include"Model.h"
const float offsetX = 4.6f;
const float offsetY = 3.0f;
const int allBoxNum =30;
const int shortDistance = 25.0f;
const int longDistance = 50.0f;
const int startPosZ=50.0f;
class Obstacle
{
public:
	Obstacle();
	~Obstacle();
	void init(std::string const &path);
	void boxProduce( float z);
	void draw(shader shader);
	void update();
	void again();
	void boxCrashTest();
	inline int getABlankBox();
	 void renew();
	 float posZ[6];
private:
	Model box[allBoxNum];
	glm::vec3 boxPosition[allBoxNum];
	bool work[allBoxNum];
	
	
};

