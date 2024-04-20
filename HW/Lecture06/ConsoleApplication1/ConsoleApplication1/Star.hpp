#include "MObject.h"
#include <GLFW/glfw3.h>
#include <random> 

class Star : public MObject
{
public:
    Star()
    {

    }
    std::random_device rand; //random STL�� �̿�
    std::mt19937 a{ rand() }; // Mersenne Twister �˰����� ������� �ϴ� ���� �� �������� ��
    std::uniform_real_distribution<float> dist{ -1.0f, 1.0f }; // ���� ���� ��ǥ�� -1���� 1 ���̷� ����
    void update()
    {

    }

    void render()
    {
        glBegin(GL_POLYGON);

        float xPos = dist(a); // x 
        float yPos = dist(a); // y
        float red = dist(a); // ������ 
        float green = dist(a); // ��� 
        float blue = dist(a); // �Ķ���
        float scale = 0.05f;

        glColor3f(red, green, blue); // ���� ���� ����

        //��1
        glVertex2f(xPos + 0.2f * scale, yPos + 0.1f * scale);
        //��2
        glVertex2f(xPos + 0.8f * scale, yPos + 0.1f * scale);
        //��3
        glVertex2f(xPos + 0.3f * scale, yPos - 0.3f * scale);
        //��4
        glVertex2f(xPos + 0.5f * scale, yPos - 0.8f * scale);
        //��5
        glVertex2f(xPos + 0.0f * scale, yPos - 0.5f * scale);
        //��6
        glVertex2f(xPos - 0.5f * scale, yPos - 0.8f * scale);
        //��7
        glVertex2f(xPos - 0.3f * scale, yPos - 0.3f * scale);
        //��8
        glVertex2f(xPos - 0.8f * scale, yPos + 0.1f * scale);
        //��9
        glVertex2f(xPos - 0.2f * scale, yPos + 0.1f * scale);
        //��10
        glVertex2f(xPos + 0.0f * scale, yPos + 0.8f * scale);

        glEnd();
    }
};