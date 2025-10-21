#include "Util.h"

void drawFace(const Vector3& topLeftPoint, const Vector3& topRightPoint, const Vector3& bottomLeftPoint, const Vector3& bottomRightPoint) {
    glVertex3d(topLeftPoint.x, topLeftPoint.y, topLeftPoint.z);
    glVertex3d(topRightPoint.x, topRightPoint.y, topRightPoint.z);
    glVertex3d(bottomLeftPoint.x, bottomLeftPoint.y, bottomLeftPoint.z);
    glVertex3d(bottomRightPoint.x, bottomRightPoint.y, bottomRightPoint.z);
}
void drawLine(const Vector3& point1, const Vector3& point2) {
    glVertex3d(point1.x, point1.y, point1.z);
    glVertex3d(point2.x, point2.y, point2.z);
}
