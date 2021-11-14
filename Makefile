NAME 		=	test

SRC			= Server.cpp \
        	HTTP/HttpRequest.cpp \
        	HTTP/HttpResponse.cpp \
        	HTTP/AutoIndex.cpp \
        	Server.cpp \
        	WebServer.cpp \
        	Parser.cpp \
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
