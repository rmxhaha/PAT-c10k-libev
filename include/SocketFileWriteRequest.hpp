#ifndef SOCKET_FILE_WRITE_REQUEST
#define SOCKET_FILE_WRITE_REQUEST

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

class SocketFileWriteRequest : public SocketWriteRequest {
private:
	int filefd;
	long int offset;
	int filesize;
public:
	virtual ~SocketFileWriteRequest();
	SocketFileWriteRequest(int filefd, int filesize);
	int write_to(int s); // socket fd
	int nbytes();
};

#endif