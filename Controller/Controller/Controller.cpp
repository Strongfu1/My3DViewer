#include "Controller.h"
namespace s21 {
Controller::Controller(Facade *facade) : facade(facade) {}

Controller::~Controller() {}

void Controller::ParsOldSettings() { facade->ParsSettings(); }

SettingsParser::Settings &Controller::GetSettings() {
  return facade->GetSettings();
}

void Controller::SetDrawer(Drawer *drawer) { facade->SetDrawer(drawer); }

void Controller::SendModelFile(std::string file) { facade->Read(file); }

std::pair<size_t, size_t> Controller::GetModelInfo() {
  return facade->ModelInfo();
}

QImage Controller::GetScreenshot() { return facade->GetScreenshot(); }

void Controller::Affine(char type, double x, double y, double z) {
  facade->AffineTransformations(type, x, y, z);
}

std::vector<QImage> Controller::DoAnimation(size_t len,
                                            AffineInfo affine_values) {
  return facade->DoAnimation(len, affine_values);
}

} // namespace s21
