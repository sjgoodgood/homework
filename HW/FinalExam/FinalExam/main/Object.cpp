#include "object.h"
#include <cmath>

void Object::Draw(float borderThickness) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y - height / 2.0f);
    glVertex2f(x + width / 2.0f, y + height / 2.0f);
    glVertex2f(x - width / 2.0f, y + height / 2.0f);
    glEnd();

    if (borderThickness > 0.0f) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        // Bottom border
        glVertex2f(x - width / 2.0f - borderThickness, y - height / 2.0f - borderThickness);
        glVertex2f(x + width / 2.0f + borderThickness, y - height / 2.0f - borderThickness);
        glVertex2f(x + width / 2.0f + borderThickness, y - height / 2.0f);
        glVertex2f(x - width / 2.0f - borderThickness, y - height / 2.0f);

        // Top border
        glVertex2f(x - width / 2.0f - borderThickness, y + height / 2.0f);
        glVertex2f(x + width / 2.0f + borderThickness, y + height / 2.0f);
        glVertex2f(x + width / 2.0f + borderThickness, y + height / 2.0f + borderThickness);
        glVertex2f(x - width / 2.0f - borderThickness, y + height / 2.0f + borderThickness);

        // Left border
        glVertex2f(x - width / 2.0f - borderThickness, y - height / 2.0f);
        glVertex2f(x - width / 2.0f, y - height / 2.0f);
        glVertex2f(x - width / 2.0f, y + height / 2.0f);
        glVertex2f(x - width / 2.0f - borderThickness, y + height / 2.0f);

        // Right border
        glVertex2f(x + width / 2.0f, y - height / 2.0f);
        glVertex2f(x + width / 2.0f + borderThickness, y - height / 2.0f);
        glVertex2f(x + width / 2.0f + borderThickness, y + height / 2.0f);
        glVertex2f(x + width / 2.0f, y + height / 2.0f);
        glEnd();
    }
}

void Player::Draw(float borderThickness) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(-width / 2.0f, -height / 2.0f);
    glVertex2f(width / 2.0f, -height / 2.0f);
    glVertex2f(width / 2.0f, height / 2.0f);
    glVertex2f(-width / 2.0f, height / 2.0f);
    glEnd();

    if (borderThickness > 0.0f) {
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
        // Bottom border
        glVertex2f(-width / 2.0f - borderThickness, -height / 2.0f - borderThickness);
        glVertex2f(width / 2.0f + borderThickness, -height / 2.0f - borderThickness);
        glVertex2f(width / 2.0f + borderThickness, -height / 2.0f);
        glVertex2f(-width / 2.0f - borderThickness, -height / 2.0f);

        // Top border
        glVertex2f(-width / 2.0f - borderThickness, height / 2.0f);
        glVertex2f(width / 2.0f + borderThickness, height / 2.0f);
        glVertex2f(width / 2.0f + borderThickness, height / 2.0f + borderThickness);
        glVertex2f(-width / 2.0f - borderThickness, height / 2.0f + borderThickness);

        // Left border
        glVertex2f(-width / 2.0f - borderThickness, -height / 2.0f);
        glVertex2f(-width / 2.0f, -height / 2.0f);
        glVertex2f(-width / 2.0f, height / 2.0f);
        glVertex2f(-width / 2.0f - borderThickness, height / 2.0f);

        // Right border
        glVertex2f(width / 2.0f, -height / 2.0f);
        glVertex2f(width / 2.0f + borderThickness, -height / 2.0f);
        glVertex2f(width / 2.0f + borderThickness, height / 2.0f);
        glVertex2f(width / 2.0f, height / 2.0f);
        glEnd();
    }

    glPopMatrix();
}

void Star::drawStar() const {
    float halfSize = size / 2.0f;
    float angle = 72.0f * 3.141592 / 180.0f;
    glColor3ub(255, 255, 0);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for (int i = 0; i <= 5; ++i) {
        float xVertex = x + halfSize * cos(i * 2 * angle);
        float yVertex = y + halfSize * sin(i * 2 * angle);
        glVertex2f(xVertex, yVertex);
    }

    glEnd();
}

void Star::Draw(float borderThickness) {
    drawStar();
}

int PhysicsAABB(Object A, Object B) {
    return (A.x - A.width / 2 < B.x + B.width / 2 &&
        A.x + A.width / 2 > B.x - B.width / 2 &&
        A.y - A.height / 2 < B.y + B.height / 2 &&
        A.y + A.height / 2 > B.y - B.height / 2);
}