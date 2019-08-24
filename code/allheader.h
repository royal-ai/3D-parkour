#pragma once
#include <stdio.h>
#include <Windows.h>
#include "mmsystem.h"      
#pragma comment(lib,"winmm.lib")
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"shader.h"
#include "camera.h"
#include"picture.h"
#include"ball.h"
#include"board.h"
#include"Obstacle.h"
#include"Star.h"
#include"tunnel.h"
#include "AudioClip.h"
#pragma  region global variables 
extern const unsigned int SCR_WIDTH ;
extern const unsigned int SCR_HEIGHT;
extern  Ball myBall;
extern Camera myCamera;
extern Board myBoard;
extern Obstacle myBox;
extern Star myStar;
extern Model sky;
extern Tunnel myTunnel;
extern float lastX;
extern float lastY;
extern bool firstMouse;
extern float deltaTime; // 当前帧与上一帧的时间差
extern float lastFrame ; // 上一帧的时间
extern glm::mat4 projection;//透视矩阵
extern float Msensitity;
extern AudioClip eatMusic;
extern shader modelShader;
extern shader pictureShader;
extern picture PmenuPlay;
extern picture PmenuExit;
extern picture backMenu0;
extern picture backMenu1;
extern picture continue0;
extern picture continue1;
extern picture again0;
extern picture again1;
extern picture point;
extern picture record;
extern picture num[30];
extern AudioClip menuMusic;
extern AudioClip playMusic;
extern int recordScore;
extern int gameState;
const int GS_menuPlay = 31;
const int GS_menuExit = 32;
const int GS_pauseReturn = 33;
const int GS_pauseContinue = 34;
const int GS_overAgain = 35;
const int GS_overReturn = 36;
const int GS_playing = 37;
bool crashTest(glm::vec3 a, glm::vec3 b,float xOffset,float yOffset,float zOffset);

# pragma endregion
