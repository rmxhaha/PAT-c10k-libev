#ifndef ECHO_INSTANCE_HPP
#define ECHO_INSTANCE_HPP

#include <Buffer.hpp>
#include <ev++.h>
#include <string>
#include <HTTPRequestHeader.hpp>
#include <HTTPResponseHeader.hpp>
#include <memory>

class EchoInstance {
private:
        static int total_clients;

        ev::io           io; // io libev
        int              sfd; // socket
  
        // Buffers that are pending write
        std::string                 raw_request_header;
        std::list<Buffer*>          write_queue;
  
        // Generic callback
        void callback(ev::io &watcher, int revents);
  
        // Socket is writable
        void write_cb(ev::io &watcher);
  
        // Receive message from client socket
        void read_cb(ev::io &watcher);
  
        // effictivly a close and a destroy
        virtual ~EchoInstance();

        void reply_request(const HTTPRequestHeader& request_header);

public:
        EchoInstance(int s);
};

#endif