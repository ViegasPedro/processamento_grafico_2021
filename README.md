# processamento_grafico
Projetos Processamento Gráfico

O projeto consiste em uma solution contendo vários projetos, onde cada um desses projetos representa um exercício da lista.

Para executar um determinado exercício é necessário defini-lo como projeto de inicialização.

CONFIGURAÇÃO DE DEPENDÊNCIAS:

1 - Nas propriedades do projeto no menu "C/C++" no campo "Additional Include Directories" adcionar os seguintes paths:
..\..\dependencies\GLAD\include;
..\..\dependencies\glfw-3.3.3.bin.WIN64\include;
..\..\dependencies\glm;

2 - Nas propriedades do projeto no menu "Linker" no campo "Additional Library Directories" adcionar os seguintes paths:
..\..\dependencies\glfw-3.3.3.bin.WIN64\lib-vc2019;

3 - Nas propriedades do projeto no menu "Input" no campo "Additional Dependencies" adcionar os seguintes dados:
glfw3.lib
opengl32.lib