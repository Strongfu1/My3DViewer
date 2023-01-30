#include "Settings.h"

#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QGraphicsDropShadowEffect>
#include <QStringList>

#include "ui_settings.h"
namespace s21 {
Settings::Settings(Controller *controller, QWidget *parent)
    : QDialog(parent), ui(new Ui::Settings), controller(controller),
      settings(controller->GetSettings()) {
  ui->setupUi(this);
  controller->ParsOldSettings();
  applyOldSettings();
  connect(ui->parallelRadio, &QRadioButton::clicked, this,
          &Settings::parallelRadio_clicked);
  connect(ui->centralRadio, &QRadioButton::clicked, this,
          &Settings::centrallRadio_clicked);
  connect(ui->solidRadio, &QRadioButton::clicked, this,
          &Settings::solidRadio_clicked);
  connect(ui->dashedRadio, &QRadioButton::clicked, this,
          &Settings::dashedRadio_clicked);
  connect(ui->noneRadio, &QRadioButton::clicked, this,
          &Settings::noneRadio_clicked);
  connect(ui->circleRadio, &QRadioButton::clicked, this,
          &Settings::circleRadio_clicked);
  connect(ui->squareRadio, &QRadioButton::clicked, this,
          &Settings::squareRadio_clicked);
  connect(ui->edgesColor, &QToolButton::clicked, this,
          &Settings::ChangeEdgesColor);
  connect(ui->verticesColor, &QToolButton::clicked, this,
          &Settings::ChangeVerColor);
  connect(ui->backgroundColor, &QToolButton::clicked, this,
          &Settings::ChangeBackColor);
  ui->thickness->setSuffix("  px");
  ui->verticesSize->setSuffix("  px");
}

Settings::~Settings() { delete ui; }

void Settings::applyOldSettings() {
  Color(ui->backgroundColor, settings.back_col, "background-color: ");
  Color(ui->verticesColor, settings.vert_col, "background-color: ");
  Color(ui->edgesColor, settings.edges_col, "background-color: ");

  if (settings.projection == kCentral)
    ui->centralRadio->setChecked(true);
  else
    ui->parallelRadio->setChecked(true);
  if (settings.edges_type == kSolid)
    ui->solidRadio->setChecked(true);
  else
    ui->dashedRadio->setChecked(true);
  if (settings.vert_type == kInvisible)
    ui->noneRadio->setChecked(true);
  else if (settings.vert_type == kCircle)
    ui->circleRadio->setChecked(true);
  else
    ui->squareRadio->setChecked(true);
  ui->verticesSize->setValue(settings.vert_size);
  ui->thickness->setValue(settings.edges_size);
}

void Settings::parallelRadio_clicked() { settings.projection = kParallel; }

void Settings::centrallRadio_clicked() { settings.projection = kCentral; }

void Settings::solidRadio_clicked() { settings.edges_type = kSolid; }

void Settings::dashedRadio_clicked() { settings.edges_type = kDashed; }

void Settings::noneRadio_clicked() { settings.vert_type = kInvisible; }

void Settings::circleRadio_clicked() { settings.vert_type = kCircle; }

void Settings::squareRadio_clicked() { settings.vert_type = kSquare; }

void Shadow(int blurSize, int offsetx, int offsety, QObject *parent) {
  QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(parent);
  shadow->setBlurRadius(blurSize);
  shadow->setOffset(offsetx, offsety);
  qobject_cast<QWidget *>(parent)->setGraphicsEffect(shadow);
}

void Color(QWidget *sender, QColor color, QString property) {
  QString style = sender->styleSheet();
  while (style[style.size() - 1] != '\n')
    style.chop(1);
  sender->setStyleSheet(style + property + color.name() + ";}");
}

void Settings::ChangeEdgesColor() {
  settings.edges_col = QColorDialog::getColor();
  Color(ui->edgesColor, settings.edges_col, "background-color:");
}

void Settings::ChangeVerColor() {
  settings.vert_col = QColorDialog::getColor();
  Color(ui->verticesColor, settings.vert_col, "background-color:");
}

void Settings::ChangeBackColor() {
  settings.back_col = QColorDialog::getColor();
  Color(ui->backgroundColor, settings.back_col, "background-color:");
}

void Settings::closeEvent(QCloseEvent *) {
  settings.edges_size = ui->thickness->value();
  settings.vert_size = ui->verticesSize->value();
}

} // namespace s21
