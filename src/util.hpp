#ifndef UTIL_HPP
#define UTIL_HPP
#include <stdint.h>
#include <cstdint>
#include <stdio.h>
#include <fcntl.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <cstring> // for memset
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <random>
#include <algorithm>    // for std::generate





#ifndef ACCESS_HELPERS
#define ACCESS_HELPERS
#define WRITE_BOOL(addr, value)(*(bool*)(addr) = value)
#define WRITE_UINT8(addr, value)(*(uint8_t*)(addr) = value)
#define WRITE_UINT16(addr, value)(*(uint16_t*)(addr) = value)
#define WRITE_UINT32(addr, value)(*(uint32_t*)(addr) = value)
#define WRITE_UINT64(addr, value)(*(uint64_t*)(addr) = value)

#define READ_BOOL(addr)(*(bool*)(addr))
#define READ_UINT8(addr)(*(uint8_t*)(addr))
#define READ_UINT16(addr)(*(uint16_t*)(addr))
#define READ_UINT32(addr)(*(uint32_t*)(addr))
#define READ_UINT64(addr)(*(uint64_t*)(addr))
#endif






void randomize_region_deterministic_int(int *data, size_t size);
std::string print_checksum_i32(int *C, int length);
int open_fd();












#endif