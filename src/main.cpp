#include <string>
#include <StaticWebServer.hpp>
// #include <HTTPResponseHeader.hpp>
// #include <HTTPRequestHeader.hpp>
//
//   A single instance of a non-blocking Echo handler
//
  
  
  #include <iostream>
int main(int argc, char **argv) 
{
// const std::string test = "\
// GET /test HTTP/1.1\r\n\
// Host: localhost:8192\r\n\
// User-Agent: curl/7.47.0\r\n\
// Accept: */*\r\n\r\n\
// \
// ";
//         HTTPRequestHeader h(test);
//         HTTPResponseHeader h2;
//         h2.version = h.version;
//         h2.statusCode = "200";
//         h2.statusMessage = "OK";
//         h2.headers = h.headers;
//         std::cout << h2.to_string() << std::endl;

//         // std::cout << h.method << std::endl;
//         // std::cout << h.path << std::endl;
//         // std::cout << h.valid << std::endl;
//         // for( auto& it:h.header){
//         //         std::cout << it.first << " : " << it.second << "\n";
//         // }
//         return 0;

        int port = 8192;
  
        if (argc > 1)
                port = atoi(argv[1]);
        
        std::string pathToFile = "html";

        if (argc > 2)
                pathToFile = argv[2];


                  
        ev::default_loop       loop;
        StaticWebServer        echo(port);
  
        loop.run(0);
  
        return 0;
}