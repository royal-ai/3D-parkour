#version 330 core
layout (location = 0) in vec3 aPos;
layout (location =1) in vec3 aNormal;
layout (location=2) in vec2 aTexCoords;
//layout (location =1)  in vec3 aColor;
//layout (location=2)   in vec2 aTexCoord;
out vec3 ourColor;
out vec3 ourPosition;
out vec2 TexCoords;
out vec3 normal;
uniform mat4 model;
uniform mat4 transform;
out vec3 fragPos;
void main()
{  
   gl_Position = transform*vec4(aPos.x,aPos.y, aPos.z, 1.0);
   // ourColor = aColor;
   //ourPosition=aPos;
   ///TexCoord=aTexCoord;
   normal=mat3(transpose(inverse(model)))*aNormal;
   //尽量避免在着色器中使用逆矩阵运算，逆矩阵运算非常耗时。
   fragPos=vec3(model*vec4(aPos,1.0));
   //片段的位置
   TexCoords=aTexCoords;
}
