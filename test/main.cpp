#include <iostream>

#include "Sockets/ServerSocket.hpp"
#include "Sockets/ClientSocket.hpp"
#include "Servers/TestServer.hpp"

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"
#define PORT   8888

int main()
{
	try {
		TestServer t;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}