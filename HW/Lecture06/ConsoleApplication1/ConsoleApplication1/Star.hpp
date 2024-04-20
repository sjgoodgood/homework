#include "MObject.h"
#include <GLFW/glfw3.h>
#include <random> 

class Star : public MObject
{
public:
    Star()
    {

    }
    std::random_device rand; //random STL를 이용
    std::mt19937 a{ rand() }; // Mersenne Twister 알고리즘을 기반으로 하는 랜덤 수 생성기라고 함
    std::uniform_real_distribution<float> dist{ -1.0f, 1.0f }; // 별의 생성 좌표를 -1에서 1 사이로 지정
    void update()
    {

    }

    void render()
    {
        glBegin(GL_POLYGON);

        float xPos = dist(a); // x 
        float yPos = dist(a); // y
        float red = dist(a); // 빨간색 
        float green = dist(a); // 녹색 
        float blue = dist(a); // 파란색
        float scale = 0.05f;

        glColor3f(red, green, blue); // 랜덤 색깔 지정

        //점1
        glVertex2f(xPos + 0.2f * scale, yPos + 0.1f * scale);
        //점2
        glVertex2f(xPos + 0.8f * scale, yPos + 0.1f * scale);
        //점3
        glVertex2f(xPos + 0.3f * scale, yPos - 0.3f * scale);
        //점4
        glVertex2f(xPos + 0.5f * scale, yPos - 0.8f * scale);
        //점5
        glVertex2f(xPos + 0.0f * scale, yPos - 0.5f * scale);
        //점6
        glVertex2f(xPos - 0.5f * scale, yPos - 0.8f * scale);
        //점7
        glVertex2f(xPos - 0.3f * scale, yPos - 0.3f * scale);
        //점8
        glVertex2f(xPos - 0.8f * scale, yPos + 0.1f * scale);
        //점9
        glVertex2f(xPos - 0.2f * scale, yPos + 0.1f * scale);
        //점10
        glVertex2f(xPos + 0.0f * scale, yPos + 0.8f * scale);

        glEnd();
    }
};