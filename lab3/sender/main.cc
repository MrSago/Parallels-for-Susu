#include <Windows.h>

#include <iostream>
#include <string>

#include "lab3/constants.h"

int main() {
  char buffer[kBufSize];

  HANDLE hEventSended = CreateEvent(NULL, false, false, kEventSendedName);
  HANDLE hEventReceived = CreateEvent(NULL, false, false, kEventReceivedName);
  if (hEventSended == NULL || hEventReceived == NULL) {
    std::cout << "CreateEvent failed, GLE=" << GetLastError() << '\n';
    return -1;
  }

  HANDLE hPipe =
      CreateNamedPipe("\\\\.\\pipe\\Pipe", PIPE_ACCESS_DUPLEX,
                      PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                      PIPE_UNLIMITED_INSTANCES, sizeof(buffer), sizeof(buffer),
                      NMPWAIT_USE_DEFAULT_WAIT, NULL);
  if (hPipe == INVALID_HANDLE_VALUE) {
    std::cout << "CreateNamedPipe failed, GLE=" << GetLastError() << '\n';
    CloseHandle(hEventSended);
    CloseHandle(hEventReceived);
    return -1;
  }

  std::cout << "Waiting for client connection...\n";
  BOOL result = ConnectNamedPipe(hPipe, NULL);
  if (!result) {
    std::cout << "ConnectNamedPipe failed, GLE=" << GetLastError() << '\n';
    CloseHandle(hPipe);
    CloseHandle(hEventSended);
    CloseHandle(hEventReceived);
    return -1;
  }

  std::cout << "Client connected.\n";

  for (int i = 0; i < kCountIterations; ++i) {
    std::string message = std::string("Hello number: ") + std::to_string(i + 1);
    memcpy(buffer, message.c_str(), message.size() + 1);

    DWORD dwWrite;
    result = WriteFile(hPipe, buffer, strlen(buffer) + 1, &dwWrite, NULL);
    if (!result) {
      std::cout << "WriteFile failed, GLE=" << GetLastError() << '\n';
      CloseHandle(hPipe);
      CloseHandle(hEventSended);
      CloseHandle(hEventReceived);
      return -1;
    }

    std::cout << "Message sended!\n";
    SetEvent(hEventSended);
    Sleep(kWaitIntervalMs);

    if (WaitForSingleObject(hEventReceived, INFINITE) != WAIT_OBJECT_0) {
      std::cout << "WaitForSingleObject failed, GLE=" << GetLastError() << '\n';
      CloseHandle(hPipe);
      CloseHandle(hEventSended);
      CloseHandle(hEventReceived);
      return -1;
    }
  }

  CloseHandle(hPipe);
  CloseHandle(hEventSended);
  CloseHandle(hEventReceived);

  return 0;
}