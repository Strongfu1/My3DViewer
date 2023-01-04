#ifndef FACADE_H
#define FACADE_H
#include <fstream>

#include "ModelReader.h"
#include "affine.h"
#include "drawer.h"
#include "parsSavedSettings.h"
namespace s21 {
class Facade {
public:
  using AffineInfo = std::array<std::array<double, 3>, 3>;
  Facade();
  ~Facade();

  void ParsSettings();
  SettingsParser::Settings &GetSettings();
  void Read(std::string file_name);
  void SetDrawer(Drawer *drawer);
  std::pair<size_t, size_t> ModelInfo();
  QImage GetScreenshot();
  void AffineTransformations(char type, double x, double y, double z);
  std::vector<QImage> DoAnimation(size_t len, AffineInfo affine_values);

private:
  std::vector<double> &GetVertices();
  Strategy affine;
  ModelReader model_reader;
  Drawer *drawer;
};
} // namespace s21

#endif
