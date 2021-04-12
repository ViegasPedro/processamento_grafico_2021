/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr'afico - Jogos Digitais - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 15/08/2020
 *
 */

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
int setupShader();
int setupGeometryHouse();
int setupGeometryChao();
int setupGeometryHouse2();
int setupGeometryTelhado();
int setupGeometryTelhado2();
int setupGeometryPorta();
void whileExercicio7(GLuint shaderID, GLuint VAOchao, GLuint VAOhouse, 
	GLuint VAOhouse2, GLuint VAOtelhado, GLuint VAOtelhado2,
	GLuint VAOporta,GLint colorLoc);


// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Código fonte do Vertex Shader (em GLSL): ainda hardcoded
const GLchar* vertexShaderSource = "#version 450\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\0";

//Códifo fonte do Fragment Shader (em GLSL): ainda hardcoded
const GLchar* fragmentShaderSource = "#version 450\n"
"uniform vec4 inputColor;\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = inputColor;\n"
"}\n\0";

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Triangulo!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Compilando e buildando o programa de shader
	GLuint shaderID = setupShader();

	//VAO usado no primeiro exercicio
	GLuint VAOchao = setupGeometryChao();
	GLuint VAOhouse = setupGeometryHouse();
	GLuint VAOhouse2 = setupGeometryHouse2();
	GLuint VAOtelhado = setupGeometryTelhado();
	GLuint VAOtelhado2 = setupGeometryTelhado2();
	GLuint VAOporta = setupGeometryPorta();

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a variáveis do tipo uniform em GLSL para armazenar esse tipo de info
	// que não está nos buffers
	GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
	assert(colorLoc > -1);
	glUseProgram(shaderID);


	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{

		//whileOriginal(shaderID, VAO, colorLoc);
		whileExercicio7(shaderID, VAOchao, VAOhouse, VAOhouse2, VAOtelhado, VAOtelhado2,VAOporta,colorLoc);

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}

	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

//Esta função está basntante hardcoded - objetivo é compilar e "buildar" um programa de
// shader simples e único neste exemplo de código
// O código fonte do vertex e fragment shader está nos arrays vertexShaderSource e
// fragmentShader source no iniçio deste arquivo
// A função retorna o identificador do programa de shader
int setupShader()
{
	// Vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// Checando erros de compilação (exibição via log no terminal)
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Checando erros de compilação (exibição via log no terminal)
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Linkando os shaders e criando o identificador do programa de shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Checando por erros de linkagem
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

int setupGeometryHouse()
{
	GLfloat vertices[] = {
		-0.5, 0.0, 0.0,
		-0.5, 0.5, 0.0,
		0.0, 0.5, 0.0,
		0.0, 0.0, 0.0
	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}

int setupGeometryHouse2()
{
	GLfloat vertices[] = {
		0.0, 0.5, 0.0,
		0.7, 0.5, 0.0,
		0.7, 0.0, 0.0
	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}

int setupGeometryChao()
{
	GLfloat vertices[] = {
		0.9f, 0.0f, 0.0f, // Top Right
		0.9f, -0.9f, 0.0f, // Bottom Right
		-0.9f, -0.9f, 0.0f, // Bottom Left
		-0.9f, 0.0f, 0.0f // Top Left
	};
	GLuint indices[] = { // Note that westart from 0
		0, 1, 3, // First Triangle
		1, 2, 3 // Second Triangle
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	return VAO;
}

int setupGeometryTelhado()
{
	GLfloat vertices[] = {
		// first triangle
		-0.5f, 0.509f, 0.0f,  // left 
		0.0f, 0.509f, 0.0f,  // right
		-0.25f, 0.8f, 0.0f,  // top
	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}

int setupGeometryTelhado2()
{
	GLfloat vertices[] = {
		-0.25f, 0.8f, 0.0f, // Top Right
		0.0f, 0.509f, 0.0f, // Bottom Right
		0.7f, 0.509f, 0.0f, // Bottom Left
		0.7f, 0.8f, 0.0f 
	};
	GLuint indices[] = { // Note that westart from 0
		0, 1, 2, // First Triangle
		0, 3, 2 // Second Triangle
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	return VAO;
}

int setupGeometryPorta()
{
	GLfloat vertices[] = {
		-0.3f, 0.2f, 0.0f, // Top Right
		-0.3f, 0.0, 0.0f, // Bottom Right
		-0.2f, 0.0, 0.0f, // Bottom Left
		-0.2f, 0.2f, 0.0f
	};
	GLuint indices[] = { // Note that westart from 0
		0, 1, 2, // First Triangle
		0, 3, 2 // Second Triangle
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	return VAO;
}

void whileExercicio7(GLuint shaderID, 
	GLuint VAOchao, 
	GLuint VAOhouse, GLuint VAOhouse2, 
	GLuint VAOtelhado, GLuint VAOtelhado2,
	GLuint VAOporta,
	GLint colorLoc) {
	// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
	glfwPollEvents();

	// Limpa o buffer de cor
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f); //cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(5);
	glPointSize(10);

	//chao
	glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
	glUseProgram(shaderID);
	glBindVertexArray(VAOchao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//casa
	glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 0.0f);
	glUseProgram(shaderID);
	glBindVertexArray(VAOhouse);
	glDrawArrays(GL_LINE_STRIP, 0, 4);

	//casa2
	glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 0.0f);
	glUseProgram(shaderID);
	glBindVertexArray(VAOhouse2);
	glDrawArrays(GL_LINE_STRIP, 0, 3);

	//telhado
	glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
	glUseProgram(shaderID);
	glBindVertexArray(VAOtelhado);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 0.0f);
	glUseProgram(shaderID);
	glDrawArrays(GL_LINE_LOOP, 0, 3);

	//telhado2
	glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
	glUseProgram(shaderID);
	glBindVertexArray(VAOtelhado2);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 0.0f);
	glUseProgram(shaderID);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	//porta
	glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);
	glUseProgram(shaderID);
	glBindVertexArray(VAOporta);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 0.0f);
	glUseProgram(shaderID);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

}
