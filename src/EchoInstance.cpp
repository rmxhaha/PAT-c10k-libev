#include <EchoInstance.hpp>

// Generic callback
void EchoInstance::callback(ev::io &watcher, int revents) {
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
void EchoInstance::write_cb(ev::io &watcher) {
        if (write_queue.empty()) {
                io.set(ev::READ);
                return;
        }

        Buffer* buffer = write_queue.front();
                  
        ssize_t written = write(watcher.fd, buffer->dpos(), buffer->nbytes());
        if (written < 0) {
                perror("read error");
                return;
        }

        buffer->pos += written;
        if (buffer->nbytes() == 0) {
                write_queue.pop_front();
                delete buffer;
        }
}

// Receive message from client socket
void EchoInstance::read_cb(ev::io &watcher) {
        char       buffer[1024];

        ssize_t   nread = recv(watcher.fd, buffer, sizeof(buffer), 0);

        if (nread < 0) {
                perror("read error");
                return;
        }

        if (nread == 0) {
                // Gack - we're deleting ourself inside of ourself!
                delete this;
        } else {
                // Send message bach to the client
                write_queue.push_back(new Buffer(buffer, nread));
        }
}

// effictivly a close and a destroy
EchoInstance::~EchoInstance() {
        // Stop and free watcher if client socket is closing
        io.stop();

        close(sfd);

        printf("%d client(s) connected.\n", --total_clients);
}

EchoInstance::EchoInstance(int s) : sfd(s) {
        fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK); 

        printf("Got connection\n");
        total_clients++;

        io.set<EchoInstance, &EchoInstance::callback>(this);

        io.start(s, ev::READ);
}

int EchoInstance::total_clients = 0;

