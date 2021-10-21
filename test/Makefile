NAME 		=	test

SRC			= Servers/Server.cpp \
			Servers/TestServer.cpp \
       		Sockets/ASocket.cpp \
        	Sockets/ServerSocket.cpp \
        	Sockets/ClientSocket.cpp \
				main.cpp

OBJ			=	$(SRC:.cpp=.o)

CC			=	clang++

FLAGS		=	-Wall -Wextra -Werror -std=c++98

RM			=	rm -rf

all:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
				$(RM) $(OBJ)

fclean: 		clean
				$(RM) $(NAME)

re:				fclean all
