#include <string>
#include <EchoServer.hpp>
  
//
//   A single instance of a non-blocking Echo handler
//
  
  
  
int main(int argc, char **argv) 
{
        int port = 8192;
  
        if (argc > 1)
                port = atoi(argv[1]);
        
        std::string pathToFile = "html";

        if (argc > 2)
                pathToFile = argv[2];


                  
        ev::default_loop       loop;
        EchoServer                   echo(port);
  
        loop.run(0);
  
        return 0;
}