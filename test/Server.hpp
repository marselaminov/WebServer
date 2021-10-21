#ifndef WEBSERV_SERVER_HPP
#define WEBSERV_SERVER_HPP



class Server {
public:

    Server();
    ~Server();

    void start();

private:
    int _server_socket;
};


#endif
