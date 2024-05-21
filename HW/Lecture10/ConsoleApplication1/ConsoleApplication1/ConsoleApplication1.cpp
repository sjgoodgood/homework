#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#define PI 3.141592//무조건 정의!!
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
    glColor3ub(r, g, b);
    glVertex2f(cx + (x * cos(angle_degree) - y * sin(angle_degree)), cy + (x * sin(angle_degree) + y * cos(angle_degree)));
    return 0;
}

int setVertexRotation2(float x, float y, float angle_degree, float cx, float cy, float r, float g, float b) {
   
    glColor3f(r, g, b);
    float scaled_x = x * 0.25;//1/4로 축소
    float scaled_y = y * 0.25;//크기 
    glVertex2f(cx + (x * cos(angle_degree) - scaled_y * sin(angle_degree)), cy + (scaled_x * sin(angle_degree) + y * cos(angle_degree)));//x,y
    return 0;

}

float angle_circle = 1.0f;
float angle_star = 0.01f; // 별의 회전 각도
float angle_star_orbit = 0.01f;
float angle_square_orbit = 0.01f; // 사각형의 궤도 회전 각도->공전
float angle_square_self = 0.01f; // 사각형의 자체 회전 각도->자전
float circle_radius_star = 0.15f; // 별이 도는 원의 반지름
float circle_radius_square = 0.8f; // 사각형이 도는 원의 반지름
const float rotationSpeed_square_self = 2 * PI / 6000; // 100초에 한 바퀴
const float rotationSpeed_square_orbit = 2 * PI / 36000; // 10분에 한 바퀴
const float rotationSpeed_star = 2 * PI / 1800; // 30초에 한 바퀴
const float rotationSpeed_circle = 2 * PI / 1800;

int render()
{

    // 사각형의 중심 좌표
    float square_center_x = circle_radius_square * cos(angle_square_orbit);
    float square_center_y = circle_radius_square * sin(angle_square_orbit);

    glLineWidth(3.0f);
    glBegin(GL_LINE_LOOP);
    setVertexRotation(-0.04f, -0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    setVertexRotation(0.04f, -0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 0.0f);  // 파란색
    setVertexRotation(0.04f, 0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 0.0f);   // 파란색
    setVertexRotation(-0.04f, 0.04f, angle_square_self, square_center_x, square_center_y, 0.0f, 0.0f, 0.0f);  // 파란색
    glEnd();


    glBegin(GL_QUADS);
    // 사각형 그리기 (자체 회전 포함)
    setVertexRotation(-0.04f, -0.04f, angle_square_self, square_center_x, square_center_y, 91,155,213);
    setVertexRotation(0.04f, -0.04f, angle_square_self, square_center_x, square_center_y, 91, 155, 213);
    setVertexRotation(0.04f, 0.04f, angle_square_self, square_center_x, square_center_y, 91, 155, 213);
    setVertexRotation(-0.04f, 0.04f, angle_square_self, square_center_x, square_center_y, 91, 155, 213);
    glEnd();

    // 별의 중심 좌표
    float star_center_x = square_center_x + circle_radius_star * cos(angle_star);//사각형 중점+반지름의 크기(평행이동)
    float star_center_y = square_center_y + circle_radius_star * sin(angle_star);

    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);

    setVertexRotation(-0.05f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    setVertexRotation(0.02f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    setVertexRotation(0.04f, 0.03f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    setVertexRotation(0.05f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    setVertexRotation(-0.02f, 0.04f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    setVertexRotation(-0.04f, -0.03f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    setVertexRotation(0.0f, 0.08f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    setVertexRotation(-0.03f, 0.0f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    setVertexRotation(0.03f, 0.0f, angle_star, star_center_x, star_center_y, 0.0f, 0.0f, 0.0f); // 파란색
    glEnd();

    glBegin(GL_TRIANGLES);
    // 별 그리기
    setVertexRotation(-0.05f, 0.04f, angle_star, star_center_x, star_center_y, 255,242,0); // 파란색
    setVertexRotation(0.02f, 0.04f, angle_star, star_center_x, star_center_y, 255, 242, 0); // 파란색
    setVertexRotation(0.04f, -0.03f, angle_star, star_center_x, star_center_y, 255, 242, 0); // 파란색
    setVertexRotation(0.05f, 0.04f, angle_star, star_center_x, star_center_y, 255, 242, 0); // 파란색
    setVertexRotation(-0.02f, 0.04f, angle_star, star_center_x, star_center_y, 255, 242, 0); // 파란색
    setVertexRotation(-0.04f, -0.03f, angle_star, star_center_x, star_center_y, 255, 242, 0); // 파란색
    setVertexRotation(0.0f, 0.08f, angle_star, star_center_x, star_center_y, 255, 242, 0); // 파란색
    setVertexRotation(-0.03f, 0.0f, angle_star, star_center_x, star_center_y, 255, 242, 0); // 파란색
    setVertexRotation(0.03f, 0.0f, angle_star, star_center_x, star_center_y, 255, 242, 0); // 파란색
    glEnd();
 
    // 큰 원의 중심 좌표
    float big_circle_center_x = 0.0f;
    float big_circle_center_y = 0.0f;

    glLineWidth(10.0f);
    glBegin(GL_LINE_LOOP);
    for (float angle = 0; angle <= 360; angle += 1) {
        setVertexRotation(0.4, 0.4, angle + angle_circle, big_circle_center_x, big_circle_center_y, 214,127,42); // 회전 각도 적용
    }
    glEnd();
    // 큰 원 그리기
    glBegin(GL_TRIANGLE_FAN);
    for (float angle = 0; angle <= 360; angle += 1) {
        setVertexRotation(0.4, 0.4, angle + angle_circle, big_circle_center_x, big_circle_center_y, 255,217,102); // 회전 각도 적용
    }
    glEnd();

    // 작은 원의 중심 좌표
    float small_circle_center_x = 0.0f;
    float small_circle_center_y = 0.3;

    // 큰 원의 회전 각도에 따라 작은 원의 좌표 변환//회전행렬
    float rotated_small_circle_center_x = small_circle_center_x * cos(angle_circle) - small_circle_center_y * sin(angle_circle);
    float rotated_small_circle_center_y = small_circle_center_x * sin(angle_circle) + small_circle_center_y * cos(angle_circle);

    glBegin(GL_TRIANGLE_FAN);
    for (float angle = 0; angle <= 360; angle += 1) {
        setVertexRotation(0.1, 0.1, angle + angle_circle, rotated_small_circle_center_x, rotated_small_circle_center_y,255,230,153); // 회전 각도 적용
    }
    glEnd();

    // 작은 원의 중심 좌표
    small_circle_center_x = 0.0f;
    small_circle_center_y = -0.4f;

    // 큰 원의 회전 각도에 따라 작은 원의 좌표 변환//평행이동
    rotated_small_circle_center_x = small_circle_center_x * cos(angle_circle) - small_circle_center_y * sin(angle_circle);//회전변환
    rotated_small_circle_center_y = small_circle_center_x * sin(angle_circle) + small_circle_center_y * cos(angle_circle);

    glBegin(GL_TRIANGLE_FAN);//angle이 각
    for (float angle = 0; angle <= 360; angle += 1) {
        setVertexRotation2(0.1, 0.1, angle + angle_circle, rotated_small_circle_center_x, rotated_small_circle_center_y, 255,192,0); // 회전 각도 적용
    }
    glEnd();

    angle_star += rotationSpeed_star; // 별의 회전 속도
    angle_star_orbit += rotationSpeed_star;//별의 궤도 회전 속도
    angle_square_orbit += rotationSpeed_square_orbit; // 사각형의 궤도 회전 속도
    angle_square_self += rotationSpeed_square_self; // 사각형의 자체 회전 속도
    angle_circle += rotationSpeed_circle;// 원들의 회전

    //angle_star += 0.0003f;//5분49초
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
        render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}