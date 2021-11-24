#include <iostream>

#include "WebServer.hpp"

int main(int argc, char **argv)
{
	if (argc <= 2){
		try {
//			signal(SIGPIPE, SIG_IGN);
//			signal(SIGILL, SIG_IGN);
			WebServer t(argv[1]);
			t.start();
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
			std::cerr << "Server dont started!" << std::endl;
			return -1;
		}
	}
	return 0;
}
