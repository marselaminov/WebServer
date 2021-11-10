#include <iostream>

#include "WebServer.hpp"

int main()
{
	try {
//		signal(SIGPIPE, SIG_IGN);
//		signal(SIGILL, SIG_IGN);
		WebServer t;
		t.start();
//		TestServer t;
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}