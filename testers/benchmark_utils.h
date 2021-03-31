// Source: https://stackoverflow.com/questions/22793669/poor-memcpy-performance-on-linux

#pragma once

#include <chrono>
#include <cstring>
#include <iostream>

class Timer {
public:
  Timer() : mStart(), mStop() { update(); }
  void update() {
    mStart = std::chrono::high_resolution_clock::now();
    mStop = mStart;
  }
  double elapsedNs() {
    mStop = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds elapsed_ns =
        std::chrono::duration_cast<std::chrono::nanoseconds>(mStop - mStart);
    return elapsed_ns.count();
  }

private:
  std::chrono::high_resolution_clock::time_point mStart;
  std::chrono::high_resolution_clock::time_point mStop;
};

static std::string formatBytes(uint64_t bytes) {
  static const int num_suffix = 5;
  static const char *suffix[num_suffix] = {"B", "KB", "MB", "GB", "TB"};
  double dbl_s_byte = bytes;
  int i = 0;

  for (; (int)(bytes / 1024.) > 0 && i < num_suffix; ++i, bytes /= 1024.) {
    dbl_s_byte = bytes / 1024.0;
  }

  const int buf_len = 64;
  char buf[buf_len];

  // use snprintf so there is no buffer overrun
  int res = snprintf(buf, buf_len, "%0.2f%s", dbl_s_byte, suffix[i]);

  // snprintf returns number of characters that would have been written if n
  // had been sufficiently large, not counting the terminating null character.
  // if an encoding error occurs, a negative number is returned.
  if (res >= 0) {
    return std::string(buf);
  }

  return std::string();
}
