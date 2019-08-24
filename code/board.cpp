#include"allheader.h"




Board::Board()
{
}


Board::~Board()
{
}

void Board::init(std::string const & path)
{
	modelA.init(path);
	modelB.init(path);
	posZA = 0.0f;
	posZB = -2*halfLength;
	work = true;
	//modelA.position = glm::translate(modelA.position, glm::vec3(0.0f, 0.0f, -1 * halfLength));
	//modelB.position = glm::translate(modelB.position, glm::vec3(0.0f, 0.0f, -3 * halfLength));
	//modelA.position = glm::scale(modelA.position, glm::vec3(0.008f, 0.008f, 0.008f));
	//modelB.position = glm::scale(modelB.position, glm::vec3(0.008f, 0.008f, 0.008f));


}

void Board::draw(shader shader)
{
	modelA.Draw(shader);
	modelB.Draw(shader);
}

void Board::update()
{
	if (work == true&&myCamera.Position.z<(posZA-halfLength))
	{
		posZA -= 4 * halfLength;
		//modelA.position = glm::translate(modelA.position, glm::vec3(0.0f, 0.0f, -2*halfLength));
		work = false;
	}
	if (work == false && myCamera.Position.z < (posZB-halfLength))
	{
		posZB -= 4 * halfLength;
		//modelB.position = glm::translate(modelA.position, glm::vec3(0.0f, 0.0f, -2*halfLength));
		work = true;
	}
	//std::cout << myCamera.Position.z << " " << posZA << " " << posZB << std::endl;
	modelA.position = glm::mat4(1.0f);
	modelB.position = glm::mat4(1.0f);
	modelA.position = glm::translate(modelA.position, glm::vec3(0.0f, 0.0f, posZA));
	modelB.position = glm::translate(modelB.position, glm::vec3(0.0f, 0.0f, posZB));
	modelA.position = glm::scale(modelA.position, glm::vec3(0.008f, 0.008f, 0.008f));
	modelB.position = glm::scale(modelB.position, glm::vec3(0.008f, 0.008f, 0.008f));
	
}

void Board::again()
{
	posZA = 0.0f;
	posZB = -2 * halfLength;
	work = true;
}
