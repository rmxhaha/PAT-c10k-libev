#include <StaticWebInstance.hpp>
#include <SocketBufferWriteRequest.hpp>
#include <iostream>
#include <fstream>

// Generic callback
void StaticWebInstance::callback(ev::io &watcher, int revents) {
        std::cout << revents << std::endl;
        if (EV_ERROR & revents) {
                perror("got invalid event");
                return;
        }

        if (revents & EV_READ)
                read_cb(watcher);

        if (revents & EV_WRITE)
                write_cb(watcher);

        if (write_queue.empty()) {
                io.set(ev::READ);
        } else {
                io.set(ev::READ|ev::WRITE);
        }
}

// Socket is writable
void StaticWebInstance::write_cb(ev::io &watcher) {
        if (write_queue.empty()) {
                io.set(ev::READ);
                return;
        }

        SocketWriteRequest* write_request = write_queue.front();
        if( write_request->write_to(watcher.fd) == -1 ) return; // error write

        if ( write_request->nbytes() == 0) {
                write_queue.pop_front();
                delete write_request;
        }

        if( write_queue.empty() ){
                // assume all is sent ? 
                io.stop();
                close(sfd);

                // should delete but exception if delete, just let memory leaks loooool
                // delete this;
        }
}

// Receive message from client socket
void StaticWebInstance::read_cb(ev::io &watcher) {
        char       buffer[1025];// suppose to be 1024 but add 1 for null terminate to append to accumulation

        ssize_t   nread = recv(watcher.fd, buffer, sizeof(buffer)-1, 0);

        if (nread < 0) {
                perror("read error");
                return;
        }

        if (nread == 0) {
                io.stop();
                std::cout << "GACK\n"; // exception kalau didelete aaaaa
                // Gack - we're deleting ourself inside of ourself!
                delete this;
        } else {
                // Send message bach to the client
                buffer[nread] = '\0';
                raw_request_header += buffer;

                HTTPRequestHeader request_header( raw_request_header );

                if( request_header.valid ){ 

                        reply_request(request_header);
                }
        }
}

void StaticWebInstance::reply_request(const HTTPRequestHeader& request_header){
        if( request_header.valid ){
                HTTPResponseHeader response_header;
                response_header.version = "HTTP/1.0";
                response_header.status_code = "200";
                response_header.status_message = "OK";
                response_header.headers["Content-Type"] = "text/html";
                response_header.headers["Content-Length"] = "13";
                response_header.headers["Server"] = "potato_server/1.0";

                std::string raw_response_header = response_header.to_string();
                char* str = new char[raw_response_header.length()+1];
                strcpy(str, raw_response_header.c_str());
                Buffer *buffer = new Buffer(str, raw_response_header.length());

                write_queue.push_back( new SocketBufferWriteRequest(buffer) );

                char* str2 = new char[100]; 
                strcpy(str2,"Hello World!\n");

                Buffer* buffer2 = new Buffer(str2, strlen(str2));
                write_queue.push_back( new SocketBufferWriteRequest(buffer2) );
        }
}


// effictivly a close and a destroy
StaticWebInstance::~StaticWebInstance() {
        // Stop and free watcher if client socket is closing
        io.stop();

        close(sfd);

        printf("%d client(s) connected.\n", --total_clients);
}

StaticWebInstance::StaticWebInstance(std::string _root, int s) : sfd(s), root(_root) {
        fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK); 

        printf("Got connection\n");
        total_clients++;

        io.set<StaticWebInstance, &StaticWebInstance::callback>(this);

        io.start(s, ev::READ);
}

int StaticWebInstance::total_clients = 0;

