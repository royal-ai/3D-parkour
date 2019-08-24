#include"allheader.h"




Tunnel::Tunnel()
{
}


Tunnel::~Tunnel()
{
}
void Tunnel::init(std::string const & path)
{
	modelA.init(path);
	modelB.init(path);
	posZA = 0.0f;
	posZB = -2 * halfTunnelLength;
	work = true;
	//modelA.position = glm::translate(modelA.position, glm::vec3(0.0f, 0.0f, -1 * halfLength));
	//modelB.position = glm::translate(modelB.position, glm::vec3(0.0f, 0.0f, -3 * halfLength));
	//modelA.position = glm::scale(modelA.position, glm::vec3(0.008f, 0.008f, 0.008f));
	//modelB.position = glm::scale(modelB.position, glm::vec3(0.008f, 0.008f, 0.008f));
}
void Tunnel::draw(shader shader)
{
	modelA.Draw(shader);
	modelB.Draw(shader);
}
void Tunnel::update()
{
	if (work == true && myCamera.Position.z < (posZA - halfTunnelLength))
	{
		posZA -= 4 * halfTunnelLength;
		//modelA.position = glm::translate(modelA.position, glm::vec3(0.0f, 0.0f, -2*halfLength));
		work = false;
	}
	if (work == false && myCamera.Position.z < (posZB - halfTunnelLength))
	{
		posZB -= 4 * halfTunnelLength;
		//modelB.position = glm::translate(modelA.position, glm::vec3(0.0f, 0.0f, -2*halfLength));
		work = true;
	}
	//std::cout << myCamera.Position.z << " " << posZA << " " << posZB << std::endl;
	modelA.position = glm::mat4(1.0f);
	modelB.position = glm::mat4(1.0f);
	modelA.position = glm::translate(modelA.position, glm::vec3(0.0f, 0.0f, posZA));
	modelB.position = glm::translate(modelB.position, glm::vec3(0.0f, 0.0f, posZB));
	modelA.position = glm::scale(modelA.position, glm::vec3(5.0f, 5.0f, 5.0f));
	modelB.position = glm::scale(modelB.position, glm::vec3(5.0f, 5.0f, 5.0f));

}

void Tunnel::again()
{
	posZA = 0.0f;
	posZB = -2 * halfTunnelLength;
	work = true;
}
