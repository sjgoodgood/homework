#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>

int width = 800;
int height = 600;
float zoom = 1.0f;
double dragStartX, dragStartY;
bool dragging = false;
bool zoomingIn = false;
float cameraX = 0.0f;
float cameraY = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        dragging = true;
        zoomingIn = false;
        glfwGetCursorPos(window, &dragStartX, &dragStartY);
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        dragging = true;
        zoomingIn = true;
        glfwGetCursorPos(window, &dragStartX, &dragStartY);
    }
    else if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_RELEASE) {
        dragging = false;
    }
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (dragging) {
        float sensitivity = 0.01f;
        float deltaX = xpos - dragStartX;
        float deltaY = ypos - dragStartY;
        if (zoomingIn) {
            if (deltaX > 0) {
                zoom *= (1.0f + sensitivity * deltaX);
            }
            else if (deltaX < 0) {
                zoom /= (1.0f - sensitivity * deltaX);
            }
        }
        else {
            cameraX -= sensitivity * deltaX;
            cameraY += sensitivity * deltaY;
        }
        dragStartX = xpos;
        dragStartY = ypos;
    }
}

void setProjection() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.8f, 0.85f);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Zoom and Move on Drag", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    glViewport(0, 0, width, height);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        setProjection();

        glLoadIdentity();
        glTranslatef(-cameraX, -cameraY, -5.0f);
        glScalef(zoom, zoom, 1.0f);

        // 삼각형 그리기
        drawTriangle(-0.5f, 0.4f, 0.2f, 0.4f, 0.4f, -0.3f);
        drawTriangle(0.5f, 0.4f, -0.2f, 0.4f, -0.4f, -0.3f);
        drawTriangle(0.0f, 0.8f, -0.3f, 0.0f, 0.3f, 0.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}