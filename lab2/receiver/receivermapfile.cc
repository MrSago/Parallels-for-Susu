#include "lab2/receiver/receivermapfile.h"

#include <Windows.h>

#include <QObject>
#include <QString>

ReceiverMapFile::ReceiverMapFile(QObject* parent)
    : receiver_event_(NULL),
      sender_event_(NULL),
      file_map_(NULL),
      buffer_(NULL),
      QObject{parent} {}

ReceiverMapFile::~ReceiverMapFile() {
  if (receiver_event_) CloseHandle(receiver_event_);
  if (sender_event_) CloseHandle(sender_event_);
  if (buffer_) UnmapViewOfFile(buffer_);
  if (file_map_) CloseHandle(file_map_);
}

bool ReceiverMapFile::tryOpenMapViewFile() {
  if (!openEvent() || !openFileMapping()) {
    return false;
  }

  if (!buffer_) {
    buffer_ = MapViewOfFile(file_map_, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
  }

  return buffer_ && SetEvent(receiver_event_);
}

void ReceiverMapFile::checkMessage() {
  if (!receiver_event_ || !sender_event_ || !file_map_ || !buffer_) {
    return;
  }

  if (WaitForSingleObject(sender_event_, 0) == WAIT_OBJECT_0) {
    emit messageReceived(QString(static_cast<QChar*>(buffer_)));
    SetEvent(receiver_event_);
  }
}

bool ReceiverMapFile::openEvent() {
  if (!receiver_event_)
    receiver_event_ = OpenEvent(EVENT_ALL_ACCESS, false, RECEIVER_EVENT);
  if (!sender_event_)
    sender_event_ = OpenEvent(EVENT_ALL_ACCESS, false, SENDER_EVENT);
  return receiver_event_ && sender_event_;
}

bool ReceiverMapFile::openFileMapping() {
  return (file_map_ = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, FILE_MAP));
}
