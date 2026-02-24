#include "util.hpp"


void randomize_region_deterministic_int(int *data, size_t size)
 {
    if (!data || size == 0) return;

    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> dist(0, 4096);
    
    std::generate(data, data + size, [&]() {
        return static_cast<int>(dist(gen));
    });
}





std::string print_checksum_i32(int *C, int length)
{
  int chsum = 0;
  for (int i = 0; i < length; i++)
  {
    chsum += C[i];
  }
    
  
  return std::to_string(chsum);
}


int open_fd() {
  int fd = open("/dev/mem", O_RDWR | O_SYNC);
  if (fd == -1) {
    printf("Can't open /dev/mem.\n");
    exit(0);
  }
  return fd;
}