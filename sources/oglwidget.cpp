#include "mainwindow.h"

OGLwidget::OGLwidget(QWidget* parent) : QOpenGLWidget(parent) { ; }

void OGLwidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void OGLwidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void OGLwidget::paintGL() {
  ortho();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (copy) {
    transform();
    draw();
    v_dup(&info, copy);
  }
}

void OGLwidget::draw() {
  glVertexPointer(3, GL_DOUBLE, 0, copy);
  glEnableClientState(GL_VERTEX_ARRAY);
  glDrawElements(GL_LINES, info.f_amount * 2, GL_UNSIGNED_INT, info.facets);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void OGLwidget::obj_upload() {
  if (copy) {
    free(copy);
    copy = NULL;
  }
  if (parse(fileName, &info)) {
    emit countTrigger(info.v_amount, info.f_amount);
    copy = (double*)malloc(info.v_amount * 3 * sizeof(double));
    v_dup(&info, copy);
    updateFrame();
  }
}

void OGLwidget::ortho() {
  double d1 = info.minMax[1] - info.minMax[0];
  double d2 = info.minMax[3] - info.minMax[2];
  double d3 = info.minMax[5] - info.minMax[4];

  double d = d1;
  if (d2 > d1) d = d2;
  if (d3 > d2) d = d3;
  double fov = 60.0 * M_PI / 180;
  double near = 5 * (info.minMax[3] / (2 * tan(fov / 2)));
  double cX = (info.minMax[1] + info.minMax[0]) / 2;
  double cY = (info.minMax[3] + info.minMax[2]) / 2;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(cX - d * 0.6, cX + d * 0.6, cY - d * 0.6, cY + d * 0.6, near, 3000);
  glTranslated(0, 0, -near * 3);
}

void OGLwidget::updateFrame() { update(); }

void OGLwidget::transform() {
  if (rot[0]) ft_ox_rotate(copy, info.v_amount, rot[0]);
  if (rot[1]) ft_oy_rotate(copy, info.v_amount, rot[1]);
  if (rot[2]) ft_oz_rotate(copy, info.v_amount, rot[2]);
  if (trans[0]) ft_translate(copy, info.v_amount, 0, trans[0]);
  if (trans[1]) ft_translate(copy, info.v_amount, 1, trans[1]);
  if (trans[2]) ft_translate(copy, info.v_amount, 2, trans[2]);
  if (scale != 1) ft_scale(copy, info.v_amount, scale);
}
