#include "SceneManager.h"
#include <iostream>
#include <chrono>
#include <ctime> 
#include <stdio.h>
#include <thread>

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;

float characterX = 50.0f, characterY = 100.0f;
double gameStart;
double lastDoctorSpawn;
bool isGameRunning= false;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize(GLuint w, GLuint h)
{
	width = w;
	height = h;

	// GLFW - GLEW - OPENGL general setup -- TODO: config file
	initializeGraphics();

}

void SceneManager::initializeGraphics()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, "Hello Sprites", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	//Setando a callback de redimensionamento da janela
	glfwSetWindowSizeCallback(window, resize);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Build and compile our shader program
	addShader("transformations.vs", "transformations.frag");

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez

}

void SceneManager::addShader(string vFilename, string fFilename)
{
	shader = new Shader(vFilename.c_str(), fFilename.c_str());
}

void SceneManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if (characterX <= 730) {
			characterX += 20.0f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		//cout << "\n Esquerda: ";
		//cout << characterX;
		if (characterX >= 60) {
			characterX -= 20.0f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (characterY <= 120.0f) {
			characterY += 10.0f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (characterY >= 60.0f) {
			characterY -= 10.0f;
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		isGameRunning = true;
	}
}

void SceneManager::resize(GLFWwindow* window, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
}

void SceneManager::update()
{
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);

	//AQUI aplicaremos as transformações nos sprites

	//movimentação do personagem
	if (characterX > character->sprite->getPositionX()) {
		character->sprite->setTexture(loadTexture("bolso_direita.png"));
		character->contFramesParado = 0;
	}
	else if (characterX < character->sprite->getPositionX()) {
		character->sprite->setTexture(loadTexture("bolso_esquerda.png"));
		character->contFramesParado = 0;
	}
	else {
		if (character->contFramesParado == 30)
			character->sprite->setTexture(loadTexture("bolso.png"));
		else
			character->contFramesParado++;
	}
	character->move(characterX, characterY);

	//movimentação do cenario
	for (int i = 0; i < backgrounds.size(); i++) {
		backgrounds[i]->move();
	}

	//atualiza os médicos
	for (int i = 0; i < doctors.size(); i++) {
		doctors[i]->move(characterX, characterY);
		if (doctors[i]->needShoot(glfwGetTime() - gameStart))
			shots.push_back(doctors[i]->shoot(loadTexture("vacina.png"), shader, glfwGetTime() - gameStart));
	}

	//movimenta os tiros
	for (int i = 0; i < shots.size(); i++) {
		shots[i]->rotate();
		shots[i]->move();
		checkColision(shots[i]);
	}

	//cria um novo médico
	if (doctors.size() < 3) {
		// cout << "numero docs:  " << doctors.size() << std::endl;
		this->createNewDoctor(doctors.size());
	}

}

void SceneManager::render()
{
	// Clear the colorbuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (resized) //se houve redimensionamento na janela, redefine a projection matrix
	{
		setupCamera2D();
		resized = false;
	}

	//atualiza e desenha os Sprites
	//atualiza o fundo da cena
	for (int i = 0; i < backgrounds.size(); i++){
		backgrounds[i]->draw();
	}
	//atualiza o desenho dos médicos
	for (int i = 0; i < doctors.size(); i++){
		doctors[i]->draw();
	}
	//atualiza o desenho dos tiros
	for (int i = 0; i < shots.size(); i++){
		shots[i]->draw();
	}
	//atualiza o desenho do personagem principal
	character->draw();

}

void SceneManager::renderGameOverOrMenu(GameStatus status) {
	// Clear the colorbuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (resized) {
		setupCamera2D();
		resized = false;
	}
	Sprite* gameOver = new Sprite();
	gameOver->setPosition(glm::vec3(400, 300, 0.0));
	gameOver->setDimension(glm::vec3(800, 600, 1.0f));
	gameOver->setShader(shader);
	if(status == MENU)
		gameOver->setTexture(loadTexture("menu.png"));
	else 
		gameOver->setTexture(loadTexture("gameover2.png"));
	gameOver->update();
	gameOver->draw();
	glfwSwapBuffers(window);
}

void SceneManager::run()
{
	gameStart = glfwGetTime();
	lastDoctorSpawn = gameStart;
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		if (!isGameRunning) {
			renderGameOverOrMenu(MENU);
			this_thread::sleep_for(chrono::milliseconds(500));
			continue;
		}
		status = ACTIVE;

		double startFrameTime = glfwGetTime();
		//Update method(s)
		update();

		//Render scene
		render();

		// Swap the screen buffers
		glfwSwapBuffers(window);

		double current_seconds = glfwGetTime();
		double elapsed_seconds = current_seconds - startFrameTime;
		startFrameTime = current_seconds;
		int d = 1000 / 60 - elapsed_seconds;
		this_thread::sleep_for(chrono::milliseconds(d));

		if (status == GAME_OVER) {
			this_thread::sleep_for(chrono::milliseconds(2000));
			renderGameOverOrMenu(GAME_OVER);
			this_thread::sleep_for(chrono::milliseconds(5000));
			break;
		}
	}
}

void SceneManager::finish()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

void SceneManager::setupScene()
{
	Sprite* obj = new Sprite;
	//cenario
	//backgrounds.push_back(new Background(450.0f, 210.0f, 900.0f, 420.0f, loadTexture("_01_ground.png"), shader,0.0f));
	//cenario
	//backgrounds.push_back(new Background(450.0f, 390.0f, 900.0f, 600.0f, loadTexture("_02_trees and bushes.png"), shader, 0.05f));
	//cenario
	//backgrounds.push_back(new Background(450.0f, 390.0f, 900.0f, 600.0f, loadTexture("_03_distant_trees.png"), shader, 0.0f));
	backgrounds.push_back(new Background(450.0f, 300.0f, 900.0f, 600.0f, loadTexture("sky.png"), shader, 0.0f));
	backgrounds.push_back(new Background(450.0f, 300.0f, 900.0f, 600.0f, loadTexture("city.png"), shader, 2.0f));
	backgrounds.push_back(new Background(1250.0f, 300.0f, 900.0f, 600.0f, loadTexture("city.png"), shader, 2.0f));
	//personagem
	character = new Character(100.0f, 100.0f, 75.0f, 75.0f, loadTexture("bolso.png"), shader);
	//medico
	doctors.push_back(new Doctor(100.0f, 520.0f, 150.0f, 160.0f, loadTexture("medico.png"),shader, 1.0f, 1.0f, 3));


	//Definindo a janela do mundo (ortho2D)
	ortho2D[0] = 0.0f; //xMin
	ortho2D[1] = 800.0f; //xMax
	ortho2D[2] = 0.0f; //yMin
	ortho2D[3] = 600.0f; //yMax

	//Habilita transparência
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void SceneManager::setupCamera2D() //TO DO: parametrizar aqui
{
	float zNear = -1.0, zFar = 1.0; //estão fixos porque não precisamos mudar

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);


	//Obtendo o identificador da matriz de projeção para enviar para o shader
	GLint projLoc = glGetUniformLocation(shader->ID, "projection");
	//Enviando a matriz de projeção para o shader
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

unsigned int SceneManager::loadTexture(string filename)
{
	unsigned int texture;

	// load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;

	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	glActiveTexture(GL_TEXTURE0);

	return texture;
}

void SceneManager::createNewDoctor(int level) {
	double elapsed_seconds = glfwGetTime() - lastDoctorSpawn;
	if (elapsed_seconds >= 15.0 && doctors.size() < 3) {
		doctors.push_back(new Doctor(100.0f, 520.0f, 150.0f, 160.0f, loadTexture("medico.png"), shader, level == 1 ? 2.0f : 3.0f, level == 1 ? 2.0f : 3.0f, level == 1 ? 2: 1));
		lastDoctorSpawn = glfwGetTime();		
	}
}

void SceneManager::checkColision(Shoot* shot) {
	//testa se houve colisão em X
	bool hitX = shot->sprite->getPositionX() + shot->sprite->getDimensionX() >= character->sprite->getPositionX()
		&& character->sprite->getPositionX() + character->sprite->getDimensionX() >= shot->sprite->getPositionX();
	//testa se houve colisão em Y
	bool hitY = shot->sprite->getPositionY() + shot->sprite->getDimensionY() >= character->sprite->getPositionY()
		&& character->sprite->getPositionY() + character->sprite->getDimensionY() >= shot->sprite->getPositionY();
	
	if (hitX && hitY) {
		//std::cout << "hitou" << std::endl;
		character->sprite->setTexture(loadTexture("jacare2.png"));
		character->sprite->setDimension(glm::vec3(200.0f,200.0f,0.0f));
		status = GAME_OVER;
	}
		
}