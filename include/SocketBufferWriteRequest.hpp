#ifndef SOCKET_BUFFER_WRITE_REQUEST_HPP
#define SOCKET_BUFFER_WRITE_REQUEST_HPP

#include <SocketWriteRequest.hpp>
#include <Buffer.hpp>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <ev++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <resolv.h>
#include <errno.h>

class SocketBufferWriteRequest : public SocketWriteRequest {
private:
	Buffer* buffer;
public:
	virtual ~SocketBufferWriteRequest();
	SocketBufferWriteRequest(Buffer* buffer);
	int write_to(int s); // socket fd
	int nbytes();
};

#endif