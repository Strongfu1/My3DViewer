#ifndef DRAWER_H
#define DRAWER_H
#ifdef __APPLE__
// Defined before OpenGL and GLUT includes to avoid deprecation messages
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#endif

#include <QtOpenGLWidgets/QOpenGLWidget>

#include "ModelReader.h"
#include "parsSavedSettings.h"
namespace s21 {
class Drawer : public QOpenGLWidget {
  Q_OBJECT
public:
  explicit Drawer(QWidget *parent);
  void SetModel(const Model &model);
  void SetSettings(const SettingsParser::Settings &settings);
  std::pair<size_t, size_t> ModelInfo() const;
  QImage GetScreenshot();
  std::vector<double> &Vertices();

public slots:
  //  void getSettings(saveSettings *settings);
  //  void updateSettings();
  //  void affineUpdate();

private:
  float x_rot_, y_rot_;
  QPoint mpos_;
  SettingsParser::Settings &settings_;
  bool active_proj_;
  Model model_;
  double zoom_;
  void drawModel();

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;
};
} // namespace s21

#endif // DRAWER_H
