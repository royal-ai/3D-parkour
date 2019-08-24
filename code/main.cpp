
#include"allheader.h"
#include"Model.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mainGame();
void gameSelector();
void again();
void numInit();
void drawScore(int number);
void menuMusicStop();
void playMusicPlay();
void menuMusicPlay();
void playMusicStop();
//unsigned int loadImageToGpu(const char *filename,int texturenum);
//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
std::ifstream readScore;
std::ofstream getScore;
int newGame = 3;
int main()
{
#pragma region windowInit
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//声明版本号是3.3，并且使用核心模式
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D parkour", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//使用这个window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowPos(window, 250, 35);
	//分别在窗口大小变化，鼠标移动，滚轮移动的时候调用这些函数，不必放在循环里
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//使鼠标不可见，并且不会脱离窗口
	//这些函数不用放在循环中
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
#pragma endregion 

#pragma region globalInit
	readScore.open("recordScore.txt");
	readScore >> recordScore;
	
	gameState = GS_menuPlay;
	PmenuPlay.init("picture/gamestart.jpg",-1.0f,1.0f,2.0f,2.0f);
	PmenuExit.init("picture/gamequit.jpg", -1.0f, 1.0f, 2.0f, 2.0f);
	backMenu0.init("picture/回到菜单0.png", -0.3f, -0.3f, 0.7f, 0.3f);
	backMenu1.init("picture/回到菜单1.png", -0.3f, -0.3f, 0.7f, 0.3f);
	continue0.init("picture/继续游戏0.png", -0.3f, 0.3f, 0.7f, 0.3f);
	continue1.init("picture/继续游戏1.png", -0.3f, 0.3f, 0.7f, 0.3f);
	again0.init("picture/再来一局0.png", -0.3f, 0.3f, 0.7f, 0.3f);
	again1.init("picture/再来一局1.png", -0.3f, 0.3f, 0.7f, 0.3f);
	point.init("picture/point.png", -1.0f, 1.0f, 0.4f, 0.22f);
	record.init("picture/record.png", -1.0f, 1.0f, 0.4f, 0.22f);
	modelShader.init("model.vert", "model.frag");
	pictureShader.init("pictureShader.vert", "pictureShader.frag");
	myBoard.init("3d model/boardRed.obj");
	myBall.init("3d model/ballsan.obj");
	myBox.init("3d model/woodbox.obj");//因为代码问题box的init必须在ball后面
	myStar.init("3d model/pyramid.obj");
	myTunnel.init("3d model/tunnel5.obj");
	menuMusic.load("music/menumusic.mp3");
	playMusic.load("music/menumusic.mp3");
	numInit();
	//home.init("picture/supersonic.ppm", -1.0f, 1.0f, 2.0f, 2.0f);
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//以line的形式去画三角形
#pragma endregion
	glEnable(GL_DEPTH_TEST);
	mciSendString("play music/menumusic.mp3", NULL, 0, NULL);
	//开启深度测试，当图片重叠时，测试深度，选择表现的图片
	//--------render loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除深度缓冲和颜色缓冲
        processInput(window);
		//ourmodel.position = glm::mat4(1.0f);
		//ball.position = glm::mat4(1.0f);
		//ourmodel.position = glm::translate(ourmodel.position, glm::vec3(4.6f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		//ourmodel.position = glm::scale(ourmodel.position, glm::vec3(0.008f, 0.008f, 0.008f));	// it's a bit too big for our scene, so scale it down
		//ball.position = glm::translate(ball.position, glm::vec3(0.0f, 1.3f, 0.0f));
		//ball.position = glm::scale(ball.position, glm::vec3(0.001f, 0.001f, 0.001f));	// 
		
		gameSelector();
		
		//设置texture对应的位置
		
		//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(board.VAO);
		
		//ourmodel.Draw(modelShader);
		//modelShader.use();
		
		
		//ball.Draw(modelShader);
		//board.Draw(pictureShader);	
		//home.Draw(pictureShader);
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);//双缓冲
		glfwPollEvents();
	
		
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	float currentTime = glfwGetTime();
	deltaTime = currentTime - lastFrame;//每一帧的时间间隔
	lastFrame = currentTime;
	deltaTime *= Msensitity;
	
	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	//	glfwSetWindowShouldClose(window, true);
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	myCamera.ProcessKeyboard(FORWARD, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	myCamera.ProcessKeyboard(BACKWARD, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	myCamera.ProcessKeyboard(LEFT, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	myCamera.ProcessKeyboard(RIGHT, deltaTime);//使摄像机移动的
	//the vector must be normalize
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}//调整鼠标的位置为窗口中心

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	//myCamera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	myCamera.ProcessMouseScroll(yoffset);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS&&gameState==GS_playing)
	{
		myBall.setRightOrLeft(2);
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS&&gameState==GS_playing)
	{
		myBall.setRightOrLeft(1);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		if (gameState == GS_menuExit)
		{
			gameState = GS_menuPlay;
		}
		else if (gameState == GS_pauseReturn)
		{
			gameState = GS_pauseContinue;
		}
		else if (gameState == GS_overReturn)
		{
			gameState = GS_overAgain;
		}
		else if (gameState == GS_playing)
		{
			myBall.setJump(1);
		}
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		if (gameState == GS_menuPlay)
			gameState = GS_menuExit;
		if (gameState == GS_pauseContinue)
			gameState = GS_pauseReturn;
		if (gameState == GS_overAgain)
			gameState = GS_overReturn;
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
	{
		if (gameState == GS_menuPlay) {
			gameState = GS_playing;
			
			menuMusicStop();
			
		}
		if(gameState==GS_menuExit)
			glfwSetWindowShouldClose(window, true);
		if (gameState == GS_pauseContinue)
		{
			playMusicPlay();
			gameState = GS_playing;
		}
		if (gameState == GS_pauseReturn)
		{
			playMusicStop();
			menuMusicPlay();
			again();
			gameState = GS_menuPlay;
		}
		if (gameState == GS_overAgain)
		{
			playMusicStop();
			playMusicPlay();
			again();
			gameState = GS_playing;
		}
		if (gameState == GS_overReturn)
		{
			playMusicStop();
			menuMusicPlay();
			gameState = GS_menuPlay;
			again();
		}
		
	}
	if (key == GLFW_KEY_K && action == GLFW_PRESS)
	{
		if (gameState == GS_playing)
		{
			gameState = GS_pauseContinue;
			playMusicStop();

		}
	}
}

void mainGame()
{
	glm::mat4 view = myCamera.GetViewMatrix();
	modelShader.use();
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "view"), 1, GL_FALSE, &view[0][0]);
	myBoard.update();

	myBall.update();
	myBox.update();
	myTunnel.update();
	myStar.update();
	myBall.draw(modelShader);
	myBoard.draw(modelShader);
	myBox.draw(modelShader);
	myStar.draw(modelShader);
	myTunnel.draw(modelShader);
}

void gameSelector()
{
	switch (gameState)
	{
	case GS_menuPlay:
		//menuMusic.play();
		record.Draw(pictureShader);
		drawScore(recordScore);
		PmenuPlay.Draw(pictureShader);
		
		break;
	case GS_menuExit:
		drawScore(recordScore);
		record.Draw(pictureShader);
		PmenuExit.Draw(pictureShader);
		break;
	case GS_playing:
		drawScore(myStar.point);
		point.Draw(pictureShader);
		mainGame();
		
		if (newGame == 1)
		{
			mciSendString("play music/newgame.mp3", NULL, 0, NULL);
			Sleep(400);
			playMusicPlay();
			newGame--;
		}
		if (newGame >1)newGame--;
		break;
	case GS_pauseContinue:
		drawScore(myStar.point);
		point.Draw(pictureShader);
		myBall.draw(modelShader);
		myBoard.draw(modelShader);
		myBox.draw(modelShader);
		myStar.draw(modelShader);
		myTunnel.draw(modelShader);
		continue1.Draw(pictureShader);
		backMenu0.Draw(pictureShader);
		break;
	case GS_pauseReturn:
		drawScore(myStar.point);
		point.Draw(pictureShader);
		myBall.draw(modelShader);
		myBoard.draw(modelShader);
		myBox.draw(modelShader);
		myStar.draw(modelShader);
		myTunnel.draw(modelShader);
		continue0.Draw(pictureShader);
		backMenu1.Draw(pictureShader);
		break;
	case GS_overAgain:
		drawScore(myStar.point);
		point.Draw(pictureShader);
		myBall.draw(modelShader);
		myBoard.draw(modelShader);
		myBox.draw(modelShader);
		myStar.draw(modelShader);
		myTunnel.draw(modelShader);
		again1.Draw(pictureShader);
		backMenu0.Draw(pictureShader);
		break;
	case GS_overReturn:
		drawScore(myStar.point);
		point.Draw(pictureShader);
		myBall.draw(modelShader);
		myBoard.draw(modelShader);
		myBox.draw(modelShader);
		myStar.draw(modelShader);
		myTunnel.draw(modelShader);
		again0.Draw(pictureShader);
		backMenu1.Draw(pictureShader);
	
		
	}
	
}
/*unsigned int loadImageToGpu(const char * filename,int texturenum)
{
	unsigned int texBuffer;
	glGenTextures(1, &texBuffer);
	glActiveTexture(GL_TEXTURE0 + texturenum);
	glBindTexture(GL_TEXTURE_2D, texBuffer);
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	//这是因为OpenGL要求y轴0.0坐标是在图片的底部的，但是图片的y轴0.0坐标通常在顶部。
	//很幸运，stb_image.h能够在图像加载时帮助我们翻转y轴，只需要在加载任何图像前加入以下语句即可：
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
	if (data) {
		GLenum format;
		if (nrChannel == 1)format = GL_RED;
		if (nrChannel == 3)format = GL_RGB;
		if (nrChannel == 4)format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0,format, width, height, 0,format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);//设置多级渐远纹理
		//第二个参数为如果手动设置多个多级渐远纹理，就填0,第六个参数是历史遗留问题
	//第七八个参数是原图的格式和数据类型
	}
	else {
		std::cout << "fail to load texture" << std::endl;
	}
	stbi_image_free(data);
	return texBuffer;
}
*/
void again()
{
	newGame = 3;
	if (myStar.point > recordScore)
	{
		getScore.open("recordScore.txt");
		recordScore = myStar.point;
		getScore << recordScore;
	}
	myBoard.again();
	myBall.again();
	myBox.again();
	myStar.again();
	myTunnel.again();
}

void numInit()
{
	num[0].init("picture/0.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[1].init("picture/1.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[2].init("picture/2.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[3].init("picture/3.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[4].init("picture/4.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[5].init("picture/5.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[6].init("picture/6.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[7].init("picture/7.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[8].init("picture/8.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[9].init("picture/9.png", -0.36f, 1.0f, 0.15f, 0.22f );
	num[10].init("picture/0.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[11].init("picture/1.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[12].init("picture/2.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[13].init("picture/3.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[14].init("picture/4.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[15].init("picture/5.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[16].init("picture/6.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[17].init("picture/7.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[18].init("picture/8.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[19].init("picture/9.png", -0.48f, 1.0f, 0.15f, 0.22f );
	num[20].init("picture/0.png", -0.6f, 1.0f, 0.15f, 0.22f );
	num[21].init("picture/1.png", -0.6f, 1.0f, 0.15f, 0.22f );
	num[22].init("picture/2.png", -0.6f, 1.0f, 0.15f, 0.22f );
	num[23].init("picture/3.png", -0.6f, 1.0f, 0.15f, 0.22f );
	num[24].init("picture/4.png", -0.6f, 1.0f, 0.15f, 0.22f );
	num[25].init("picture/5.png", -0.6f, 1.0f, 0.15f, 0.22f );
	num[26].init("picture/6.png", -0.6f, 1.0f, 0.15f, 0.22f );
	num[27].init("picture/7.png", -0.6f, 1.0f, 0.15f, 0.22f );
	num[28].init("picture/8.png", -0.6f, 1.0f, 0.15f, 0.22f );
	num[29].init("picture/9.png", -0.6f, 1.0f, 0.15f, 0.22f );
}

void drawScore(int number) {
	
	int hund = (int)(number / 100);
	number %= 100;
	num[20 + hund].Draw(pictureShader);
	int ten = (int)(number / 10);
	num[10 + ten].Draw(pictureShader);
	num[number % 10].Draw(pictureShader);
}

void menuMusicStop()
{
	mciSendString("stop music/menumusic.mp3", NULL, 0, NULL);
}

void playMusicPlay()
{
	mciSendString("play music/gamemusic.mp3", NULL, 0, NULL);
}

void menuMusicPlay()
{
	mciSendString("play music/menumusic.mp3", NULL, 0, NULL);
}

void playMusicStop()
{
	mciSendString("stop music/gamemusic.mp3", NULL, 0, NULL);
}
