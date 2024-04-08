#pragma comment(lib,"OpenGL32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#define GLFW_MOUSE_BUTTON_RiGHT
#define GLFW_MOUSE_BUTTON_LEFT

//bool isLeftButtonPressed = false;
//bool isRightButtonPressed = false;


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)//어떤 윈도우에서 받은건지 어떤키인지 어떤 스페이스인지 어떤 휠인지..
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)//키가 
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);//윈도우가 닫히면 true(1)
	}
}
void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error:" << description << std::endl;

}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)//int scancode가 키보드와 관련된거라서 있으면 에러남
{
	//if (button == GLFW_MOUSE_BUTTON_2) {
	//	isLeftButtonPressed = (action == GLFW_PRESS);
	//}
	//else if (button == GLFW_MOUSE_BUTTON_1) {
	//	isRightButtonPressed = (action == GLFW_PRESS);
	//}

	if (button == GLFW_MOUSE_BUTTON_2 && action == GLFW_PRESS) {


		glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}

	else if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {


		glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}

	else {

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	}

}
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {



	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}
	if (xoffset == 0 && yoffset == 0) {
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
				glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				glfwSwapBuffers(window);
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
		}
				
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);



	}


}


int main()
{

	GLFWwindow* window;

	if (!glfwInit())//반환값이 있다 (0이면 실패로 뜸) 그래서 if문으로 써야함
		return -1;


	window = glfwCreateWindow(1280, 768, "hohoho himnae", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetErrorCallback(errorCallback);//윈도우로 부터 에러가 났을때(윈도우나 os에서 잘못했을때)설정했던 함수를 지원해주겠다
	glfwSetKeyCallback(window, keyCallback);
	/*Make the window's context current */ //주도권을 갖고 쓰겠다 
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	while (!glfwWindowShouldClose(window)) //while은 게임루프
	{
		glfwPollEvents();//반복해서 확인하기
		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);

	}



	glfwTerminate();
	return 0;
}

