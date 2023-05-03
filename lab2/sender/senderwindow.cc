#include "lab2/sender/senderwindow.h"

#include "./ui_senderwindow.h"

SenderWindow::SenderWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::SenderWindow),
      smf_(new SenderMapFile(this)) {
  ui_->setupUi(this);
  connect(ui_->senderLineEdit, &QLineEdit::returnPressed, this,
          &SenderWindow::on_sendButton_clicked);
}

SenderWindow::~SenderWindow() {
  delete smf_;
  delete ui_;
}

void SenderWindow::on_sendButton_clicked() {
  QString msg = ui_->senderLineEdit->text();
  if (msg.isEmpty()) {
    return;
  }

  ui_->senderLineEdit->setText("");
  if (smf_->sendMessage(msg)) {
    ui_->senderListWidget->addItem(msg);
    ui_->senderListWidget->scrollToBottom();
  }
}
