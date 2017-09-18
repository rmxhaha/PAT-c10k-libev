
#include <HTTPRequestHeader.hpp>
#include <HTTPRequestHeader.hpp>
#include <sstream>
#include <iostream>

HTTPRequestHeader::HTTPRequestHeader(const std::string& rawRequest){
	std::stringstream ss;
	ss << rawRequest;
	ss >> method >> path >> version;
	//std::cout << rawRequest << std::endl;

	/*
	std::string key, value;
	while(!ss.eof()){
		if(ss >> key >> value){
			// remove `:` at the end of key
			key.resize(key.size()-1);
			headers[key] = value;
			std::cout << key << " " << value << std::endl; 
		}
        else if (!ss.eof())
        {
            ss.clear();
            ss.ignore(1);
        }
	}

	ss.clear();
	*/

	valid = rawRequest.rfind("\r\n\r\n") != std::string::npos;
}

HTTPRequestHeader::HTTPRequestHeader() : valid(false){
}
