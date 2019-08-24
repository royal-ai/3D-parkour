#pragma once
#include<glad/glad.h>
#include<fstream>
#include<fstream>
#include<sstream>
#include<iostream>
class shader
{
public:
	unsigned int ID;
	//≥Ã–ÚID
	shader()
	{

	}
	void init(const GLchar* vertexPath,const GLchar* fragmentPath );
	void use();
	void setBool(const std::string &name,bool value)const;
	void setInt(const std::string &name, int value)const;
	void setFloat(const std::string &name, float value)const;
	
private:
	void checkCompileErrors(GLuint shader, std::string type);

};

