#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

#include "controller.h"
namespace Ui {
class Settings;
}
namespace s21 {
void Shadow(int blurSize, int offsetx, int offsety, QObject *parent);
void Color(QWidget *sender, QColor color, QString prop);

class Settings : public QDialog {
  Q_OBJECT

public:
  explicit Settings(Controller *controller, QWidget *parent = nullptr);
  ~Settings();

public slots:
  void applyOldSettings();

signals:
  void updateSettings();

private slots:
  void ChangeEdgesColor();
  void ChangeVerColor();
  void ChangeBackColor();

  void parallelRadio_clicked();
  void centrallRadio_clicked();

  void solidRadio_clicked();
  void dashedRadio_clicked();

  void noneRadio_clicked();
  void circleRadio_clicked();
  void squareRadio_clicked();

private:
  Ui::Settings *ui;
  Controller *controller;
  SettingsParser::Settings &settings;

protected:
  void closeEvent(QCloseEvent *);
};
} // namespace s21

#endif // SETTINGS_H
