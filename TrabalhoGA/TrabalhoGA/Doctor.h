#include "Sprite.h"
#include "Shoot.h"

class Doctor {
public:
	//construtores
	Doctor();
	~Doctor() {}
	Doctor(float posX, float posY, float dimX, float dimY, int texID, Shader* shader, float movementSpeed, float shootingSpeed, int shootDelay);

	//setters
	void setSprite(float posX, float posY, float dimX, float dimY, int texID, Shader* shader);

	//m�todos especificos
	void move(float characterX, float characterY);
	void draw();
	bool needShoot( double currentGameTime);
	Shoot* shoot(int textureId, Shader* shader, double currentGameTime);

	//atributos
	//distancia de deslocamento do m�dico
	float movementSpeed;
	//distancia do deslocamento do tiro
	float shootingSpeed;
	Sprite* sprite;
	//time do �ltimo tiro efetuado
	double lastShootTime;
	//tempo de espera entre os tiros
	int shootDelay;
};