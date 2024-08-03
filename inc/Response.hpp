#pragma once

#include "Request.hpp"
#include "Client.hpp"
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>


struct STATUS_CODE {
  unsigned short code;
  std::string status;
};

class Client;

class Response {
private:
  std::string _value;
  STATUS_CODE _statusCode;
  std::string _contentType;
  std::string _buffer;
  Client *_client;


  void build();
  void buildError();

public:
  Response();
  Response(Client *);
  Response(const Response &);
  Response &operator=(const Response &);
  ~Response();



  const std::string getResponse() const;

  void setStatusCode(STATUS_CODE);
  void setStatusCode(unsigned short code);
  STATUS_CODE getStatusCode() const;
  std::string getStatusToString() const;
};
