#include "../inc/Response.hpp"
#include "CGIResponse.hpp"
#include <unistd.h>

Response::Response() : _value("") {}
Response::~Response() {}

void	Response::build(const Request &request)
{
	std::string 	path = request.getPath();
	std::string	mimetype = request.getMimeType();

	if (mimetype == "application/python") // CGI Request
	{
		std::string		path;

		path = "/home/yzioual/Desktop/ft_webserv/cgi-bin/form/my_cgi.py";
		CGIResponse cgiResponse(path);
		const std::string 	cgiOut = cgiResponse.execute();
		const std::string 	response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + cgiOut;
		this->_value = response;
		return ;
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
			this->_value = "HTTP/1.1 302 Found\nLocation: /static/index.html\n\n";
			return;
		}
		std::string fileRequested = buffer.str();
		std::ostringstream ss;
		ss 
			<< "HTTP/1.1 200 OK\nContent-Type: " 
			<< request.getMimeType()
			<< "\nContent-Length: " 
			<< fileRequested.size() << "\n\n"
			<< fileRequested;
		this->_value = ss.str();
	}
}

const std::string Response::getResponse() const { return this->_value; }
