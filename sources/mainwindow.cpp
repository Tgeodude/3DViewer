#include "mainwindow.h"

#include "QFileDialog"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(this, &MainWindow::openTrigger, ui->widget, &OGLwidget::obj_upload);
  connect(ui->widget, &OGLwidget::countTrigger, this, &MainWindow::setVF);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setVF(size_t v, size_t f) {
  ui->label_vertices->setText("Number of vertices: " + QString::number(v));
  ui->label_edges->setText("Number of edges: " + QString::number(f));
}

void MainWindow::on_toolButton_clicked() {
  ui->doubleSpinBox_scale->setValue(1);
  ui->doubleSpinBox_transX->setValue(0);
  ui->doubleSpinBox_transY->setValue(0);
  ui->doubleSpinBox_transZ->setValue(0);
  ui->horizontalSlider_rotX->setValue(0);
  ui->horizontalSlider_rotY->setValue(0);
  ui->horizontalSlider_rotZ->setValue(0);
  QString fileName =
      QFileDialog::getOpenFileName(this, "Open File", "~/", "*.obj");
  if (fileName.isNull()) return;
  setWindowTitle("3DViewer_v1.0 - " + fileName);
  QByteArray tmp = fileName.toLocal8Bit();
  const char *str = tmp.data();
  ui->widget->fileName = str;
  emit openTrigger();
}

void MainWindow::on_horizontalSlider_rotX_valueChanged(int value) {
  ui->label_degreeX->setText(QString::number(value) + "°");
  ui->widget->rot[0] = (double)value / 180 * M_PI;
  ui->widget->updateFrame();
}

void MainWindow::on_horizontalSlider_rotY_valueChanged(int value) {
  ui->label_degreeY->setText(QString::number(value) + "°");
  ui->widget->rot[1] = (double)value / 180 * M_PI;
  ui->widget->updateFrame();
}

void MainWindow::on_horizontalSlider_rotZ_valueChanged(int value) {
  ui->label_degreeZ->setText(QString::number(value) + "°");
  ui->widget->rot[2] = (double)value / 180 * M_PI;
  ui->widget->updateFrame();
}

void MainWindow::on_doubleSpinBox_transX_valueChanged(double arg1) {
  ui->widget->trans[0] = arg1;
  ui->widget->updateFrame();
}

void MainWindow::on_doubleSpinBox_transY_valueChanged(double arg1) {
  ui->widget->trans[1] = arg1;
  ui->widget->updateFrame();
}

void MainWindow::on_doubleSpinBox_transZ_valueChanged(double arg1) {
  ui->widget->trans[2] = arg1;
  ui->widget->updateFrame();
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1) {
  ui->widget->scale = arg1;
  ui->widget->updateFrame();
}
