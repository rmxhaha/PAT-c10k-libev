
//
//   Buffer class - allow for output buffering such that it can be written out 
//                                 into async pieces
//
#include <Buffer.hpp>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ev++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <resolv.h>
#include <errno.h>
#include <list>

Buffer::Buffer(const char *bytes, ssize_t nbytes) {
        pos = 0;
        len = nbytes;
        data = new char[nbytes];
        memcpy(data, bytes, nbytes);
}
  
Buffer::~Buffer() {
        delete [] data;
}
  
char* Buffer::dpos() {
        return data + pos;
}
  
ssize_t Buffer::nbytes() {
        return len - pos;
}