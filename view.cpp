#include "view.h"

#include <QChar>
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>

#include "QtGifImage/qgifimage.h"
#include "ui_view.h"
namespace s21 {

View::View(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View), controller(controller),
      menu(new Settings(controller, this)) {
  ui->setupUi(this);
  QLocale curLocale(QLocale("ru_RU"));
  QLocale::setDefault(curLocale);
  Shadow(40, 0, 5, ui->openFile);
  Shadow(40, 0, 5, ui->settings);
  Shadow(40, 0, 5, ui->rotationDo);
  Shadow(40, 0, 5, ui->moveDo);
  Shadow(40, 0, 5, ui->scaleDo);
  Shadow(40, 0, 5, ui->gifButton);
  Shadow(40, 0, 5, ui->photoButton);
  Color(ui->frame, controller->GetSettings().back_col, "border:2px solid ");
  controller->SetDrawer(ui->openGLWidget);
}

View::~View() { delete ui; }

void View::on_openFile_clicked() {
  QString filename = QFileDialog::getOpenFileName(this, tr("Choose .objfile"),
                                                  "../../../../src/Models",
                                                  tr("OBJ FILES (*.obj)"));
  if (!filename.isEmpty()) {
    controller->SendModelFile(filename.toStdString());
    std::pair<size_t, size_t> sizes = controller->GetModelInfo();
    ui->edgesLine->setText(QString::number(sizes.first));
    ui->verticesLine->setText(QString::number(sizes.second));
    filename = filename.split("/").last();
    ui->fileNameLine->setText(filename);
  }
}

void View::on_settings_clicked() {
  menu->exec();
  Color(ui->frame, QColor(controller->GetSettings().back_col),
        "border:2px solid ");
}

void View::on_photoButton_clicked() {
  QImage screenshot = controller->GetScreenshot();
  const QString format = "jpeg";
  QString default_path = "images";
  QFileDialog save_dialog(this, tr("Сохранить как"), default_path);
  save_dialog.setAcceptMode(QFileDialog::AcceptSave);
  save_dialog.setFileMode(QFileDialog::AnyFile);
  save_dialog.setDirectory(default_path);
  save_dialog.setDefaultSuffix(format);

  QStringList mime_types;
  const QList<QByteArray> ba_mime_types = QImageWriter::supportedMimeTypes();
  for (const QByteArray &bf : ba_mime_types)
    mime_types.append(QLatin1String(bf));
  save_dialog.setMimeTypeFilters(mime_types);
  save_dialog.selectMimeTypeFilter("image/" + format);

  if (save_dialog.exec() == QDialog::Accepted) {
    const QString fname = save_dialog.selectedFiles().first();
    if (!screenshot.save(fname)) {
      QMessageBox::warning(this, tr("Ошибка"),
                           tr("Невозможно сохранить изображение в \"%1\".")
                               .arg(QDir::toNativeSeparators(fname)));
    }
  }
}

void View::on_scaleDo_clicked() {
  controller->Affine(kScale, ui->scaleXVal->value(), ui->scaleYVal->value(),
                     ui->scaleZVal->value());
}

void View::on_rotationDo_clicked() {
  controller->Affine(kRotate, ui->rotationXVal->value(),
                     ui->rotationYVal->value(), ui->rotationZVal->value());
}

void View::on_moveDo_clicked() {
  controller->Affine(kMove, ui->moveXVal->value(), ui->moveYVal->value(),
                     ui->moveZVal->value());
}

void View::on_gifButton_clicked() {
  QString filename = QFileDialog::getSaveFileName(
      this, tr("Save File"), "../../../../", tr("(*.gif)"));
  if (!filename.isEmpty()) {
    AffineInfo affine_values;
    GetAffineValues(affine_values);

    QGifImage gif(controller->GetScreenshot().size());
    gif.setDefaultDelay(100);
    std::vector<QImage> frames = controller->DoAnimation(50, affine_values);

    for (auto &frame : frames)
      gif.addFrame(frame);

    gif.save(filename);
  }
}

void View::GetAffineValues(AffineInfo &values) {
  values[kScale][0] = ui->scaleXVal->value();
  values[kScale][1] = ui->scaleYVal->value();
  values[kScale][2] = ui->scaleZVal->value();
  values[kRotate][0] = ui->rotationXVal->value();
  values[kRotate][1] = ui->rotationYVal->value();
  values[kRotate][2] = ui->rotationZVal->value();
  values[kMove][0] = ui->moveXVal->value();
  values[kMove][1] = ui->moveYVal->value();
  values[kMove][2] = ui->moveZVal->value();
}

} // namespace s21
