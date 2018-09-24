NAME	=	ini

SRC	=	src/IniParser.cpp	\
		src/IniFile.cpp		\
		src/EscapeChar.cpp

SRC_UNIT=	$(filter-out src/main.cpp, $(SRC))	\
		tests/test_key_file.cpp	\
		tests/test_get_map.cpp

SRC	+=	src/main.cpp

CPPFLAGS=	-I./include

CPPFLAGS_UNIT	=	-I./tests/include

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS=	-W -Wall -Wextra -Werror -std=c++14

TESTS_FLAGS	=	-lcriterion --coverage

all:	$(NAME)

$(NAME):	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

tests_run:
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(CPPFLAGS_UNIT) $(SRC_UNIT) $(TESTS_FLAGS) -o tests_run
	./tests_run

clean_coverage:
		find . \( -name '*.gcda' -o -name '*.gcno' -o -name '*.gcov' -o -name 'tests_run' \) -delete

.PHONY: all clean fclean re tests_run clean_coverage
