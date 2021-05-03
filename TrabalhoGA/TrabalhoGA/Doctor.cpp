#include "Doctor.h"


Doctor::Doctor() {

}

Doctor::Doctor(float posX, float posY, float dimX, float dimY, int texID, Shader* shader, float movementSpeed, float shootingSpeed, int shootDelay) {
	sprite = new Sprite;
	sprite->setPosition(glm::vec3(posX, posY, 0.0));
	sprite->setDimension(glm::vec3(dimX, dimY, 1.0f));
	sprite->setShader(shader);
	sprite->setTexture(texID);

	this->movementSpeed = movementSpeed;
	this->shootingSpeed = shootingSpeed;
	this->shootDelay = shootDelay;
}

void Doctor::setSprite(float posX, float posY, float dimX, float dimY, int texID, Shader* shader) {
	sprite = new Sprite;
	sprite->setPosition(glm::vec3(posX, posY, 0.0));
	sprite->setDimension(glm::vec3(dimX, dimY, 1.0f));
	sprite->setShader(shader);
	sprite->setTexture(texID);
}

void Doctor::move(float characterX, float characterY) {
	float x = sprite->getPositionX();
	float y = sprite->getPositionY();
	if (characterX < x) {
		sprite->setPosition(glm::vec3(x -= movementSpeed, y, 0.0));
	}
	if (characterX > x) {
		sprite->setPosition(glm::vec3(x += movementSpeed, y, 0.0));
	}
}

void Doctor::draw() {
	sprite->update();
	sprite->draw();
}
/*
Shoot* Doctor::shoot(int textureId, Shader* shader) {
	Shoot* shoot = new Shoot(sprite->getPositionX(), sprite->getPositionY() - 50.0f, 50.0f, 50.0f, textureId, shader, shootingSpeed);
	return shoot;
}*/
bool Doctor::needShoot(double currentGameTime) {
	return (int)currentGameTime - (int)lastShootTime >= shootDelay;
}
Shoot* Doctor::shoot(int textureId, Shader* shader, double currentGameTime) {
	lastShootTime = currentGameTime;
	return new Shoot(sprite->getPositionX(), sprite->getPositionY() - 50.0f, 50.0f, 50.0f, textureId, shader, shootingSpeed);
}
