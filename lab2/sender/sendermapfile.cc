#include "lab2/sender/sendermapfile.h"

#include <Windows.h>

#include <QObject>
#include <QString>
#include <algorithm>

SenderMapFile::SenderMapFile(QObject* parent)
    : receiver_event_(CreateEvent(NULL, false, false, RECEIVER_EVENT)),
      sender_event_(CreateEvent(NULL, false, false, SENDER_EVENT)),
      file_map_(CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0,
                                  BUF_SIZE, FILE_MAP)),
      buffer_(MapViewOfFile(file_map_, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE)),
      reserved(false),
      QObject{parent} {}

SenderMapFile::~SenderMapFile() {
  if (receiver_event_) CloseHandle(receiver_event_);
  if (sender_event_) CloseHandle(sender_event_);
  if (buffer_) UnmapViewOfFile(buffer_);
  if (file_map_) CloseHandle(file_map_);
}

WINBOOL SenderMapFile::sendMessage(const QString& message) {
  if (!receiver_event_ || !sender_event_ || !file_map_ || !buffer_) {
    return false;
  }

  if (!reserved && WaitForSingleObject(receiver_event_, 0) == WAIT_OBJECT_0) {
    reserved = true;
  }

  if (reserved) {
    CopyMemory(buffer_, message.data(),
               std::min((message.size() + 1) * sizeof(QChar), BUF_SIZE));
    reserved = false;
    return SetEvent(sender_event_);
  }

  return false;
}
