
#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#define PI 3.141592
#include<math.h>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		moveFactor += 0.01f;
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		scaleFactor += 0.1f;
	}
}

//int setVertexRotation(float x, float y, float angle_degree)
//{
//	glColor3f(0.7f, 0.8f, 0.85f);
//	glVertex2f(x * cos(-angle_degree) - (y * sin(-angle_degree)), x * sin(-angle_degree) + (y * cos(-angle_degree)));
//	return 0;

//}반대로 회전하는거

int setVertexRotation(float x, float y, float angle_degree, float cx, float cy, float r, float g, float b)
{
	glColor3f(r,g,b);
	glVertex2f(cx + (x * cos(angle_degree) - y * sin(angle_degree)), cy + (x * sin(angle_degree) + y * cos(angle_degree)));
	return 0;
}


float angle_star = 0.01f; // 별의 회전 각도
float angle_square = 0.01f; // 사각형의 회전 각도
float circle_radius_star = 0.4; // 별이 도는 원의 반지름
float circle_radius_square = 0.2f; // 사각형이 도는 원의 반지름


int render()
{
    // 별의 중심 좌표
    float star_center_x = circle_radius_star * cos(angle_star);
    float star_center_y = circle_radius_star * sin(angle_star);

    glBegin(GL_TRIANGLES);
    setVertexRotation(-0.05f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 1.0f); // 파란색
    setVertexRotation(0.02f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 1.0f); // 파란색
    setVertexRotation(0.04f, -0.03f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 1.0f); // 파란색
    setVertexRotation(0.05f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 1.0f); // 파란색
    setVertexRotation(-0.02f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 1.0f); // 파란색
    setVertexRotation(-0.04f, -0.03f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 1.0f); // 파란색
    setVertexRotation(0.0f, 0.08f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 1.0f); // 파란색
    setVertexRotation(-0.03f, 0.0f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 1.0f); // 파란색
    setVertexRotation(0.03f, 0.0f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 1.0f); // 파란색
    glEnd();


    glBegin(GL_QUADS);
    // 사각형의 중심 좌표
    float square_center_x = circle_radius_square * cos(angle_square);
    float square_center_y = circle_radius_square * sin(angle_square);
    setVertexRotation(square_center_x - 0.025f, square_center_y - 0.025f, angle_star, star_center_x, star_center_y, 0.7f, 0.8f, 0.85f);// 회색
    setVertexRotation(square_center_x + 0.025f, square_center_y - 0.025f, angle_star, star_center_x, star_center_y, 0.7f, 0.8f, 0.85f); 
    setVertexRotation(square_center_x + 0.025f, square_center_y + 0.025f, angle_star, star_center_x, star_center_y, 0.7f, 0.8f, 0.85f); 
    setVertexRotation(square_center_x - 0.025f, square_center_y + 0.025f, angle_star, star_center_x, star_center_y, 0.7f, 0.8f, 0.85f); 
    glEnd();

    angle_star += 0.0007f; // 별의 회전 속도
    angle_square += 0.0001f; // 사각형의 회전 속도
    return 0;
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1000, 1000, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glBegin(GL_POINTS);

        for (double d = 0.0; d <= PI * 2.0; d += PI / 800) {
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex3f(0.4 * cos(d), 0.4 * sin(d), 0.1);
        }
        glEnd();

        glBegin(GL_QUADS);
        // 사각형의 네 꼭지점 좌표 직접 지정
        glColor3f(1.0f, 0.0f, 0.0f); // 사각형의 색상을 파란색으로 설정
        glVertex2f(-0.04f, -0.04f); // 좌하단
        glVertex2f(0.04f, -0.04f);  // 우하단
        glVertex2f(0.04f, 0.04f);   // 우상단
        glVertex2f(-0.04f, 0.04f);  // 좌상단
        glEnd();
        render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}