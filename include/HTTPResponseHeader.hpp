#ifndef HTTP_RESPONSE_HEADER
#define HTTP_RESPONSE_HEADER

#include <string>
#include <map>

class HTTPResponseHeader {
public:
	std::string version;
	std::string status_code;
	std::string status_message;

	std::map<std::string, std::string> headers;

	std::string to_string();
};

#endif