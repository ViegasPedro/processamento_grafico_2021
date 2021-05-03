#include "Sprite.h"
#pragma once

class Shoot {
public:
	Shoot();
	~Shoot() {}
	Shoot(float posX, float posY, float dimX, float dimY, int texID, Shader* shader, float movementSpeed);

	void setSprite(float posX, float posY, float dimX, float dimY, int texID, Shader* shader);
	void move();
	void draw();
	void rotate();

	Sprite* sprite;
	float movementSpeed;
};
