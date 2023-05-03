#ifndef RECEIVERMAPFILE_H
#define RECEIVERMAPFILE_H

#include <Windows.h>

#include <QObject>
#include <QString>

constexpr LPCWSTR RECEIVER_EVENT = L"REVENT";
constexpr LPCWSTR SENDER_EVENT = L"SEVENT";
constexpr LPCWSTR FILE_MAP = L"MYMAP";
constexpr SIZE_T BUF_SIZE = 1024;

class ReceiverMapFile : public QObject {
  Q_OBJECT
 public:
  explicit ReceiverMapFile(QObject* parent = nullptr);
  ~ReceiverMapFile();

  bool tryOpenMapViewFile();
  void checkMessage();

 signals:
  void messageReceived(const QString message);

 private:
  HANDLE receiver_event_;
  HANDLE sender_event_;
  HANDLE file_map_;
  LPVOID buffer_;

  bool openEvent();
  bool openFileMapping();
};

#endif  // RECEIVERMAPFILE_H
