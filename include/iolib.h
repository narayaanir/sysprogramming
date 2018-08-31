#include <unistd.h> // Unistd should always come first
// Common headers
#include <string.h>
#include <stdlib.h>
// File I/O related libs
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


#ifdef __cplusplus
extern "C" {
#endif

  // Writes to file descriptor provided
  extern void cust_write(const char*, const int& fd);

  // Reads from console and writes to console
  extern void cust_read();

  extern int cust_open(const char*, const int&);

  extern int cust_close(const int&);

  // Read fron console and write to a file using system calls
  extern void console_file_write(const char*);

  extern void copy(const char*, const char*);

#ifdef __cplusplus
}
#endif
