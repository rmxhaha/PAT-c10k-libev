#ifndef ECHO_SERVER
#define ECHO_SERVER

#include <EchoInstance.hpp>
#include <ev++.h>

class EchoServer {
private:
        ev::io           io;
        ev::sig         sio;
        int                 s;
  
public:
  
        void io_accept(ev::io &watcher, int revents);
  
        static void signal_cb(ev::sig &signal, int revents);
  
        EchoServer(int port);
          
        virtual ~EchoServer();
};

#endif