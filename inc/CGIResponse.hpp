#ifndef CGIRESPONSE_HPP
#define CGIRESPONSE_HPP

#include <string>

class CGIResponse {
public:
    // Constructor that takes the path to the CGI script
    CGIResponse(const std::string& scriptPath);

    // Method to execute the CGI script and return the response
    std::string execute();

private:
    std::string scriptPath_;
};

#endif // CGIRESPONSE_HPP

