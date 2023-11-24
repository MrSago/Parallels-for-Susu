#include <Windows.h>

#include <iostream>
#include <string>

#include "lab3/constants.h"

int main() {
  char buffer[kBufSize];

  HANDLE hPipe;
  while (TRUE) {
    std::cout << "Trying to connect to server...";
    hPipe =
        CreateFile(kPipeName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hPipe != INVALID_HANDLE_VALUE) break;
    Sleep(kWaitIntervalMs);
    std::cout << '\n';
  }
  std::cout << "\nConnected.\n";

  for (int i = 0; i < kCountIterations; ++i) {
    DWORD dwRead;
    BOOL result = ReadFile(hPipe, buffer, sizeof(buffer), &dwRead, NULL);
    if (!result) {
      std::cout << "ReadFile failed, GLE=" << GetLastError() << '\n';
      CloseHandle(hPipe);
      return -1;
    }
    std::cout << "Received: " << buffer << '\n';
  }

  CloseHandle(hPipe);
  return 0;
}