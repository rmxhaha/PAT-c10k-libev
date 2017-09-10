#ifndef HTTP_REQUEST_HEADER_HPP
#define HTTP_REQUEST_HEADER_HPP
#include <string>
#include <map>

// read only class
class HTTPRequestHeader {
public:
	HTTPRequestHeader(const std::string&);
	HTTPRequestHeader();

	bool valid;	
	std::string method; //GET
	std::string path; // /path/to/f.html
	std::string version; // HTTP/1.1

	std::map<std::string, std::string> headers;
	// Host: google.com
};
#endif