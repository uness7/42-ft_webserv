#pragma once

#include "Request.hpp"
#include <iostream>
#include <map>

class Response {
	private:
		std::string _value;
		std::map<std::string, std::string> envMap;


	public:
		Response();
		~Response();

		void build(const Request &);

		const std::string getResponse() const;
};
