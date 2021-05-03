#include "Sprite.h"

class Character {
public:
	Character();
	~Character() {}
	Character(float posX, float posY, float dimX, float dimY, int texID, Shader* shader);

	void setSprite(float posX, float posY, float dimX, float dimY, int texID, Shader* shader);
	void move(float x, float y);
	void draw();

	Sprite* sprite;
	float const movementSpeedX = 20.0f;
	float const movementSpeedY = 10.0f;
	int contFramesParado;
};
