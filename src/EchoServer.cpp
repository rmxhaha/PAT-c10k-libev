#include <EchoServer.hpp>

void EchoServer::io_accept(ev::io &watcher, int revents) {
        if (EV_ERROR & revents) {
                perror("got invalid event");
                return;
        }

        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_sd = accept(watcher.fd, (struct sockaddr *)&client_addr, &client_len);

        if (client_sd < 0) {
                perror("accept error");
                return;
        }

        EchoInstance *client = new EchoInstance(client_sd);
}

void EchoServer::signal_cb(ev::sig &signal, int revents) {
        signal.loop.break_loop(); // buat ctrl+c exit program 
}

EchoServer::EchoServer(int port) {
        printf("Listening on port %d\n", port);

        struct sockaddr_in addr;

        s = socket(PF_INET, SOCK_STREAM, 0);

        addr.sin_family = AF_INET;
        addr.sin_port     = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
                perror("bind");
        }

        fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK); 

        listen(s, 5); // 5 is max queue connection

        io.set<EchoServer, &EchoServer::io_accept>(this);
        io.start(s, ev::READ);

        sio.set<&EchoServer::signal_cb>();
        sio.start(SIGINT);
}
  
EchoServer::~EchoServer() {
        shutdown(s, SHUT_RDWR);
        close(s);
}
