#include <Windows.h>

#include <iostream>
#include <string>

#include "lab3/constants.h"

int main() {
  char buffer[kBufSize];

  HANDLE hPipe =
      CreateNamedPipe(kPipeName, PIPE_ACCESS_OUTBOUND,
                      PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                      PIPE_UNLIMITED_INSTANCES, sizeof(buffer), sizeof(buffer),
                      NMPWAIT_USE_DEFAULT_WAIT, NULL);
  if (hPipe == INVALID_HANDLE_VALUE) {
    std::cout << "CreateNamedPipe failed, GLE=" << GetLastError() << '\n';
    return -1;
  }

  std::cout << "Waiting for client connection...\n";
  BOOL result = ConnectNamedPipe(hPipe, NULL);
  if (!result) {
    std::cout << "ConnectNamedPipe failed, GLE=" << GetLastError() << '\n';
    CloseHandle(hPipe);
    return -1;
  }
  std::cout << "Client connected.\n";

  for (int i = 0; i < kCountIterations; ++i) {
    std::string message = std::string("Hello number: ") + std::to_string(i + 1);
    CopyMemory(buffer, message.c_str(), message.size() + 1);

    DWORD dwWrite;
    result = WriteFile(hPipe, buffer, strlen(buffer) + 1, &dwWrite, NULL);
    if (!result) {
      std::cout << "WriteFile failed, GLE=" << GetLastError() << '\n';
      CloseHandle(hPipe);
      return -1;
    }

    std::cout << "Message sended!\n";
    Sleep(kWaitIntervalMs);
  }

  CloseHandle(hPipe);
  return 0;
}