#include <Windows.h>

#include <iostream>
#include <string>

#include "lab3/constants.h"

int main() {
  char buffer[kBufSize];

  HANDLE hEventSended = OpenEvent(EVENT_ALL_ACCESS, false, kEventSendedName);
  HANDLE hEventReceived =
      OpenEvent(EVENT_ALL_ACCESS, false, kEventReceivedName);
  if (hEventSended == NULL || hEventReceived == NULL) {
    std::cout << "OpenEvent failed, GLE=" << GetLastError() << '\n';
    return -1;
  }

  HANDLE hPipe = CreateFile("\\\\.\\pipe\\Pipe", GENERIC_READ, 0, NULL,
                            OPEN_EXISTING, 0, NULL);
  if (hPipe == INVALID_HANDLE_VALUE) {
    std::cout << "CreateFile failed, GLE=" << GetLastError() << '\n';
    CloseHandle(hEventSended);
    CloseHandle(hEventReceived);
    return -1;
  }

  std::cout << "Connected.\n";

  for (int i = 0; i < kCountIterations; ++i) {
    if (WaitForSingleObject(hEventSended, INFINITE) != WAIT_OBJECT_0) {
      std::cout << "WaitForSingleObject failed, GLE=" << GetLastError() << '\n';
      CloseHandle(hPipe);
      CloseHandle(hEventSended);
      CloseHandle(hEventReceived);
      return -1;
    }

    DWORD dwRead;
    BOOL result = ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL);
    if (!result) {
      std::cout << "ReadFile failed, GLE=" << GetLastError() << '\n';
      CloseHandle(hPipe);
      CloseHandle(hEventSended);
      CloseHandle(hEventReceived);
      return -1;
    }

    std::cout << "Received: " << buffer << '\n';
    SetEvent(hEventReceived);
  }

  CloseHandle(hPipe);
  CloseHandle(hEventSended);
  CloseHandle(hEventReceived);

  return 0;
}