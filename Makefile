##
## EPITECH PROJECT, 2024
## makefile
## File description:
## compiler
##

CC = gcc
RM ?= rm -f

MAIN =		src/main.c
MAINOBJ =	$(MAIN:.c=.o)

SRC =		./src/entity/entity.c \
			./src/entity/collision.c \
			./src/game/game.c \
			./src/game/event.c \
			./src/utils/dict.c \
			./src/utils/load_map.c \
			./src/utils/pos_converter.c \
			./src/utils/sprite_dup.c \
			./src/utils/vector.c \
			./src/world/world.c \
			./src/world/parsing.c
			./src/fight/fight_events.c
			./src/fight/fight_display.c
			./src/fight/fight_loop.c

SRCOBJ =	$(SRC:.c=.o)

LIBSRC =	lib/freef/arr_flags.c \
			lib/freef/free_flags.c \
			lib/freef/free_real.c \
			lib/BASICS/my_printf.c \
			lib/BASICS/my_printf2.c \
			lib/BASICS/my_atoi.c \
			lib/BASICS/my_itoa.c \
			lib/BASICS/my_put_nbr.c \
			lib/BASICS/my_putstr.c\
			lib/BASICS/my_strcmp.c \
			lib/BASICS/my_strcpy.c \
			lib/BASICS/my_strlen.c \
			lib/BASICS/my_realloc.c \
			lib/BASICS/my_str_to_all_array.c \
			lib/BASICS/free_str_array.c \
			lib/BASICS/concatmem.c \
			lib/BASICS/my_strdup_array.c \
			lib/BASICS/append.c \
			lib/BASICS/my_strchr.c \
			lib/BASICS/cleanstr.c \
			lib/BASICS/isdigit.c \
			lib/BASICS/open_file.c

LIBOBJ =	$(LIBSRC:.c=.o)

SRC_TEST	=	$(addprefix tests/,\
			redirect.c	\
			)

OBJ_TEST	=	$(SRC_TEST:.c=.o)

CFLAGS = -Wall -Wextra
LDLIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lm
CPPFLAGS = -iquote ./include

CRITFLAGS = -lcriterion
GCOVRFLAGS = --coverage

NAME =	myrpg

TEST_NAME	=	unit_tests

all: $(NAME)

$(NAME): $(LIBOBJ) $(MAINOBJ) $(SRCOBJ)
	$(CC) $(LIBOBJ) $(MAINOBJ) $(SRCOBJ) -o $(NAME) \
	$(CFLAGS) $(LDLIBS) $(CPPFLAGS)

clean:
	$(RM) $(MAINOBJ) $(SRCOBJ) $(LIBOBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -ggdb3
debug: re

asan: CC = clang -fsanitize=address
asan: re

$(TEST_NAME):	$(OBJ_TEST)
	$(CC) -o $(TEST_NAME) $(CFLAGS) $(CPPFLAGS)	\
	$(OBJ_TEST) $(SRC) $(LIBSRC) $(LDFLAGS) $(LDLIB)	\
	$(CRITFLAGS) $(GCOVRFLAGS) $(LDLIBS)

tests_run:	$(TEST_NAME)
	./$(TEST_NAME)

tests_clean:
	$(RM) *.gcda
	$(RM) *.gcno
	$(RM) coverage*
	$(RM) unit_tests

coverage:
	gcovr --html-details coverage && firefox coverage

.PHONY: all clean fclean re debug \
	tests_run coverage tests_clean
