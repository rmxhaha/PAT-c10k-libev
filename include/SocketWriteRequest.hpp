#ifndef WRITE_REQUEST_H
#define WRITE_REQUEST_H

class SocketWriteRequest {
public:
	virtual ~SocketWriteRequest();
	virtual int write_to(int s) = 0;
	virtual int nbytes() = 0;
};

#endif