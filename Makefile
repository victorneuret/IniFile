NAME	=	ini

SRC	=	src/main.cpp	\
		src/IniParser.cpp	\
		src/IniFile.cpp		\
		src/EscapeChar.cpp

CPPFLAGS	=	-I./include

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra -Werror -std=c++14

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(OBJ) $(CPPFLAGS) $(CXXFLAGS) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
