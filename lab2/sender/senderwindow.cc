#include "lab2/sender/senderwindow.h"

#include "./ui_senderwindow.h"

SenderWindow::SenderWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(new Ui::SenderWindow),
      smf_(new SenderMapFile(this)),
      waitReceived(new QTimer(this)) {
  ui_->setupUi(this);
  connect(ui_->senderLineEdit, &QLineEdit::returnPressed, this,
          &SenderWindow::onSendButtonClicked);
  connect(waitReceived, &QTimer::timeout, this,
          &SenderWindow::waitMessageReceived);
}

SenderWindow::~SenderWindow() {
  if (smf_) delete smf_;
  delete ui_;
}

void SenderWindow::onSendButtonClicked() {
  QString msg = ui_->senderLineEdit->text();
  if (!smf_ || msg.isEmpty()) {
    return;
  }

  ui_->senderLineEdit->setText("");
  if (smf_->sendMessage(msg)) {
    ui_->senderListWidget->addItem(msg);
    ui_->senderListWidget->scrollToBottom();
    ui_->senderStatusBar->showMessage(
        "Message sended!");
    ui_->senderLineEdit->setEnabled(false);
    ui_->sendButton->setEnabled(false);
    // waitReceived->start(100);
    // this->close();
  }
}

void SenderWindow::waitMessageReceived() {
  if (smf_->checkMessageReceived()) {
    waitReceived->stop();
    ui_->senderStatusBar->showMessage("Message successful received!");
    delete smf_, smf_ = nullptr;
  }
}
