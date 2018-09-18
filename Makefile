.PHONY : clean, fclean, re
.SUFFIXES :

NAME = main

SRC =	main.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(OBJ) -Wall -Werror -Wextra -std=c99 -o $@

%.o : %.c
	gcc -c $^ -Wall -Werror -Wextra -std=c99 -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
