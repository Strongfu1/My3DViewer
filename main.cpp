#include <QApplication>

#include "Controller/Controller/Controller.h"
#include "Controller/Facade/Facade.h"
#include "View/MainWindow/View.h"

std::string s21::SettingsParser::settings_file_ = SETTINGSNAME;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Facade Facade;
  s21::Controller Controller(&Facade);
  s21::View w(&Controller);
  w.show();
  return a.exec();
}
