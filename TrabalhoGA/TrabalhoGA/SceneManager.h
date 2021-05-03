#pragma once

#include "Shader.h"
#include "Sprite.h"
#include "Character.h"
#include "Doctor.h"
#include "Shoot.h"
#include "Background.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

enum GameStatus {
	ACTIVE,
	GAME_OVER,
	MENU
};

using namespace std;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	GameStatus status;

	//GLFW callbacks - PRECISAM SER EST�TICAS
	//Para isso, as vari�veis que modificamos dentro deles
	//tamb�m precisam ser e est�o no in�cio do SceneManager.cpp
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void resize(GLFWwindow* window, int width, int height);

	//M�todos pricipais
	void initialize(GLuint width, GLuint height);
	void run();
	void finish();

	//M�todos chamados no run (ciclo)
	void update();
	void render();
	void renderGameOverOrMenu(GameStatus status);

	//M�todos para configura��o e carregamento dos elementos da cena
	void initializeGraphics();
	void addShader(string vFilename, string fFilename);
	void setupScene(); //antigo setupGeometry
	void setupCamera2D();
	unsigned int loadTexture(string filename);
	void createNewDoctor(int level);
	void checkColision(Shoot* shot);

private:

	//Janela GLFW (por enquanto, assumimos apenas 1 inst�ncia)
	GLFWwindow* window;

	//Programa de shader (por enquanto, assumimos apenas 1 inst�ncia)
	Shader* shader;

	//C�mera 2D - Matriz de proje��o (ortogr�fica) com os limites em x,y
	glm::vec4 ortho2D; //xmin, xmax, ymin, ymax
	glm::mat4 projection;

	//Nossos objetos (sprites) da cena
	vector <Background*> backgrounds;
	vector <Shoot*> shots;
	vector <Doctor*> doctors;
	Character* character;

};