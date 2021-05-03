#include "Sprite.h"

class Background {
public: 
	//construtores
	Background();
	~Background() {}
	Background(float posX, float posY, float dimX, float dimY, int texID, Shader* shader, float movementSpeed);

	//m�todos
	void move();
	void draw();

	//atributos
	Sprite* sprite;
	float movementSpeed;
};