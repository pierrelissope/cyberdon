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


CFLAGS = -Wall -Wextra
LIBFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system
CPPFLAGS = -iquote ./include

CRITFLAGS = -lcriterion
GCOVRFLAGS = --coverage

NAME =	myrpg

all: $(NAME)

$(NAME): $(LIBOBJ) $(MAINOBJ) $(SRCOBJ)
	$(CC) $(LIBOBJ) $(MAINOBJ) $(SRCOBJ) -o $(NAME) \
	$(CFLAGS) $(LIBFLAGS) $(CPPFLAGS)

clean:
	$(RM) $(MAINOBJ) $(SRCOBJ) $(LIBOBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
