#ifndef VIEW_H
#define VIEW_H
#include <QMainWindow>
#include <QtSvg>
#include <array>

#include "../../Controller/Controller/Controller.h"
#include "../Settings/Settings.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT
  using AffineInfo = std::array<std::array<double, 3>, 3>;

 public:
  explicit View(Controller *Controller, QWidget *parent = nullptr);
  ~View();

 private slots:
  void on_openFile_clicked();
  void on_settings_clicked();
  void on_photoButton_clicked();
  void on_scaleDo_clicked();
  void on_moveDo_clicked();
  void on_rotationDo_clicked();
  void on_gifButton_clicked();

 signals:
  void fileSetter(FILE *s);
  void applyOldSettings();
  void affineUpdate();

 private:
  Ui::View *ui;
  Controller *controller;
  Settings *menu;
  void GetAffineValues(AffineInfo &values);
};
}  // namespace s21
#endif  // VIEW_H
