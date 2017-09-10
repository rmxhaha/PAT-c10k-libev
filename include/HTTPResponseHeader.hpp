#include <string>
#include <map>

class HTTPResponseHeader {
public:
	std::string version;
	std::string statusCode;
	std::string statusMessage;

	std::map<std::string, std::string> headers;

	std::string to_string();
};