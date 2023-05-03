#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWaitCondition>
#include <QWidget>

#include "lab1/sharedstate.h"
#include "lab1/threadgeneratestring.h"
#include "lab1/threadreaderstring.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 public slots:
  void onAddItemToList(const int nThread, const int val);

 private slots:
  void on_horizontalSlider_valueChanged(int value);

  void on_horizontalSlider_2_valueChanged(int value);

  void on_horizontalSlider_3_valueChanged(int value);

 private:
  Ui::MainWindow* ui_;
  SharedState* shared_state_;
  ThreadGenerateString* thread_generate_;
  ThreadGenerateString* thread_generate2_;
  ThreadReaderString* thread_reader_;
};
#endif  // MAINWINDOW_H
