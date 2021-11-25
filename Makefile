NAME 		=	webserv

SRC			= 	srcs/Server.cpp \
        		srcs/HttpRequest.cpp \
        		srcs/HttpResponse.cpp \
        		srcs/AutoIndex.cpp \
        		srcs/WebServer.cpp \
        		srcs/Parser.cpp \
        		srcs/ChunkedRequest.cpp \
 				srcs/CGI.cpp \
 				srcs/Client.cpp \
				srcs/main.cpp

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
