#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../Facade/Facade.h"
namespace s21 {
class Controller {
  using AffineInfo = std::array<std::array<double, 3>, 3>;

 public:
  explicit Controller(Facade *Facade);
  ~Controller();
  void ParsOldSettings();
  SettingsParser::Settings &GetSettings();
  void SetDrawer(Drawer *drawer);
  void SendModelFile(std::string file);
  std::pair<size_t, size_t> GetModelInfo();
  QImage GetScreenshot();
  void Affine(char type, double x, double y, double z);
  std::vector<QImage> DoAnimation(size_t len, AffineInfo affine_values);

 private:
  Facade *facade;
};

}  // namespace s21
#endif
