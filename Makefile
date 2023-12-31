##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC			=	src/main.cpp \
				src/auto_makefile_declaration.cpp \
				src/check_arg_validity.cpp \
				src/get_file_content.cpp \
				src/get_param.cpp \
				src/parse_makefile_param.cpp \
				src/error_message.cpp \
				src/split_string.cpp \
				src/get_makefile_rule_pos.cpp \
				src/generate_rule_content.cpp \
				src/formate_rule.cpp \
				src/formate_rule_content.cpp \
				src/remove_empty_folder.cpp \
				src/sort_rule_content.cpp \
				src/insert_rule_in_makefile.cpp \
				src/multiple_rule_with_same_name_protection.cpp

CPPFLAGS	=	-std=c++20 -Wall -Wextra -I./include/ -I../include/ -I../../include/

NAME		=	auto_makefile

SRC_TESTS	=

RUN_TEST	=	--coverage

NAME_TESTS	=	unit_tests

OBJ			=	$(SRC:.cpp=.o)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CPPFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)
	rm -f *.gcno
	rm -f *.gcda

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_TESTS)

re: fclean all

unit_tests: SRC := $(patsubst src/main.cpp%,%,$(SRC))
unit_tests: fclean
	g++ -o $(NAME_TESTS) $(SRC_TESTS) $(SRC) $(CPPFLAGS) $(RUN_TEST)

tests_run: unit_tests
	./$(NAME_TESTS)

gcovr:
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

debug: CPPFLAGS += -g3
debug: re
	gdb -ex "run $(arg)" -ex "bt full" -ex "detach" -ex "quit" $(NAME)

.PHONY: all clean fclean re unit_tests tests_run gcovr debug
