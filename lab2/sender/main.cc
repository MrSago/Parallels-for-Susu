#include <Windows.h>

#include <iostream>
#include <string>

#include "lab2/constants.h"

int main() {
  char message[] = "Hello!";

  HANDLE hEventMessageSended =
      CreateEvent(NULL, false, false, kEventMessageSendedName);
  HANDLE hEventFileMapOpened =
      CreateEvent(NULL, false, false, kEventFileMapOpenedName);
  if (!hEventMessageSended || !hEventFileMapOpened) {
    std::cout << "OpenEvent failed, GLE=" << GetLastError() << '\n';
    return -1;
  }
  std::cout << "Events created.\n";

  HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL,
                                      PAGE_READWRITE, 0, kBufSize, kMapName);
  if (!hFileMap) {
    hFileMap = NULL;
    std::cout << "CreateFileMapped failed, GLE=" << GetLastError() << '\n';
    CloseHandle(hEventMessageSended);
    CloseHandle(hEventFileMapOpened);
    return -1;
  }
  std::cout << "CreateFileMapped success.\n";

  LPVOID pointer = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, kBufSize);
  if (!pointer) {
    std::cout << "MapViewOfFile failed, GLE=" << GetLastError() << '\n';
    CloseHandle(hEventMessageSended);
    CloseHandle(hEventFileMapOpened);
    CloseHandle(hFileMap);
    return -1;
  }
  std::cout << "MapViewOfFile success.\n";

  CopyMemory(pointer, message, sizeof(message));
  SetEvent(hEventMessageSended);
  std::cout << "Message written.\n";

  std::cout << "Wait when receiver open map file...";
  if (WaitForSingleObject(hEventFileMapOpened, INFINITE) == WAIT_FAILED) {
    std::cout << "WaitForSingleObject failed, GLE=" << GetLastError() << '\n';
    CloseHandle(hEventMessageSended);
    CloseHandle(hEventFileMapOpened);
    CloseHandle(hFileMap);
    return -1;
  }
  std::cout << "\nReceiver has open map file. Now I can exit.\n";

  CloseHandle(hEventMessageSended);
  CloseHandle(hEventFileMapOpened);
  UnmapViewOfFile(pointer);
  CloseHandle(hFileMap);
  return 0;
}