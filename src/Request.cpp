#include "../inc/Request.hpp"
#include <iterator>
#include <sstream>

Request::Request(std::string entireRequest)
    : _data(entireRequest), _method(""), _path(""), _mimetype(""), _version(""),
      _host(""), _userAgent("") {
  this->parseData();
  std::cout << entireRequest << std::endl;
}

Request::~Request() {}

void Request::parseData() {
  std::stringstream request(_data);
  std::string method;
  std::string path;
  std::string version;
  std::string line;

  request >> method;
  request >> path;
  request >> version;
  setPath(path);
  setMethod(method);
  _version = version;
  while (std::getline(request, line)) {
    if (!_host.size() && line.compare(0, 6, "Host: ") == 0)
      setHost(line.substr(6));
    else if (!_userAgent.size() && line.compare(0, 12, "User-Agent: ") == 0)
      setUserAgent(line.substr(12));
    else if (!_connection.size() && line.compare(0, 12, "Connection: ") == 0)
      setConnection(line.substr(12));
  }
}

void Request::setMethod(std::string s) { this->_method = s; }
void Request::setPath(std::string s) {
  std::size_t found = s.find("?");
  if (found != std::string::npos)
    this->_path = s.substr(0, found);
  else
    this->_path = s;
  setMimeType();
}
void Request::setMimeType() {
  if (_path.length() >= 5 && _path.substr(_path.length() - 5) == ".html") {
    _mimetype = "text/html";
  } else if (_path.length() >= 4 &&
             _path.substr(_path.length() - 4) == ".css") {
    _mimetype = "text/css";
  } else if (_path.length() >= 4 &&
             _path.substr(_path.length() - 4) == ".jpg") {
    _mimetype = "image/jpg";
  } else if (_path.length() >= 3 && _path.substr(_path.length() - 3) == ".js") {
    _mimetype = "application/javascript";
  } else if (_path.length() >= 4 &&
             _path.substr(_path.length() - 4) == ".mp4") {
    _mimetype = "video/mp4";
  } else {
    _mimetype = "text/plain";
  }
}
void Request::setHost(std::string s) { this->_host = s; }
void Request::setVersion(std::string s) { this->_version = s; }
void Request::setUserAgent(std::string s) { this->_userAgent = s; }
void Request::setConnection(std::string s) { this->_connection = s; }

std::string Request::getMethod() const { return this->_method; }
std::string Request::getPath() const { return this->_path; }
std::string Request::getMimeType() const { return this->_mimetype; }
std::string Request::getConnection() const { return this->_connection; }

std::ostream &operator<<(std::ostream &out, const Request &req) {
  out << "Request: " << std::endl;
  out << " -> Method: " << req.getMethod() << std::endl;
  out << " -> Path: " << req.getPath() << std::endl;
  out << " -> Mimetype: " << req.getMimeType() << std::endl;
  out << " -> Connection: " << req.getConnection() << std::endl;
  return out;
}
