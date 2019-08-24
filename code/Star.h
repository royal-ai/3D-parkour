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
const int allStarNum =30;
const float starY=1.5f;
const float instant=12.0f;
class Star
{
public:
	Star();
	~Star();
	void init(std::string const &path);//init要放在obstacle后面
	void again();
	void update();
	void draw(shader shader);
	void starProduce(float begin, float end);
	inline  int getABlankStar();
	void disappear();
	int point;
private:
	Model starModel[allStarNum];
	glm::vec3 position[allStarNum];
	bool work[allStarNum];
	

};

