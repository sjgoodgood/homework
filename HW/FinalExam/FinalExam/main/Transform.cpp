#include "Transform.h"
#include <cmath>

namespace Transform {
    const float PI = 3.14159265358979323846f;

    Vertex MoveVertex(Vertex point, Vector meter) {
        point.x += meter.x_meter;
        point.y += meter.y_meter;
        return point;
    }

    Vertex RotateVertex(Vertex point, float angle_degree) {
        float angle_rad = angle_degree * (PI / 180.0f);
        float cos_angle = cos(angle_rad);
        float sin_angle = sin(angle_rad);
        float x_new = point.x * cos_angle - point.y * sin_angle;
        float y_new = point.x * sin_angle + point.y * cos_angle;
        return { x_new, y_new };
    }

    Vertex ScaleVertex(Vertex point, Vector meter) {
        point.x = meter.x_meter;
        point.y = meter.y_meter;
        return point;
    }
}