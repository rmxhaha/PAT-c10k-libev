#include <SocketBufferWriteRequest.hpp>


SocketBufferWriteRequest::SocketBufferWriteRequest(Buffer* _buffer) : buffer(_buffer){

}

SocketBufferWriteRequest::~SocketBufferWriteRequest() {
	delete buffer;
}

int SocketBufferWriteRequest::write_to(int sfd){
	if( buffer->nbytes() == 0 ) return 0;

    ssize_t written = write(sfd, buffer->dpos(), buffer->nbytes());
    if (written < 0) {
        perror("read error");
        return -1;
    }

    buffer->pos += written;

    return buffer->nbytes();
}

int SocketBufferWriteRequest::nbytes(){
	return buffer->nbytes();
}

