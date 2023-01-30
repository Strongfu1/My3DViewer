#include "Facade.h"
namespace s21 {
Facade::Facade() : drawer(nullptr) { SettingsParser::GetInstance(); }

Facade::~Facade() {
  SettingsParser *pars = SettingsParser::GetInstance();
  delete pars;
}

void Facade::ParsSettings() {
  SettingsParser *pars = SettingsParser::GetInstance();
  pars->parsFileSavedSettings();
}

SettingsParser::Settings &Facade::GetSettings() {
  return SettingsParser::GetInstance()->GetSettings();
}

void Facade::Read(std::string file_name) {
  drawer->SetModel(model_reader.Read(file_name));
  drawer->update();
}

std::pair<size_t, size_t> Facade::ModelInfo() {
  return std::pair<size_t, size_t>(drawer->ModelInfo());
}

void Facade::SetDrawer(Drawer *drawer) { this->drawer = drawer; }

QImage Facade::GetScreenshot() { return drawer->GetScreenshot(); }

std::vector<double> &Facade::GetVertices() { return drawer->Vertices(); }

void Facade::AffineTransformations(char type, double x, double y, double z) {
  switch (type) {
  case kScale:
    Affine.SetStrategy(new Scale);
    break;
  case kRotate:
    Affine.SetStrategy(new Rotate);
    break;
  case kMove:
    Affine.SetStrategy(new Move);
    break;
  default:
    return;
  }
  std::vector<double> &vec = GetVertices();
  Affine.Work(vec, x, y, z);
  drawer->update();
}

std::vector<QImage> Facade::DoAnimation(size_t len, AffineInfo affine_values) {
  std::vector<QImage> animation(len);
  for (size_t i = 0; i < len; ++i) {
    AffineTransformations(kScale, affine_values[0][0], affine_values[0][1],
                          affine_values[0][2]);
    AffineTransformations(kRotate, affine_values[1][0], affine_values[1][1],
                          affine_values[1][2]);
    AffineTransformations(kMove, affine_values[2][0], affine_values[2][1],
                          affine_values[2][2]);
    animation[i] = (GetScreenshot());
  }
  return animation;
}

} // namespace s21
