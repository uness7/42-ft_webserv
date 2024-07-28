#include "../inc/Response.hpp"
#include "CGIResponse.hpp"
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <iostream>

Response::Response() : _value("") {}
Response::~Response() {}

void Response::build(const Request &request)
{
	std::string path = request.getPath();
	std::string mimetype = request.getMimeType();

	if (mimetype == "application/python")
	{
		std::string 	scriptPath = "/home/yzioual/Desktop/ft_webserv/cgi-bin/file_upload/upload.py";
		CGIResponse 	cgiResponse(scriptPath);
		std::string 	postData = request.getPostData(); 

		cgiResponse.setCgiEnv(envMap);
		const std::string 	response = cgiResponse.execute(this->envMap, "/usr/bin/python3", scriptPath, "POST", postData);

		std::ostringstream httpResponse;
		httpResponse << "HTTP/1.1 200 OK\r\n";
		httpResponse << "Content-Type: text/html\r\n";
		httpResponse << "Content-Length: " << response.size() << "\r\n";
		httpResponse << "\r\n"; 
		httpResponse << response;
		this->_value = httpResponse.str();
		return;
	}
	else
	{
		std::ifstream inFile(std::string("." + path).c_str());
		// Problem when path is a directory ("/" | "/static")
		std::stringstream buffer;
		if (inFile.is_open()) {
			buffer << inFile.rdbuf();
			inFile.close();
		} 
		else 
		{
			std::cerr << "Unable to open file " << path << std::endl;
			this->_value = "HTTP/1.1 302 Found\r\nLocation: /static/index.html\r\n\r\n";
			return;
		}
		std::string fileRequested = buffer.str();
		std::ostringstream ss;
		ss 
			<< "HTTP/1.1 200 OK\r\nContent-Type: " 
			<< request.getMimeType()
			<< "\r\nContent-Length: " 
			<< fileRequested.size() << "\r\n\r\n"
			<< fileRequested;
		this->_value = ss.str();
	}
}

const std::string Response::getResponse() const
{
	return this->_value;
}
