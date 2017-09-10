#include <HTTPResponseHeader.hpp>
#include <sstream>

std::string HTTPResponseHeader::to_string(){
	std::stringstream ss;

	ss << version << " " << statusCode << " " << statusMessage << "\r\n";
	for( auto& header:headers){
		ss << header.first << ": " << header.second << "\r\n";
	}
	
	ss << "\r\n";


	return ss.str();
}
