#include"allheader.h"



Obstacle::Obstacle()
{
}


Obstacle::~Obstacle()
{
}

void Obstacle::init(std::string const &path)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < allBoxNum; i++)
	{
		box[i].init(path);
		work[i] = false;
	 }
	posZ[0] = myBall.getZ() - startPosZ;
	posZ[1] = myBall.getZ() - startPosZ-35.0f;
	posZ[2] = myBall.getZ() - startPosZ - 75.0f;
	posZ[3] = myBall.getZ() - startPosZ - 120.0f;
	posZ[4] = myBall.getZ() - startPosZ - 170.0f;
	
	for (int i = 0; i < 4; i++)
	{
		posZ[5] = myBall.getZ() - 225.0f;//防止posZ[5]被改变
		boxProduce(posZ[i]);
	}
}

void Obstacle::boxProduce(float z)
{
	
	int boxNumber = rand() % 2+1;//空的位置为一个或两个
	int a[6];
	for (int i = 0; i < 6; i++)
	{
		a[i] = 1;
	}
	int count = 0;
	while (count < boxNumber) 
	{
	   int pos = rand() % 6 + 1;//1-6
	   if (a[pos] == 1) 
	   {
	      a[pos] = 0;
	      count++;
	   }
	}
	for (int i = 0; i < 6; i++)
	{
		
		if (a[i] == 1)
		{
			int num = getABlankBox();
		work[num] = 1;
			switch (i){//左下{
			case 0:					
				boxPosition[num] = glm::vec3(-offsetX, 0.0f, z);
				break;
			case 1:							
				boxPosition[num] = glm::vec3(0.0f, 0.0f, z);	
				break;
			case 2:							
				boxPosition[num] = glm::vec3(offsetX, 0.0f, z);		
				break;
			case 3:							
				boxPosition[num] = glm::vec3(-offsetX, offsetY, z);		
				break;
			case 4:			
				boxPosition[num] = glm::vec3(0.0f, offsetY, z);	
				break;
			case 5:
				boxPosition[num] = glm::vec3(+offsetX, offsetY, z);		
				break;
			}	
		}
	}
	posZ[5] = z;
}

void Obstacle::draw(shader shader)
{
	for (int i = 0; i < allBoxNum; i++)
	{
		if (work[i] == 1)
		{
			box[i].position = glm::mat4(1.0f);
			box[i].position = glm::translate(box[i].position, boxPosition[i]);
			box[i].position = glm::scale(box[i].position, glm::vec3(0.008f, 0.008f, 0.008f));
			box[i].Draw(shader);
		}
	}
}

void Obstacle::update()
{
    renew();
	boxCrashTest();
	
}

void Obstacle::again()
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < allBoxNum; i++)
	{
		work[i] = false;
	}
	posZ[0] = myBall.getZ() - startPosZ;
	posZ[1] = myBall.getZ() - startPosZ - 35.0f;
	posZ[2] = myBall.getZ() - startPosZ - 75.0f;
	posZ[3] = myBall.getZ() - startPosZ - 120.0f;
	posZ[4] = myBall.getZ() - startPosZ - 170.0f;

	for (int i = 0; i < 4; i++)
	{
		posZ[5] = myBall.getZ() - 225.0f;//防止posZ[5]被改变
		boxProduce(posZ[i]);
	}
}

void Obstacle::boxCrashTest()
{
	for (int i = 0; i < allBoxNum; i++)
	{
		if (posZ[0] == boxPosition[i].z)
		{
			if (crashTest(myBall.cPos, boxPosition[i], 3.0f, offsetY-ballY, offsetY - 0.1f))
			{   
				mciSendString("stop music/gamemusic.mp3", NULL, 0, NULL);
				mciSendString("play music/overmusic.mp3", NULL, 0, NULL);
				gameState = GS_overAgain;
				Sleep(1000);
				mciSendString("play music/玛丽奥.mp3", NULL, 0, NULL);
			}
		}
	}
}

inline int Obstacle::getABlankBox()
{
	for (int i = 0; i < allBoxNum; i++)
	{
		if (work[i] == false)
		{
	return i;
		}
	}
	std::cout << "no enough box               ";
	return -1;
}

void Obstacle::renew()
{
	if (myCamera.Position.z < posZ[0])
	{
		for (int i = 0; i < allBoxNum; i++)
		{
			if (boxPosition[i].z == posZ[0])
			{
				work[i] = 0;
			 }
		}
	
	for (int i = 0; i < 5; i++)
	{
		posZ[i] = posZ[i + 1];
		std::cout << "renew:::::::::::::::::::::::::::::::::::::::::;;";
		
	}
	float lert = (rand() % 10) / 10.0f;//线性插值随机取接下来的障碍物位置,0.0~0.9
	posZ[5] = posZ[4]-(shortDistance * (1 - lert) + longDistance * lert);
	boxProduce(posZ[5]);
	myStar.starProduce(posZ[4], posZ[5]);
	}
}
