#include "Affine.h"
namespace s21 {

void Scale::Affine(std::vector<double> &vert, double scaleX, double scaleY,
                   double scaleZ) {
  if (scaleX != 1 || scaleY != 1 || scaleZ != 1)
    for (size_t i = 0; i < vert.size(); i += 3) {
      vert[i] *= scaleX;
      vert[i + 1] *= scaleY;
      vert[i + 2] *= scaleZ;
    }
}

void Rotate::Affine(std::vector<double> &vert, double radX, double radY,
                    double radZ) {
  if (radX)
    rotateX(vert, radX);
  if (radY)
    rotateY(vert, radY);
  if (radZ)
    rotateZ(vert, radZ);
}

void Rotate::rotateX(std::vector<double> &vert, double rad) {
  for (size_t i = 0; i < vert.size(); i += 3) {
    double tempY = vert[i + 1];
    double tempZ = vert[i + 2];
    vert[i + 1] = tempY * cos(rad) - tempZ * sin(rad);
    vert[i + 2] = tempZ * cos(rad) + tempY * sin(rad);
  }
}

void Rotate::rotateY(std::vector<double> &vert, double rad) {
  for (size_t i = 0; i < vert.size(); i += 3) {
    double tempX = vert[i];
    double tempZ = vert[i + 2];
    vert[i] = tempX * cos(rad) + tempZ * sin(rad);
    vert[i + 2] = tempZ * cos(rad) - tempX * sin(rad);
  }
}

void Rotate::rotateZ(std::vector<double> &vert, double rad) {
  for (size_t i = 0; i < vert.size(); i += 3) {
    double tempX = vert[i];
    double tempY = vert[i + 1];
    vert[i] = tempX * cos(rad) - tempY * sin(rad);
    vert[i + 1] = tempY * cos(rad) + tempX * sin(rad);
  }
}

void Move::Affine(std::vector<double> &vert, double moveX, double moveY,
                  double moveZ) {
  if (moveX || moveY || moveZ)
    for (size_t i = 0; i < vert.size(); i += 3) {
      vert[i] += moveX;
      vert[i + 1] += moveY;
      vert[i + 2] += moveZ;
    }
}

} // namespace s21
