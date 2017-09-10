
#include <HTTPRequestHeader.hpp>
#include <HTTPRequestHeader.hpp>
#include <sstream>
#include <iostream>

HTTPRequestHeader::HTTPRequestHeader(const std::string& rawRequest){
	std::stringstream ss;
	ss << rawRequest;
	ss >> method >> path >> version;
	std::cout << rawRequest << std::endl;

	std::string key, value;
	while(ss >> key >> value){
		// remove `:` at the end of key
		key.resize(key.size()-1);
		headers[key] = value;
	}

	valid = !ss.fail();
}

HTTPRequestHeader::HTTPRequestHeader() : valid(false){
}
