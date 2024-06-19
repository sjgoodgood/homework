#pragma comment(lib, "OpenGL32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include "object.h"
#include "Transform.h"

// 화면 크기
const int WIDTH = 800;
const int HEIGHT = 600;

// 장애물 수
const int MAX_OBSTACLES = 2;
const int MAX_STARS = 5; // 별 수

// 중력 가속도
const float GRAVITY = -9.8f; // 중력 가속도

// 플레이어 점프 속도
const float MAX_JUMP_FORCE = 15.0f;

// 플레이어 상태
bool isJumping = false;
float playerVelocityY = 0.0f;
double spacebarPressedTime = 0.0;
bool spacebarHeld = false;

// 전역 변수로 플레이어 선언
Player player(0.0f, 0.0f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f);

// 미터 좌표를 픽셀 좌표로 변환하는 함수
float meterToPixel(float meter) {
    return meter * 10.0f; // 1 cm = 10 pixels
}

// 픽셀 좌표를 OpenGL 좌표로 변환하는 함수
float pixelToOpenGL(float pixel, float screenSize) {
    return (2.0f * pixel / screenSize) - 1.0f;
}

void errorCallback(int error, const char* description) {
    printf("GLFW Error: %s", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !isJumping) {
        spacebarPressedTime = glfwGetTime();
        spacebarHeld = true;
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE && !isJumping) {
        double spacebarReleasedTime = glfwGetTime();
        double heldTime = spacebarReleasedTime - spacebarPressedTime;
        float jumpForce = (heldTime * 15.0f < MAX_JUMP_FORCE) ? (heldTime * 15.0f) : MAX_JUMP_FORCE;  // 최대 점프력을 제한
        playerVelocityY = jumpForce;
        isJumping = true;
        spacebarHeld = false;
        player.rotationSpeed = -180.0f / (2 * jumpForce / -GRAVITY); // 점프 동안 180도 반대 방향으로 회전
    }
}

void reshape(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    float aspectRatio = (float)width / (float)height;
    float left, right, bottom, top, near = -1.0f, far = 1.0f;

    if (aspectRatio > 1.0f) {
        // Wider than tall
        left = -aspectRatio;
        right = aspectRatio;
        bottom = -1.0f;
        top = 1.0f;
    }
    else {
        // Taller than wide
        left = -1.0f;
        right = 1.0f;
        bottom = -1.0f / aspectRatio;
        top = 1.0f / aspectRatio;
    }

    float orthoMatrix[16] = {
        2.0f / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (top - bottom), 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f / (far - near), 0.0f,
        -(right + left) / (right - left), -(top + bottom) / (top - bottom), -(far + near) / (far - near), 1.0f
    };

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(orthoMatrix);

    glMatrixMode(GL_MODELVIEW);
}

void ApplyPhysics(Player& player, Floor& ground, float deltaTime) {
    if (isJumping) {
        playerVelocityY += GRAVITY * deltaTime; // 중력 가속도 적용 
        player.y += playerVelocityY * deltaTime; // y 위치 업데이트
        player.rotationAngle += player.rotationSpeed * deltaTime; // 회전 각도 업데이트

        // 지면에 닿으면 점프 멈춤
        if (player.y - player.height / 2 <= ground.y + ground.height / 2) {
            player.y = ground.y + ground.height / 2 + player.height / 2;
            isJumping = false;
            playerVelocityY = 0.0f;
            player.rotationAngle = 0.0f; // 땅에 닿으면 회전 각도 초기화
        }
    }
}

void UpdateObstacles(EnemyBlock obstacles[], int obstacleCount, float deltaTime, float ground_y_opengl) {
    float obstacleSpeed = 1.0f; // 장애물 속도
    // 각 장애물을 왼쪽으로 이동시킵니다.
    for (int i = 0; i < obstacleCount; ++i) {
        obstacles[i].Move(-obstacleSpeed * deltaTime); // 장애물을 왼쪽으로 이동시킵니다.
    }

    // 화면 밖으로 나간 장애물을 확인하고 재활용합니다.
    for (int i = 0; i < obstacleCount; ++i) {
        if (obstacles[i].x + obstacles[i].width / 2 < -1.0f) {
            // 장애물을 화면 오른쪽 끝으로 다시 이동시킵니다.
            float heights[2] = { 0.2f, 0.6f }; // 낮고 높은 장애물의 높이
            float newX = 1.0f + 0.25f * (rand() % 5); // 새로운 x 위치를 무작위로 설정
            int heightIndex = rand() % 2;
            float newHeight = heights[heightIndex];
            float newY = ground_y_opengl + newHeight / 2; // 지면 위에 장애물을 배치
            obstacles[i] = EnemyBlock(newX, newY, 0.1f, newHeight, 0.0f, 1.0f, 0.0f); // 장애물 재활용
        }
    }
}

void UpdateStars(Star stars[], int starCount, float deltaTime) {
    float starSpeed = 1.0f / 3.0f; // 장애물 속도의 1/3 속도
    // 각 별을 왼쪽으로 이동시킵니다.
    for (int i = 0; i < starCount; ++i) {
        stars[i].Move(-starSpeed * deltaTime); // 별을 왼쪽으로 이동시킵니다.
    }

    // 화면 밖으로 나간 별을 확인하고 재활용합니다.
    for (int i = 0; i < starCount; ++i) {
        if (stars[i].x + stars[i].width / 2 < -1.0f) {
            // 별을 화면 오른쪽 끝으로 다시 이동시킵니다.
            float newX = 1.0f + 0.25f * (rand() % 5); // 새로운 x 위치를 무작위로 설정
            float newY = 0.5f + 0.5f * (rand() % 100) / 100.0f; // 새로운 y 위치를 무작위로 설정
            stars[i] = Star(newX, newY, stars[i].size); // 별 재활용
        }
    }
}

int main(void) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GLFW 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "Google Dino Run Copy Game", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    // 초기 위치 설정
    float x_meter = 5.0f; // 지면에서 50cm 오른쪽으로 이동
    float y_meter = 12.0f; // 지면에서 1m 위에 위치

    float x_pixel = meterToPixel(x_meter);
    float y_pixel = meterToPixel(y_meter);

    float x_opengl = pixelToOpenGL(x_pixel, WIDTH);
    float y_opengl = pixelToOpenGL(y_pixel, HEIGHT);

    // 사각형의 크기
    const float square_size_meter = 5.0f; // 50cm = 5m
    const float border_thickness_meter = 0.3f; // 3cm = 0.3m
    float square_size_opengl = 2.0f * meterToPixel(square_size_meter) / WIDTH; // OpenGL 좌표로 변환
    float border_thickness_opengl = 2.0f * meterToPixel(border_thickness_meter) / WIDTH; // OpenGL 좌표로 변환

    // 화면 비율
    float aspectRatio = (float)WIDTH / (float)HEIGHT;

    // 지면의 y 위치
    float ground_y_meter = 10.0f; // 100cm = 10m
    float ground_y_pixel = meterToPixel(ground_y_meter);
    float ground_y_opengl = pixelToOpenGL(ground_y_pixel, HEIGHT);

    // 객체 생성
    player = Player(x_opengl, y_opengl, square_size_opengl, square_size_opengl, 1.0f, 0.0f, 0.0f); // 전역 변수로 선언된 player 객체 초기화
    Floor ground(0.0f, ground_y_opengl - 1.0f, 4.0f, 2.0f, 1.0f, 0.78f, 0.06f); // 너비를 4.0으로 설정하여 지면을 늘림

    // 장애물 생성
    EnemyBlock obstacles[MAX_OBSTACLES];
    int obstacleCount = MAX_OBSTACLES;
    float obstacle_width_opengl = 2.0f * meterToPixel(5.0f) / WIDTH; // 50cm = 5m
    float obstacle_height_low_opengl = 2.0f * meterToPixel(10.0f) / HEIGHT; // 100cm = 10m
    float obstacle_height_high_opengl = 2.0f * meterToPixel(30.0f) / HEIGHT; // 300cm = 30m

    obstacles[0] = EnemyBlock(0.75f, ground_y_opengl + obstacle_height_low_opengl / 2, obstacle_width_opengl, obstacle_height_low_opengl, 0.0f, 1.0f, 0.0f);
    obstacles[1] = EnemyBlock(1.25f, ground_y_opengl + obstacle_height_high_opengl / 2, obstacle_width_opengl, obstacle_height_high_opengl, 0.0f, 1.0f, 0.0f);

    // 별 생성
    Star stars[MAX_STARS];
    int starCount = MAX_STARS;

    for (int i = 0; i < starCount; ++i) {
        float newX = -1.0f + 2.0f * (rand() % 100) / 100.0f; // x 위치를 무작위로 설정
        float newY = 0.5f + 0.5f * (rand() % 100) / 100.0f; // y 위치를 무작위로 설정 (화면 위쪽에 위치하도록 설정)
        stars[i] = Star(newX, newY, 0.05f); // 별 초기화
    }

    glfwSetFramebufferSizeCallback(window, reshape);
    reshape(window, WIDTH, HEIGHT);

    float lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // 배경색을 (R:0, G:30, B:100)로 설정
        glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // 프레임 버퍼를 지우는 함수 호출

        glfwPollEvents();

        // 물리 적용
        ApplyPhysics(player, ground, deltaTime);

        // 장애물 업데이트
        UpdateObstacles(obstacles, obstacleCount, deltaTime, ground_y_opengl);

        // 별 업데이트
        UpdateStars(stars, starCount, deltaTime);

        // 충돌 검사
        for (int i = 0; i < obstacleCount; ++i) {
            if (PhysicsAABB(player, obstacles[i])) {
                // 충돌이 발생하면 창을 닫음
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
        }

        // 객체 그리기
        ground.Draw();
        player.Draw(border_thickness_opengl);
        for (int i = 0; i < obstacleCount; ++i) {
            obstacles[i].Draw();
        }

        // 별 그리기
        for (int i = 0; i < starCount; ++i) {
            stars[i].Draw();
        }

        // 버퍼를 교체하여 화면에 그립니다.
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}