#include "Drawer.h"

#include <QMouseEvent>
#include <QPainterPath>
namespace s21 {
Drawer::Drawer(QWidget *parent)
    : QOpenGLWidget(parent),
      settings_(SettingsParser::GetInstance()->GetSettings()),
      active_proj_(!settings_.projection), zoom_(1) {}

void Drawer::resizeGL(int w, int h) { // Channging size of window
  glViewport(0, 0, w, h);
  QPainterPath path;
  path.addRoundedRect(this->rect(), 15, 15);
  QRegion mask = QRegion(path.toFillPolygon().toPolygon());
  this->setMask(mask);
}

void Drawer::paintGL() {
  glClearColor(settings_.back_col.redF(), settings_.back_col.greenF(),
               settings_.back_col.blueF(), 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (active_proj_ != settings_.projection) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (settings_.projection == kCentral) {
      glOrtho(-5, 5, -5, 5, -100000, 10000);
      active_proj_ = kCentral;
    } else {
      glFrustum(-0.1, 0.1, -0.1, 0.1, 0.5, 100);
      active_proj_ = kParallel;
    }
    glMatrixMode(GL_MODELVIEW);
  }
  if (settings_.vert_type == kCircle) {
    glEnable(GL_POINT_SMOOTH);
  } else if (settings_.vert_type == kSquare) {
    glDisable(GL_POINT_SMOOTH);
  }

  glLineWidth(settings_.edges_size);
  if (settings_.edges_type == kDashed) {
    glLineStipple(1, 0xFF); // Dashed lines
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glTranslatef(0, 0, -2);
  glScaled(zoom_, zoom_, zoom_);
  glRotatef(x_rot_, 1, 0, 0);
  glRotatef(y_rot_, 0, 1, 0);
  drawModel();
}

void Drawer::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Drawer::drawModel() {
  glEnableClientState(GL_VERTEX_ARRAY); // Allowing OpenGl to use buffer
  glVertexPointer(3, GL_DOUBLE, 0, model_.vertices.data());
  glColor3f(settings_.edges_col.redF(), settings_.edges_col.greenF(),
            settings_.edges_col.blueF());
  glDrawElements(GL_LINES, model_.polygons.size(), GL_UNSIGNED_INT,
                 model_.polygons.data());
  if (settings_.vert_type != kInvisible) {
    glColor3f(settings_.vert_col.redF(), settings_.vert_col.greenF(),
              settings_.vert_col.blueF());
    glPointSize(settings_.vert_size);
    glDrawElements(GL_POINTS, model_.polygons.size(), GL_UNSIGNED_INT,
                   model_.polygons.data());
  }
  glDisableClientState(GL_VERTEX_ARRAY);
}

void Drawer::wheelEvent(QWheelEvent *mo) {
  QPoint numDegrees = mo->angleDelta();
  if (numDegrees.y() < 0) {
    zoom_ /= 1.1;
  } else {
    zoom_ *= 1.1;
  }
  update();
}

void Drawer::mousePressEvent(QMouseEvent *mo) { mpos_ = mo->pos(); }

void Drawer::mouseMoveEvent(QMouseEvent *mo) {
  x_rot_ += 0.5 / M_PI * (mo->pos().y() - mpos_.y()); //  Rotation
  y_rot_ += 0.5 / M_PI * (mo->pos().x() - mpos_.x());
  update();
}

void Drawer::SetSettings(const SettingsParser::Settings &settings) {
  settings_ = settings;
}

void Drawer::SetModel(const Model &model) { model_ = model; }

std::pair<size_t, size_t> Drawer::ModelInfo() const {
  return std::pair<size_t, size_t>(model_.polygons.size() / 2,
                                   model_.vertices.size() / 3);
}

QImage Drawer::GetScreenshot() { return grabFramebuffer(); }

std::vector<double> &Drawer::Vertices() { return model_.vertices; }

} // namespace s21
