#ifndef AFFINE_H_
#define AFFINE_H_

#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace s21 {
enum Aff { kScale, kRotate, kMove };

class AffineTransform {
 public:
  virtual ~AffineTransform() = default;
  virtual void Affine(std::vector<double> &vert, double scaleX, double scaleY,
                      double scaleZ) = 0;
};

class Scale : public AffineTransform {
 public:
  void Affine(std::vector<double> &vert, double scaleX, double scaleY,
              double scaleZ) override;
};

class Rotate : public AffineTransform {
 public:
  void Affine(std::vector<double> &vert, double radX, double radY,
              double radZ) override;

 private:
  void rotateX(std::vector<double> &vert, double radX);
  void rotateY(std::vector<double> &vert, double radY);
  void rotateZ(std::vector<double> &vert, double radZ);
};

class Move : public AffineTransform {
 public:
  void Affine(std::vector<double> &vert, double scaleX, double scaleY,
              double scaleZ) override;
};

class Strategy {
 private:
  AffineTransform *affine_;

 public:
  explicit Strategy(AffineTransform *Affine = nullptr) : affine_(Affine) {}
  ~Strategy() { delete affine_; }
  void SetStrategy(AffineTransform *Affine) {
    delete affine_;
    affine_ = Affine;
  }
  void Work(std::vector<double> &vert, double x, double y, double z) {
    affine_->Affine(vert, x, y, z);
  }
};

}  // namespace s21

#endif
