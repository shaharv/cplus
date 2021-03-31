// Based on benchmark code from
// https://stackoverflow.com/questions/22793669/poor-memcpy-performance-on-linux

#include <cstdint>
#include <cstring>
#include <iostream>

#include "benchmark_utils.h"

int benchmark(uint64_t sizeBytes) {

  std::cout << "Buffer size: " << sizeBytes << std::endl;

  // big array to use for testing
  char *p_big_array = NULL;

  // malloc
  {
    Timer timer;
    p_big_array = (char *)malloc(sizeBytes * sizeof(char));
    uint64_t elapsed_ns = timer.elapsedNs();

    if (p_big_array == NULL) {
      std::cerr << "ERROR: malloc of " << sizeBytes << " returned NULL!"
                << std::endl;
      return 1;
    }

    std::cout << "malloc for " << formatBytes(sizeBytes) << " took "
              << elapsed_ns << "ns" << std::endl;
  }

  // memset
  {
    Timer timer;
    memset(p_big_array, 0xF, sizeBytes * sizeof(char));
    uint64_t elapsed_ns = timer.elapsedNs();
    std::cout << "memset for " << formatBytes(sizeBytes) << " took "
              << elapsed_ns << "ns "
              << "(" << formatBytes(sizeBytes / (elapsed_ns / 1.0e9))
              << " bytes/sec)" << std::endl;
  }

  // memcpy
  {
    char *p_dest_array = (char*)malloc(sizeBytes * sizeof(char));
    if (p_dest_array == NULL) {
      std::cerr << "ERROR: malloc of " << sizeBytes << " for memcpy test"
                << " returned NULL!" << std::endl;
      return 1;
    }
    memset(p_dest_array, 0xF, sizeBytes * sizeof(char));

    Timer timer;
    memcpy((uint8_t*)p_dest_array, (uint8_t*)p_big_array,
	       sizeBytes * sizeof(uint8_t));
    uint64_t elapsed_ns = timer.elapsedNs();

    std::cout << "memcpy for " << formatBytes(sizeBytes) << " took "
              << elapsed_ns << "ns "
              << "(" << formatBytes(sizeBytes / (elapsed_ns / 1.0e9))
              << " bytes/sec)" << std::endl;

    // cleanup p_dest_array
    free(p_dest_array);
    p_dest_array = NULL;
  }

  // cleanup
  free(p_big_array);
  std::cout << std::endl;

  return 0;
}

int main(int argc, char *argv[]) {
  uint64_t sizes[] = {
    1024,       // 1KB
    16384,      // 8KB
    1048576,    // 1MB
    16777216,   // 16MB
    268435456,  // 256MB
    1073741824, // 1GB
  };

  if (argc > 1) {
    uint64_t sizeBytes = std::stoull(argv[1]);
    std::cout << "Using buffer size from command line: "
              << formatBytes(sizeBytes) << std::endl;
    benchmark(sizeBytes);
    return 0;
  } else {
    std::cout
        << "To specify a custom buffer size: big_memcpy_test [sizeBytes] \n"
        << "Using built in buffer sizes." << std::endl;
  }

  for (unsigned i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
    benchmark(sizes[i]);
  }

  return 0;
}
