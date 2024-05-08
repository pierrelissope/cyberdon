##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## nothing to see here just a makefile
##

SRC	 =	free_flags.c	\
		free_real.c	\
		arr_flags.c	\

INCLUDES	=	-iquote../../include

CPPFLAGS	=	$(INCLUDES)

CFLAGS	=	-Wall -Wextra

OBJ =	$(SRC:.c=.o)

NAME	=	libfree.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) ../$(NAME)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
