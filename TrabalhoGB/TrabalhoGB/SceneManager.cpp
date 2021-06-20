#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;
double mouseX = 0, mouseY = 0;
int imageFilter = 5;

bool createSticker1 = false, moveSticker1 = false;
double sticker1X = 100, sticker1Y = 450;

bool createSticker2 = false, moveSticker2 = false;
double sticker2X = 200, sticker2Y = 450;

bool createSticker3 = false, moveSticker3 = false;
double sticker3X = 300, sticker3Y = 450;

bool createSticker4 = false, moveSticker4 = false;
double sticker4X = 400, sticker4Y = 450;

bool createSticker5 = false, moveSticker5 = false;
double sticker5X = 500, sticker5Y = 450;


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
	glfwSetCursorPosCallback(window, cursorPositionCallback); 
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

	//Setando a callback de redimensionamento da janela
	glfwSetWindowSizeCallback(window, resize);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}
	
	// Build and compile our shader program
	addShader("transformation.vs", "binarizacao.frag");
	addShader("transformation.vs", "colorizacao.frag");
	addShader("transformation.vs", "grayscale.frag");
	addShader("transformation.vs", "inversao.frag");
	addShader("transformation.vs", "grayscaleinvertido.frag");
	addShader("transformation.vs", "transformation.frag");
	addShader("transformation.vs", "colorizacao.frag");

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez

	
}

void SceneManager::addShader(string vFilename, string fFilename)
{
	Shader* shader = new Shader(vFilename.c_str(), fFilename.c_str());
	shaders.push_back(shader);
}

void SceneManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
	if (moveSticker1) {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (sticker1X <= 730) {
				sticker1X += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (sticker1X >= 60) {
				sticker1X -= 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (sticker1Y <= 800.0f) {
				sticker1Y += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (sticker1Y >= 60.0f) {
				sticker1Y -= 10.0f;
			}
		}
	}else if (moveSticker2) {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (sticker2X <= 730) {
				sticker2X += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (sticker2X >= 60) {
				sticker2X -= 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (sticker2Y <= 800.0f) {
				sticker2Y += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (sticker2Y >= 60.0f) {
				sticker2Y -= 10.0f;
			}
		}
	}else if (moveSticker3) {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (sticker3X <= 730) {
				sticker3X += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (sticker3X >= 60) {
				sticker3X -= 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (sticker3Y <= 800.0f) {
				sticker3Y += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (sticker3Y >= 60.0f) {
				sticker3Y -= 10.0f;
			}
		}
	}else if (moveSticker4) {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (sticker4X <= 730) {
				sticker4X += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (sticker4X >= 60) {
				sticker4X -= 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (sticker4Y <= 800.0f) {
				sticker4Y += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (sticker4Y >= 60.0f) {
				sticker4Y -= 10.0f;
			}
		}
	}
	else if (moveSticker5) {
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (sticker5X <= 730) {
				sticker5X += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (sticker5X >= 60) {
				sticker5X -= 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (sticker5Y <= 800.0f) {
				sticker5Y += 10.0f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (sticker5Y >= 60.0f) {
				sticker5Y -= 10.0f;
			}
		}
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

	if (imageFilter == 5) {
		objects[5]->setShader(shaders[5]);
	}else if (imageFilter == 0) {
		objects[5]->setShader(shaders[0]);
	}else if (imageFilter == 1) {
		objects[5]->setShader(shaders[1]);
	}else if (imageFilter == 2) {
		objects[5]->setShader(shaders[2]);
	}else if (imageFilter == 3) {
		objects[5]->setShader(shaders[3]);
	}else if (imageFilter == 4) {
		objects[5]->setShader(shaders[4]);
	}else if (imageFilter == 6) {
		objects[5]->setShader(shaders[6]);
	}

	if (createSticker1 && sticker1 == NULL) {
		unsigned int texID = loadTexture("unnamed.png");
		Sprite* obj = new Sprite;
		obj->setPosition(glm::vec3(sticker1X, sticker1Y, 0.0));
		obj->setDimension(glm::vec3(100.0f, 50.0f, 1.0f));
		obj->setShader(shaders[5]);
		obj->setTexture(texID);
		sticker1 = obj;
	}
	else if (sticker1 != NULL) {
		sticker1->setPosition(glm::vec3(sticker1X, sticker1Y, 0.0));
		if (moveSticker1)
			sticker1->setShader(shaders[2]);
		else 
			sticker1->setShader(shaders[5]);
	}

	if (createSticker2 && sticker2 == NULL) {
		Sprite* obj = new Sprite;
		obj->setPosition(glm::vec3(sticker2X, sticker2Y, 0.0));
		obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
		obj->setShader(shaders[5]);
		obj->setTexture(loadTexture("uni.gif"));
		sticker2 = obj;
	}
	else if (sticker2 != NULL) {
		sticker2->setPosition(glm::vec3(sticker2X, sticker2Y, 0.0));
		if (moveSticker2)
			sticker2->setShader(shaders[2]);
		else
			sticker2->setShader(shaders[5]);
	}

	if (createSticker3 && sticker3 == NULL) {
		Sprite* obj = new Sprite;
		obj->setPosition(glm::vec3(sticker3X, sticker3Y, 0.0));
		obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
		obj->setShader(shaders[5]);
		obj->setTexture(loadTexture("wow.png"));
		sticker3 = obj;
	}
	else if (sticker3 != NULL) {
		sticker3->setPosition(glm::vec3(sticker3X, sticker3Y, 0.0));
		if (moveSticker3)
			sticker3->setShader(shaders[2]);
		else
			sticker3->setShader(shaders[5]);
	}

	if (createSticker4 && sticker4 == NULL) {
		unsigned int lenaTexID = loadTexture("coelho.png");
		Sprite* obj = new Sprite;
		obj->setPosition(glm::vec3(sticker4X, sticker4Y, 0.0));
		obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
		obj->setShader(shaders[5]);
		obj->setTexture(lenaTexID);
		sticker4 = obj;
	}
	else if (sticker4 != NULL) {
		sticker4->setPosition(glm::vec3(sticker4X, sticker4Y, 0.0));
		if (moveSticker4)
			sticker4->setShader(shaders[2]);
		else
			sticker4->setShader(shaders[5]);
	}

	if (createSticker5 && sticker5 == NULL) {
		unsigned int lenaTexID = loadTexture("cigarro.png");
		Sprite* obj = new Sprite;
		obj->setPosition(glm::vec3(sticker5X, sticker5Y, 0.0));
		obj->setDimension(glm::vec3(80.0f, 40.0f, 1.0f));
		obj->setShader(shaders[5]);
		obj->setTexture(lenaTexID);
		sticker5 = obj;
	}
	else if (sticker5 != NULL) {
		sticker5->setPosition(glm::vec3(sticker5X, sticker5Y, 0.0));
		if (moveSticker5)
			sticker5->setShader(shaders[2]);
		else
			sticker5->setShader(shaders[5]);
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

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update();
		objects[i]->draw();
	}

	if (sticker1 != NULL) {
		sticker1->update();
		sticker1->draw();
	}
	if (sticker2 != NULL) {
		sticker2->update();
		sticker2->draw();
	}
	if (sticker3 != NULL) {
		sticker3->update();
		sticker3->draw();
	}
	if (sticker4 != NULL) {
		sticker4->update();
		sticker4->draw();
	}
	if (sticker5 != NULL) {
		sticker5->update();
		sticker5->draw();
	}


}

void SceneManager::run()
{
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		glfwGetCursorPos(window, &mouseX, &mouseY);
		//Update method(s)
		update();

		//Render scene
		render();

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

void SceneManager::finish()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

void SceneManager::setupScene()
{
	//Criação dos Sprites iniciais -- pode-se fazer métodos de criação posteriormente
	unsigned int lenaTexID = loadTexture("lena.jpg");
	unsigned int sunglassesTexID = loadTexture("unnamed.png");
	unsigned int uniTexID = loadTexture("uni.gif"); 
	unsigned int wowTexID = loadTexture("wow.png");
	unsigned int coelhoTexID = loadTexture("coelho.png");
	unsigned int cigarroTexID = loadTexture("cigarro.png");
	//Mínimo: posicao e escala e ponteiro para o shader
	Sprite* obj = new Sprite;
	obj->setPosition(glm::vec3(100.0f, 70.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 100.0f, 1.0f));
	obj->setShader(shaders[0]);
	obj->setTexture(lenaTexID);
	objects.push_back(obj); 
	shaders[0]->setInt("limiar", 90);

	obj = new Sprite;
	obj->setPosition(glm::vec3(200.0f, 70.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 100.0f, 1.0f));
	obj->setShader(shaders[1]);
	obj->setTexture(lenaTexID);
	objects.push_back(obj); 
	shaders[1]->setVec3("corColorizadora", 0.5, 0.65, 0.5);
	
	obj = new Sprite;
	obj->setPosition(glm::vec3(300.0f, 70.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 100.0f, 1.0f));
	obj->setShader(shaders[2]);
	obj->setTexture(lenaTexID);
	objects.push_back(obj); 

	obj = new Sprite;
	obj->setPosition(glm::vec3(400.0f, 70.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 100.0f, 1.0f));
	obj->setShader(shaders[3]);
	obj->setTexture(lenaTexID);
	objects.push_back(obj); 

	obj = new Sprite;
	obj->setPosition(glm::vec3(500.0f, 70.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 100.0f, 1.0f));
	obj->setShader(shaders[4]);
	obj->setTexture(lenaTexID);
	objects.push_back(obj); 

	obj = new Sprite;
	obj->setPosition(glm::vec3(400.0f, 300.0f, 0.0));
	obj->setDimension(glm::vec3(300.0f, 300.0f, 1.0f));
	obj->setShader(shaders[5]);
	obj->setTexture(lenaTexID);
	objects.push_back(obj);

	obj = new Sprite;
	obj->setPosition(glm::vec3(600.0f, 70.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 100.0f, 1.0f));
	obj->setShader(shaders[5]);
	obj->setTexture(lenaTexID);
	objects.push_back(obj);

	obj = new Sprite;
	obj->setPosition(glm::vec3(700.0f, 70.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 100.0f, 1.0f));
	obj->setShader(shaders[6]);
	obj->setTexture(lenaTexID);
	shaders[1]->setVec3("corColorizadora", 0.65, 0.5, 0.5);
	objects.push_back(obj);

	obj = new Sprite;
	obj->setPosition(glm::vec3(100.0f, 550.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 50.0f, 1.0f));
	obj->setShader(shaders[5]);
	obj->setTexture(sunglassesTexID);
	objects.push_back(obj);

	obj = new Sprite;
	obj->setPosition(glm::vec3(200.0f, 550.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
	obj->setShader(shaders[5]);
	obj->setTexture(uniTexID);
	objects.push_back(obj);

	obj = new Sprite;
	obj->setPosition(glm::vec3(300.0f, 550.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	obj->setShader(shaders[5]);
	obj->setTexture(wowTexID);
	objects.push_back(obj);

	obj = new Sprite;
	obj->setPosition(glm::vec3(400.0f, 550.0f, 0.0));
	obj->setDimension(glm::vec3(50.0f, 50.0f, 1.0f));
	obj->setShader(shaders[5]);
	obj->setTexture(coelhoTexID);
	objects.push_back(obj);

	obj = new Sprite;
	obj->setPosition(glm::vec3(500.0f, 550.0f, 0.0));
	obj->setDimension(glm::vec3(80.0f, 40.0f, 1.0f));
	obj->setShader(shaders[5]);
	obj->setTexture(cigarroTexID);
	objects.push_back(obj);
	
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


	for (int i = 0; i < shaders.size(); i++)
	{
		shaders[i]->Use();
		GLint projLoc = glGetUniformLocation(shaders[i]->ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}
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

void SceneManager::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	//std::cout << xpos << " : " << ypos << std::endl;
}

void SceneManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//click nos filtros
		if (mouseX >= 75 && mouseX <= 125 &&
			mouseY >= 480 && mouseY <= 580) {
			imageFilter = 0;
		}else if (mouseX >= 175 && mouseX <= 225 &&
			mouseY >= 480 && mouseY <= 580) {
			imageFilter = 1;
		}else if (mouseX >= 275 && mouseX <= 325 &&
			mouseY >= 480 && mouseY <= 580) {
			imageFilter = 2;
		}else if (mouseX >= 375 && mouseX <= 425 &&
			mouseY >= 480 && mouseY <= 580) {
			imageFilter = 3;
		}else if (mouseX >= 475 && mouseX <= 525 &&
			mouseY >= 480 && mouseY <= 580) {
			imageFilter = 4;
		}else if (mouseX >= 575 && mouseX <= 625 &&
			mouseY >= 480 && mouseY <= 580) {
			imageFilter = 5;
		}else if (mouseX >= 675 && mouseX <= 725 &&
			mouseY >= 480 && mouseY <= 580) {
			imageFilter = 6;
		}
		//click nos stickers
		else if (mouseX >= 45 && mouseX <= 150 &&
			mouseY >= 28 && mouseY <= 70) {
			createSticker1 = true;
			moveSticker1 = !moveSticker1;
		}else if (mouseX >= 173 && mouseX <= 229 &&
			mouseY >= 17 && mouseY <= 79) {
			createSticker2 = true;
			moveSticker2 = !moveSticker2;
		}else if (mouseX >= 244 && mouseX <= 354 &&
			mouseY >= 7 && mouseY <= 91) {
			createSticker3 = true;
			moveSticker3 = !moveSticker3;
		}else if (mouseX >= 366 && mouseX <= 430 &&
			mouseY >= 22 && mouseY <= 74) {
			createSticker4 = true;
			moveSticker4 = !moveSticker4;
		}else if (mouseX >= 450 && mouseX <= 542 &&
			mouseY >= 20 && mouseY <= 70) {
			createSticker5 = true;
			moveSticker5 = !moveSticker5;
		}
		
	}
}
