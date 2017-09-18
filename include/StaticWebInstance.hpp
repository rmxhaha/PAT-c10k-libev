#ifndef ECHO_INSTANCE_HPP
#define ECHO_INSTANCE_HPP

#include <Buffer.hpp>
#include <ev++.h>
#include <string>
#include <HTTPRequestHeader.hpp>
#include <HTTPResponseHeader.hpp>
#include <SocketWriteRequest.hpp>
#include <memory>

class StaticWebInstance {
private:
        static int total_clients;

        ev::io           io; // io libev
        int              sfd; // socket
  
        std::string                 root;
        std::string                 raw_request_header;

        // Buffers that are pending write
        std::list<SocketWriteRequest*>          write_queue;
  
        // Generic callback
        void callback(ev::io &watcher, int revents);
  
        // Socket is writable
        void write_cb(ev::io &watcher);
  
        // Receive message from client socket
        void read_cb(ev::io &watcher);
  
        // effictivly a close and a destroy
        virtual ~StaticWebInstance();

        void reply_request(const HTTPRequestHeader& request_header);

public:
        StaticWebInstance(std::string root, int s);
};

#endif