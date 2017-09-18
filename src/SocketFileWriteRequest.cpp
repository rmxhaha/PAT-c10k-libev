#include <SocketFileWriteRequest.hpp>
#include <sys/sendfile.h>
SocketFileWriteRequest::SocketFileWriteRequest(int _filefd, int _filesize):filefd(_filefd), filesize(_filesize){
	offset = 0; // ?	
}

SocketFileWriteRequest::~SocketFileWriteRequest(){
	
}

int SocketFileWriteRequest::write_to(int s){
	if( nbytes() == 0 ) return 0;
	
	if( sendfile(s, filefd, &offset, filesize) < 0 ){
		perror("write fail");
		return -1;
	}

	if( nbytes() == 0 ){
		close(filefd);
	}

	return nbytes();
}

int SocketFileWriteRequest::nbytes(){
	return (int)filesize - offset;
}

