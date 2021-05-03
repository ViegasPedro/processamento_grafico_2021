#include "Background.h"

#include <stdio.h>
#include <iostream>
Background::Background() {

}

Background::Background(float posX, float posY, float dimX, float dimY, int texID, Shader* shader, float movementSpeed) {
	sprite = new Sprite;
	sprite->setPosition(glm::vec3(posX, posY, 0.0));
	sprite->setDimension(glm::vec3(dimX, dimY, 1.0f));
	sprite->setShader(shader);
	sprite->setTexture(texID);

	this->movementSpeed = movementSpeed;
}

void Background::move() {
	float posX = sprite->getPositionX();
	sprite->setPositionX(posX - movementSpeed);
	if (sprite->getPositionX() <= -450) {
		//std::cout << "hitou" << std::endl;
		sprite->setPositionX(1250.0f);
	}
}

void Background::draw() {
	sprite->update();
	sprite->draw();
}