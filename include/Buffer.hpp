#ifndef BUFFER_HPP
#define BUFFER_HPP

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
//
//   Buffer class - allow for output buffering such that it can be written out 
//                                 into async pieces
//
struct Buffer {
        char       *data;
        ssize_t len;
        ssize_t pos;
  
        Buffer(const char *bytes, ssize_t nbytes);
  
        virtual ~Buffer();
  
        char *dpos();
  
        ssize_t nbytes();
};

#endif