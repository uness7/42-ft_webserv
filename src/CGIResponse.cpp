#include "CGIResponse.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

CGIResponse::CGIResponse(const std::string& scriptPath): scriptPath_(scriptPath)
{
	// Constructor
}

std::string	CGIResponse::execute()
{
	int 	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		std::perror("pipe");
		return "Internal Server Error";
	}
	pid_t pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO); 
		execlp(scriptPath_.c_str(), scriptPath_.c_str(), NULL);
		std::perror("execlp");
		exit(1);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		char 	buffer[1024];
		ssize_t	bytesRead;
		std::ostringstream response;
		while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytesRead] = '\0';
			response << buffer;
		}
		close(pipefd[0]);
		int	status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return response.str();
		else 
			return "Internal Server Error";
	}
	else 
	{
		std::perror("fork");
		return "Internal Server Error";
	}
}

