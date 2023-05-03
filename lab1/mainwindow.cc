#include "lab1/mainwindow.h"

#include <QMainWindow>
#include <QString>
#include <QWidget>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  shared_state_ = new SharedState;
  thread_generate_ = new ThreadGenerateString(shared_state_, 1000, 1, this);
  thread_generate2_ = new ThreadGenerateString(shared_state_, 1000, 2, this);
  thread_reader_ = new ThreadReaderString(shared_state_, 1000, this);

  connect(thread_reader_, &ThreadReaderString::updateGui, this,
          &MainWindow::onAddItemToList);

  thread_generate_->start();
  thread_generate2_->start();
  thread_reader_->start();

  ui_->setupUi(this);
}

MainWindow::~MainWindow() {
  thread_generate_->terminate();
  thread_generate_->wait();
  delete thread_generate_;

  thread_generate2_->terminate();
  thread_generate2_->wait();
  delete thread_generate2_;

  thread_reader_->terminate();
  thread_reader_->wait();
  delete thread_reader_;

  delete shared_state_;
  delete ui_;
}

void MainWindow::onAddItemToList(const int nThread, const int val) {
  ui_->listWidget->addItem(
      QString("Writer[%1]: %2")
          .arg(QString::number(nThread), QString::number((val))));
  ui_->listWidget->scrollToBottom();
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
  thread_generate_->setDelay(value);
  ui_->label_3->setText(QString::number(value));
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value) {
  thread_reader_->setDelay(value);
  ui_->label_4->setText(QString::number(value));
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value) {
  thread_generate2_->setDelay(value);
  ui_->label_6->setText(QString::number(value));
}
