#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "oglwidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_toolButton_clicked();

  void on_horizontalSlider_rotX_valueChanged(int value);

  void on_horizontalSlider_rotY_valueChanged(int value);

  void on_horizontalSlider_rotZ_valueChanged(int value);

  void on_doubleSpinBox_transX_valueChanged(double arg1);

  void on_doubleSpinBox_transY_valueChanged(double arg1);

  void on_doubleSpinBox_transZ_valueChanged(double arg1);

  void on_doubleSpinBox_scale_valueChanged(double arg1);

 private:
  Ui::MainWindow *ui;
  void setVF(size_t v, size_t f);

 signals:
  void openTrigger();
};
#endif  // MAINWINDOW_H
