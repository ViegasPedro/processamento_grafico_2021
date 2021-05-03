#pragma once

//Esta classe vai ir sofrendo alterações durante o curso
//Aqui ela está preparada apenas para sprites texturizados

#include "Shader.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sprite
{
public:
	Sprite();
	~Sprite() {}

	void initialize(); //similar ao setupGeometry

	//Para setar os atributos 
	void setTexture(int texID);
	void setShader(Shader* shader) { this->shader = shader; shader->Use(); }
	void setPosition(glm::vec3 pos) { this->pos = pos; } 
	void setDimension(glm::vec3 scale) { this->scale = scale; }
	void setAngle(float angle) { this->angle = angle; } //para 3D precisa angulo por eixo ou quaternion
	void setPositionX(float x) { this->pos[0] = x; }
	void setPositionY(float y) { this->pos[1] = y; }
	void setMovimentSpeed(float movimentSpeed) { this->movimentSpeed = movimentSpeed; }

	//getters
	float getPositionX() { return this->pos[0]; }
	float getPositionY() { return this->pos[1]; }
	float getDimensionX() { return this->scale[0]; }
	float getDimensionY() { return this->scale[1]; }
	float getMovimentSpeed() { return this->movimentSpeed; }

	//Para controle direto da matriz de transformações
	void setRotation(float angle, glm::vec3 axis, bool reset = true);
	void setTranslation(glm::vec3 displacements, bool reset = true);
	void setScale(glm::vec3 scaleFactors, bool reset = true);

	//Chamados no ciclo do SceneManager
	void draw();
	void update();

	//TO DO: métodos para animação

protected:
	//Atributos gerais

	GLuint VAO; //ID do buffer de geometria

	glm::mat4 transform; //matriz de transformação

	unsigned int texID; //identificador da textura

	Shader* shader; //ponteiro para o objeto de shader, para fazer a interface

	//Atributos de controle da posição, orientação e dimensões do sprite
	glm::vec3 pos, scale;
	float angle;

	//Atributos para controle da animação
	int nAnims, nFrames;
	int iAnim, iFrame; //indices da animação e frame atual

	float movimentSpeed;
};