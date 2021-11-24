NAME 		=	webserv

SRC			= Server.cpp \
        	HTTP/HttpRequest.cpp \
        	HTTP/HttpResponse.cpp \
        	HTTP/AutoIndex.cpp \
        	WebServer.cpp \
        	Parser.cpp \
        	ChunkedRequest.cpp \
 			CGI.cpp \
 			Client.cpp \
				main.cpp

OBJ			=	$(SRC:.cpp=.o)

CC			=	clang++

FLAGS		=	-g -Wall -Wextra -Werror -std=c++98

RM			=	rm -rf

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(FLAGS) $(SRC) -o $(NAME)
				@make clean

clean:
				$(RM) $(OBJ)

fclean: 		clean
				$(RM) $(NAME)

re:				fclean all
