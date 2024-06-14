#pragma comment(lib, "OpenGL32.lib")
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

const float playerSize = 0.1f; // 50cm 변환
const float groundHeight = 0.1f; // 100cm 변환

float PlayerY = -1.0f + groundHeight; // 플레이어의 초기 위치 (지면 위)
float PlayerJumpSpeed = 0.0f;
const float maxJumpSpeed = 10.0f; // 최대 점프 속도
const float gravity = -9.8f; // 중력 가속도
bool isJumping = false;
bool isFalling = false; // 하강 중인지 여부
bool isSpacePressed = false;
const float speedIncrement = 5.0f; // 점프 속도 증가량

bool isRightKeyPressed = false;
const float normalSpeed = 1.0f;
const float fastSpeed = 2.0f;
float obstacleSpeed = normalSpeed; // 장애물 이동 속도
float obstacleAcceleration = 0.0f;
const float accelerationIncrement = 0.5f; // 가속도 증가량

bool isCollision = false; // 충돌 상태 확인

unsigned int seed = 123456789; // 초기 시드 값

float lowObstacleX1 = 0.8f;
float lowObstacleX2 = 1.2f;
float highObstacleX1 = 1.0f;
float highObstacleX2 = 1.4f;

float randomFloat(float min, float max) {
    seed = (1103515245 * seed + 12345) % (1 << 31);
    float random = static_cast<float>(seed) / (1 << 31);
    return min + random * (max - min);
}

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
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && !isJumping && !isCollision) // 스페이스바를 누르면 점프 시작
    {
        isJumping = true; // 점프 상태로 설정
        isFalling = false; // 하강 상태 해제
        PlayerJumpSpeed = 2.0f; // 초기 점프 속도 설정
        isSpacePressed = true; // 스페이스바 눌림 상태 설정
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE) // 스페이스바를 떼면
    {
        isSpacePressed = false; // 스페이스바 눌림 상태 해제
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) // 오른쪽 방향키를 누르면
    {
        isRightKeyPressed = true;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) // 오른쪽 방향키를 떼면
    {
        isRightKeyPressed = false;
    }
}

void PlayerMove(float deltaTime)
{
    if (isCollision) return; // 충돌 시 움직임 멈춤

    if (isSpacePressed && isJumping && !isFalling) // 스페이스바가 눌린 상태에서 점프 중이고 하강 중이 아니면
    {
        PlayerJumpSpeed += speedIncrement * deltaTime; // 점프 속도 증가
        if (PlayerJumpSpeed > maxJumpSpeed) // 최대 점프 속도 제한
        {
            PlayerJumpSpeed = maxJumpSpeed;
        }
    }

    PlayerJumpSpeed += gravity * deltaTime;  // 중력 적용
    PlayerY += PlayerJumpSpeed * deltaTime;  // 속도를 위치에 적용

    if (PlayerJumpSpeed < 0) // 상향 속도가 0보다 작아지면 하강 상태로 전환
    {
        isFalling = true;
    }

    if (PlayerY <= -1.0f + groundHeight)
    {
        PlayerY = -1.0f + groundHeight; // 바닥에 닿았을 때 위치 고정
        PlayerJumpSpeed = 0.0f; // 속도 제거
        isJumping = false; // 점프 상태 해제
        isFalling = false; // 하강 상태 해제
    }
}

void updateObstacleSpeed(float deltaTime)
{
    if (isCollision) return; // 충돌 시 움직임 멈춤

    if (isRightKeyPressed)
    {
        obstacleAcceleration += accelerationIncrement * deltaTime; // 가속도 증가
        if (obstacleSpeed < fastSpeed)
        {
            obstacleSpeed += obstacleAcceleration * deltaTime;
            if (obstacleSpeed > fastSpeed)
            {
                obstacleSpeed = fastSpeed; // 최대 속도 제한
            }
        }
    }
    else
    {
        if (obstacleAcceleration > 0.0f)
        {
            obstacleAcceleration -= accelerationIncrement * deltaTime; // 가속도 감소
        }
        else
        {
            obstacleAcceleration = 0.0f;
        }
        if (obstacleSpeed > normalSpeed)
        {
            obstacleSpeed -= accelerationIncrement * deltaTime; // 가속도 감소가 아니라 직접적으로 속도를 줄여야 합니다.
            if (obstacleSpeed < normalSpeed)
            {
                obstacleSpeed = normalSpeed; // 최소 속도 제한
            }
        }
    }
}

bool checkCollision()
{
    float playerLeft = -0.875f;
    float playerRight = playerLeft + playerSize; // 50cm 정사각형의 오른쪽 경계
    float playerTop = PlayerY + playerSize; // 50cm 정사각형의 위쪽 경계
    float playerBottom = PlayerY;

    // 낮은 장애물
    float lowObstacleTop = -1.0f + groundHeight + 0.1f; // 낮은 장애물 높이

    // 높은 장애물
    float highObstacleTop = -1.0f + groundHeight + 0.3f; // 높은 장애물 높이

    // 낮은 장애물과의 충돌 검사
    bool collisionWithLowObstacle1 = (playerRight >= lowObstacleX1 && playerLeft <= lowObstacleX1 + 0.05f &&
        playerTop >= -1.0f + groundHeight && playerBottom <= lowObstacleTop);

    bool collisionWithLowObstacle2 = (playerRight >= lowObstacleX2 && playerLeft <= lowObstacleX2 + 0.05f &&
        playerTop >= -1.0f + groundHeight && playerBottom <= lowObstacleTop);

    // 높은 장애물과의 충돌 검사
    bool collisionWithHighObstacle1 = (playerRight >= highObstacleX1 && playerLeft <= highObstacleX1 + 0.05f &&
        playerTop >= -1.0f + groundHeight && playerBottom <= highObstacleTop);

    bool collisionWithHighObstacle2 = (playerRight >= highObstacleX2 && playerLeft <= highObstacleX2 + 0.05f &&
        playerTop >= -1.0f + groundHeight && playerBottom <= highObstacleTop);

    return collisionWithLowObstacle1 || collisionWithLowObstacle2 || collisionWithHighObstacle1 || collisionWithHighObstacle2;
}

void drawObstacle(float x, float y, float width, float height)
{
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 1.0f, 0.0f); // 녹색
    glVertex2f(x, y);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y);
    glEnd();
}
void obstacles(float deltaTime) {
    float obstacleWidth = 0.05f; // 50cm
    float lowObstacleHeight = 0.1f; // 100cm
    float highObstacleHeight = 0.3f; // 300cm

    // 장애물 그리기
    drawObstacle(lowObstacleX1, -1.0f + groundHeight, obstacleWidth, lowObstacleHeight); // 지면 위에 그리기
    drawObstacle(lowObstacleX2, -1.0f + groundHeight, obstacleWidth, lowObstacleHeight); // 지면 위에 그리기
    drawObstacle(highObstacleX1, -1.0f + groundHeight, obstacleWidth, highObstacleHeight); // 지면 위에 그리기
    drawObstacle(highObstacleX2, -1.0f + groundHeight, obstacleWidth, highObstacleHeight); // 지면 위에 그리기

    // 장애물 이동
    lowObstacleX1 -= obstacleSpeed * deltaTime;
    lowObstacleX2 -= obstacleSpeed * deltaTime;
    highObstacleX1 -= obstacleSpeed * deltaTime;
    highObstacleX2 -= obstacleSpeed * deltaTime;

    // 장애물이 화면을 벗어나면 반대편에서 나타나도록
    if (lowObstacleX1 < -1.2f) {
        lowObstacleX1 = 1.0f;
    }
    if (lowObstacleX2 < -1.2f) {
        lowObstacleX2 = 1.0f;
    }
    if (highObstacleX1 < -1.2f) {
        highObstacleX1 = 1.0f;
    }
    if (highObstacleX2 < -1.2f) {
        highObstacleX2 = 1.0f;
    }
}

void Player() {
    // 플레이어 내부 사각형 (빨간색)
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.875f, PlayerY + playerSize);
    glVertex2f(-0.875f, PlayerY);
    glVertex2f(-0.875f + playerSize, PlayerY);
    glVertex2f(-0.875f + playerSize, PlayerY + playerSize);
    glEnd();

    // 플레이어 테두리 (검정색)
    glLineWidth(3.0f); // 3cm 두께의 테두리
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.875f, PlayerY + playerSize);
    glVertex2f(-0.875f, PlayerY);
    glVertex2f(-0.875f + playerSize, PlayerY);
    glVertex2f(-0.875f + playerSize, PlayerY + playerSize);
    glEnd();
}

void ground() {
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.784f, 0.0588f); // RGB(255, 200, 15)
    glVertex2f(-1.0f, -1.0f + groundHeight); // 100cm를 고려하여 지면 높이 설정
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f + groundHeight);
    glEnd();
}

void render() {
    ground();
    Player();
    obstacles(0); // 0은 초기화된 deltaTime 값
}

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    auto previousTime = std::chrono::high_resolution_clock::now(); // 현재 시간 가져오기

    seed = static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()); // 랜덤 시드 초기화

    while (!glfwWindowShouldClose(window))
    {
        auto currentTime = std::chrono::high_resolution_clock::now(); // 현재 시간 가져오기
        std::chrono::duration<float> deltaTime = currentTime - previousTime; // 경과 시간 계산
        previousTime = currentTime; // 이전 시간 갱신

        glfwPollEvents();
        glClearColor(0.0f, 0.1176f, 0.3922f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (!isCollision) {
            isCollision = checkCollision();
        }
        updateObstacleSpeed(deltaTime.count());
        obstacles(deltaTime.count());
        PlayerMove(deltaTime.count());

        if (isCollision) {
            obstacleSpeed = 0.0f; // 충돌 시 장애물 멈춤
        }
        render();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}