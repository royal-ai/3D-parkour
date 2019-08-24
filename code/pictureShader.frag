#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_picture;

void main()
{    
    FragColor = texture(texture_picture, TexCoords);
	//FragColor=vec4(0.6f,0.6f,0.4f,1.0f);
}