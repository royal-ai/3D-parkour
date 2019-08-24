#include"allheader.h"



Ball::Ball()
{

}


Ball::~Ball()
{
}

void Ball::init(std::string const &path)
{
	ballModel.init(path);
	angleSpeed = 600.0f;
	zSpeed = speedBegin;
	xSpeed = 10.0f;
	cPos = glm::vec3(0.0f, 1.3f, halfLength);
	rightOrLeft = 0;
	jump = false;
	xConstant = 4.0f;
	g = 30.0f;
}

void Ball::update()
{
	if(zSpeed<25.0f)
	zSpeed = speedBegin + (-cPos.z) / 150.0f;//使球的速度越来越快，但不能超过顶峰值
	if (jump == 1)
	{
		jumpMove(offsetY*1.6f);
	}
	rotateAndMove();
	std::cout << zSpeed<< std::endl;
}

void Ball::rotateAndMove()
{
	//x = 5.7f;
	
	cPos.z -= deltaTime * zSpeed;
	
	
	if (rightOrLeft == 1&&(cPos.x==-xConstant||cPos.x==0.0f))
	{
		nPos.x += xConstant;
	}
	if (rightOrLeft == 2 && (cPos.x == +xConstant || cPos.x == 0.0f))
	{
		nPos.x -= xConstant;
	}
	if(rightOrLeft!=0)
	{ 
	crossMove(cPos.x, nPos.x);
	}
	//std::cout << myCamera.Position.z << std::endl;
	ballModel.position = glm::mat4(1.0f);
	ballModel.position = glm::translate(ballModel.position, cPos);
	ballModel.position = glm::rotate(ballModel.position, glm::radians((float)glfwGetTime() * glm::radians(50.0f)*angleSpeed), glm::vec3(-1.0f, 0.0f, 0.0f));
    ballModel.position = glm::scale(ballModel.position, glm::vec3(0.0015f,0.0015f, 0.0015f));
	myCamera.setPosition(glm::vec3(0, 9.0f, cPos.z+14.0f));
	
}

void Ball::draw(shader shader)
{
	ballModel.Draw(shader);
}

void Ball::again()
{
	zSpeed = speedBegin;
	cPos = glm::vec3(0.0f, 1.3f, +1 * halfLength);
	nPos.x = 0.0f;
	rightOrLeft = 0;
	jump = false;
	myCamera.setPosition(glm::vec3(0, 9.0f, cPos.z + 14.0f));

}

inline void Ball::crossMove(float begin, float end)
{
	if (begin > end)
	{
		if ((cPos.x - end)>0.2f)
		{
		cPos.x -= xSpeed * deltaTime;
		}
		else
		{
			cPos.x = end;
			rightOrLeft = 0;
		}
	}
	if (begin < end)
	{
		if ((cPos.x - end)<-0.2f)
		{
			cPos.x += xSpeed * deltaTime;
		}
		else
		{
			cPos.x = end;
			rightOrLeft = 0;
		}
	}
}


 void Ball::setRightOrLeft(int a)
{
	rightOrLeft = a;
}

 void Ball::setJump(bool a)
{
	jump = a;
}

 float Ball::getZ()
 {
	 return cPos.z;
 }

 void Ball::jumpMove(float y)
 {
	 float v = sqrt(2 * y*g);//重力方程吖吖吖
	 static float t = 0.0f;
	 t += deltaTime;
	cPos.y = v * t - 0.5*g*t*t+ballY;
	 
	 if (cPos.y < ballY)
	 {
		 cPos.y = ballY;
		 jump = 0;
		 t = 0.0f;
	 }
 }

