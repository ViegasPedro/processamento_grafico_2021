#include "Character.h"

Character::Character() {

}

Character::Character(float posX, float posY, float dimX, float dimY, int texID, Shader* shader) {
	sprite = new Sprite;
	sprite->setPosition(glm::vec3(posX, posY, 0.0));
	sprite->setDimension(glm::vec3(dimX, dimY, 1.0f));
	sprite->setShader(shader);
	sprite->setTexture(texID);
}

void Character::setSprite(float posX, float posY, float dimX, float dimY, int texID, Shader* shader) {
	sprite = new Sprite;
	sprite->setPosition(glm::vec3(posX, posY, 0.0));
	sprite->setDimension(glm::vec3(dimX, dimY, 1.0f));
	sprite->setShader(shader);
	sprite->setTexture(texID);
}

void Character::move(float x, float y) {
	sprite->setPosition(glm::vec3(x, y, 0.0));
}

void Character::draw() {
	sprite->update();
	sprite->draw();
}