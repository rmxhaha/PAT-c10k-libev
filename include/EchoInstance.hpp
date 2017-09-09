#ifndef ECHO_INSTANCE_HPP
#define ECHO_INSTANCE_HPP

#include <Buffer.hpp>
#include <ev++.h>


class EchoInstance {
private:
        ev::io           io;
        static int total_clients;
        int              sfd;
  
        // Buffers that are pending write
        std::list<Buffer*>     write_queue;
  
        // Generic callback
        void callback(ev::io &watcher, int revents);
  
        // Socket is writable
        void write_cb(ev::io &watcher);
  
        // Receive message from client socket
        void read_cb(ev::io &watcher);
  
        // effictivly a close and a destroy
        virtual ~EchoInstance();
  
public:
        EchoInstance(int s);
};

#endif