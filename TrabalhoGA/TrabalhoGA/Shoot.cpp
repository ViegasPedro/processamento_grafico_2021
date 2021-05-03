#include "Shoot.h"

Shoot::Shoot() {

}

Shoot::Shoot(float posX, float posY, float dimX, float dimY, int texID, Shader* shader, float movementSpeed) {
	sprite = new Sprite;
	sprite->setPosition(glm::vec3(posX, posY, 0.0));
	sprite->setDimension(glm::vec3(dimX, dimY, 1.0f));
	sprite->setShader(shader);
	sprite->setTexture(texID);

	this->movementSpeed = movementSpeed;
}

void Shoot::setSprite(float posX, float posY, float dimX, float dimY, int texID, Shader* shader) {
	sprite = new Sprite;
	sprite->setPosition(glm::vec3(posX, posY, 0.0));
	sprite->setDimension(glm::vec3(dimX, dimY, 1.0f));
	sprite->setShader(shader);
	sprite->setTexture(texID);
}

void Shoot::move() {
	float shootY = sprite->getPositionY();
	if (shootY > -50.0f) {
		sprite->setPositionY(shootY - movementSpeed);
	}

}

void Shoot::draw() {
	sprite->update();
	sprite->draw();
}

void Shoot::rotate() {
	sprite->setAngle((float)glfwGetTime());
}