#include "iolib.h"

// Standard scale
#define BUFFERSIZE 256
// Large scale
#define LARGE_BUFFERSIZE 1024*1024


void cust_write(const char* data, const int& fd)
{
  if ((write(fd, data, (size_t) strlen(data))) != strlen(data))
    {
      write(2, "A write error has occurred\n", 27);
      exit(2);
    }
}


/************************************************
 Buffers 256 bytes before issuing a system call
*************************************************/
void cust_read()
{
  char buffer[BUFFERSIZE];
  size_t read_size = read(0, buffer, sizeof(buffer));
  if (read_size == -1)
    write(2, "A read error occurred\n", 22);
  cust_write(buffer, 1);
}


int cust_open(const char* i_in, const int& i_oflags)
{
  int i_fd = open(i_in, i_oflags);
  if (i_fd == -1)
    // cust_write("ERROR: Opening file", 2) ;
    cust_write(i_in, 2);
  return i_fd;
}

int cust_close(const int& out)
{
  if (close(out) == -1)
    cust_write("ERROR: Closing file", 2) ;
  return 0;
}

// Enum for file permissions
enum file_perm
  {
    U_R   = S_IRUSR,
    U_RW  = S_IRUSR|S_IWUSR,
    U_RX  = S_IRUSR|S_IXUSR,
    U_RWX = S_IRUSR|S_IWUSR|S_IXUSR,
    G_R   = S_IRGRP,
    G_RW  = S_IRGRP|S_IWGRP,
    G_RX  = S_IRGRP|S_IXGRP,
    G_IWX = S_IXGRP|S_IWGRP|S_IXGRP,
    O_R   = S_IROTH,
    O_RW  = S_IROTH|S_IWOTH,
    O_RX  = S_IROTH|S_IXOTH,
    O_RWX = S_IROTH|S_IWOTH|S_IXOTH
  };

// Writes to file until a # is entered
void console_file_write(const char* file_name)
{
  int in = 0;
  int out = open(file_name, O_WRONLY|O_CREAT, U_RWX);
  if (out == -1)
    {
      cust_write("ERROR: Opening file", 0);
      exit(2);
    }
  char c = 'x';
  while (c != '#')
    {
      if (read(in, &c, 1) == -1)
	cust_write("ERROR: Read error has occurred", 2);
      cust_write(&c, out);
    }
  if (close(out) == -1)
    {
      cust_write("ERROR: Closing file", 2);
      exit(2);
    }
}



// Uses 1MB buffers to reduce system calls
void copy(const char* file_in, const char* file_out)
{
  int in = open(file_in, O_RDONLY);
  int fperm = U_RWX|G_RX|O_RX; // From the enum declared above
  int out = open(file_out, O_CREAT|O_WRONLY, fperm);
  if (in == -1)
    {
      write(2,"ERROR: Opening file: ", 21);
      write(2, file_in, strlen(file_in));
      exit(2);
    }
  if (out == -1)
    {
      write(2,"ERROR: Opening file: ", 21);
      write(2, file_out, strlen(file_out));
      exit(2);
    }
  int read_size = 1;
  // Commenting out the unbuffered solution
  //  while ((read_size = read(in, &c, 1)) > 0)
  //  char c;
    char buffer[LARGE_BUFFERSIZE];
    while ((read_size = read(in, &buffer, LARGE_BUFFERSIZE)) > 0)
      write(out, &buffer, read_size);
  if (close(in) == -1)
    {
      write(2,"ERROR: Closing file: ", 21);
      write(2, file_in, strlen(file_in));
      exit(2);
    }
  if (close(out) == -1)
    {
      write(2,"ERROR: Closing file: ", 21);
      write(2, file_in, strlen(file_in));
      exit(2);
    }
}



