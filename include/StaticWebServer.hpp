#ifndef ECHO_SERVER
#define ECHO_SERVER

#include <StaticWebInstance.hpp>
#include <ev++.h>
#include <string>

class StaticWebServer {
private:
        ev::io           io;
        ev::sig         sio;
        int                 s;
  		std::string 		root;
public:
  
        void io_accept(ev::io &watcher, int revents);
  
        static void signal_cb(ev::sig &signal, int revents);
  
        StaticWebServer(std::string rootpath, int port);
          
        virtual ~StaticWebServer();
};

#endif