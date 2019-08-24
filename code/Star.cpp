#include"allheader.h"


Star::Star()
{
}


Star::~Star()
{
}

void Star::init(std::string const & path)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < allStarNum; i++)
	{
		starModel[i].init(path);
		work[i] = 0;
	}

	for (int i = 0; i < 5; i++) {
		starProduce(myBox.posZ[i], myBox.posZ[i + 1]);
	}
	
	point = 0;
	eatMusic.load("music/score.mp3");
	
}

void Star::again()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < allStarNum; i++)
	{
		work[i] = 0;
	}

	for (int i = 0; i < 5; i++) {
		starProduce(myBox.posZ[i], myBox.posZ[i + 1]);
	}

	point = 0;
}

void Star::update()
{
	disappear();
	//std::cout << point << std::endl;
}

void Star::draw(shader shader)
{
	for (int i = 0; i <allStarNum; i++)
	{
		if (work[i] == 1)
		{
			
			starModel[i].position = glm::mat4(1.0f);
			starModel[i].position = glm::translate(starModel[i].position, position[i]);
			//starModel[i].position = glm::rotate(starModel[i].position, glm::radians((float)glfwGetTime() * glm::radians(50.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
			//因为obj x,y 点坐标不在原点所以放弃旋转
			starModel[i].position = glm::scale(starModel[i].position, glm::vec3(0.3f, 0.3f, 0.3f));
			starModel[i].Draw(shader);
		}
	}
}

void Star::starProduce(float begin, float end)
{
	int x = (rand() % 3 - 1)*myBall.xConstant;//直接就是star的x坐标了
	int num = (begin - end) / instant;
	for (int i = 1; i <= num; i++) 
	{
		int a = getABlankStar();
		position[a] = glm::vec3(x, starY, begin - instant * i);
		work[a] = 1;
	}
}


inline int Star::getABlankStar()
{
	for (int i = 0; i < allBoxNum; i++)
	{
		if (work[i] == false)
			return i;
		
	}
	std::cout << "no enough star >>>>>>>>>>>>>>>>";

	return -1;
}

void Star::disappear()
{
	for (int i = 0; i < allStarNum; i++)
	{
		if (myBall.getZ() - position[i].z<5.0f&&work[i]==1)
		{
			if ((crashTest(myBall.cPos, position[i], myBall.xConstant / 2, 1.0f, 4.0f)))
			{
			point++;
			eatMusic.play();
			work[i] = 0;
			}
		}
		if (myCamera.Position.z - position[i].z < 0.0f&&work[i] == 1)
		{
			work[i] = 0;
		}
	}


}

