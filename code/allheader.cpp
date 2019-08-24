#include"allheader.h"
const unsigned int SCR_WIDTH = 1400;
const unsigned int SCR_HEIGHT = 990;
Camera myCamera(glm::vec3(0.0f, 5.0f, 9.0f));
Ball myBall;
Board myBoard;
Obstacle myBox;
Star myStar;
Model sky;
Tunnel myTunnel;
shader modelShader;
shader pictureShader;
picture PmenuPlay;
picture PmenuExit;
picture backMenu0;
picture backMenu1;
picture continue0;
picture continue1;
picture again0;
picture again1;
picture point;
picture record;
picture num[30];
AudioClip menuMusic;
AudioClip playMusic;
int recordScore;
int gameState;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间
float Msensitity = 1.5f;
AudioClip eatMusic;
glm::mat4 projection = glm::perspective(glm::radians(myCamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);


bool crashTest(glm::vec3 a, glm::vec3 b, float xOffset, float yOffset, float zOffset)
{
	if ((a.x - b.x) < xOffset && (b.x - a.x) < xOffset && (a.y - b.y) < yOffset && (b.y - a.y)
		< yOffset && (a.z - b.z) < zOffset && (b.z - a.z) < (zOffset))
		return true;
	return false;
}
