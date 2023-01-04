#include <QApplication>

#include "controller.h"
#include "facade.h"
#include "view.h"

std::string s21::SettingsParser::settings_file_ = SETTINGSNAME;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Facade facade;
  s21::Controller controller(&facade);
  s21::View w(&controller);
  w.show();
  return a.exec();
}
