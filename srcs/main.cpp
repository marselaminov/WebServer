#include <iostream>

#include "../includes/WebServer.hpp"

int main(int argc, char **argv) {

	if (argv[1]) {
		std::string file = argv[1];
		if (file.find(".conf", 0) != std::string::npos);
		else {
			std::cout << RED"Invalid file extension!" RESET << std::endl;
			return (-1);
		}
	}

	if (argc <= 2) {
		try {
			signal(SIGPIPE, SIG_IGN);
			signal(SIGILL, SIG_IGN);
			WebServer t(argv[1]);
			t.start();
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
			std::cerr << RED"Server crashed!" RESET << std::endl;
			return (-1);
		}
	} else
		std::cout << RED"Invalid arguments!" RESET << std::endl;

	return (0);
}
