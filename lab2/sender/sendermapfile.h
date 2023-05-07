#ifndef SENDERMAPFILE_H
#define SENDERMAPFILE_H

#include <Windows.h>

#include <QObject>
#include <QString>

constexpr LPCWSTR RECEIVER_EVENT = L"REVENT";
constexpr LPCWSTR SENDER_EVENT = L"SEVENT";
constexpr LPCWSTR FILE_MAP = L"MYMAP";
constexpr SIZE_T BUF_SIZE = 1024;

class SenderMapFile : public QObject {
  Q_OBJECT
 public:
  explicit SenderMapFile(QObject* parent = nullptr);
  ~SenderMapFile();

  WINBOOL sendMessage(const QString& message);
  WINBOOL checkMessageReceived();

 private:
  HANDLE receiver_event_;
  HANDLE sender_event_;
  HANDLE file_map_;
  LPVOID buffer_;
};

#endif  // SENDERMAPFILE_H
