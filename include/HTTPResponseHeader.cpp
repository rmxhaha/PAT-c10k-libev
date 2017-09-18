#include <HTTPResponseHeader.hpp>
#include <stringstream>

HTTPResponseHeader::to_string(){
	std::sstream ss;

	ss << version << " " << statusCode << " " << statusMessage << "\r\n";
	for( auto& header:headers){
		ss << header.first << ": " << header.second << "\r\n";
	}
	
	ss << "\r\n";


	return ss.str();
}
