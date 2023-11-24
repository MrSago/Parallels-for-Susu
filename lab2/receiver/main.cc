#include <Windows.h>

#include <iostream>
#include <string>

#include "lab2/constants.h"

int main() {
  HANDLE hEventMessageSended, hEventFileMapOpened;
  while (TRUE) {
    std::cout << "Trying to open events...";
    hEventMessageSended =
        OpenEvent(EVENT_ALL_ACCESS, false, kEventMessageSendedName);
    hEventFileMapOpened =
        OpenEvent(EVENT_ALL_ACCESS, false, kEventFileMapOpenedName);
    if (hEventMessageSended && hEventFileMapOpened) break;
    Sleep(500);
  }
  std::cout << "\nOpenEvent success.\n";

  HANDLE hFileMap;
  while (TRUE) {
    std::cout << "Trying to open file mapping...";
    hFileMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, kMapName);
    if (hFileMap) break;
    Sleep(500);
    std::cout << '\n';
  }
  SetEvent(hEventFileMapOpened);
  std::cout << "\nOpenFileMapping success.\n";

  LPVOID pointer = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, kBufSize);
  if (!pointer) {
    std::cout << "MapViewOfFile failed, GLE=" << GetLastError() << '\n';
    CloseHandle(hEventMessageSended);
    CloseHandle(hEventFileMapOpened);
    CloseHandle(hFileMap);
    return -1;
  }
  std::cout << "MapViewOfFile success.\n";

  std::cout << "Wait when sender write message...";
  if (WaitForSingleObject(hEventMessageSended, INFINITE) == WAIT_FAILED) {
    std::cout << "\nWaitForSingleObject failed, GLE=" << GetLastError() << '\n';
    CloseHandle(hEventMessageSended);
    CloseHandle(hEventFileMapOpened);
    UnmapViewOfFile(pointer);
    CloseHandle(hFileMap);
    return -1;
  }

  std::cout << "\nMessage from sender: " << static_cast<char*>(pointer) << '\n';

  CloseHandle(hEventMessageSended);
  CloseHandle(hEventFileMapOpened);
  UnmapViewOfFile(pointer);
  CloseHandle(hFileMap);
  return 0;
}