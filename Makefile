#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: dlouise <davidlouiz@gmail.com>             +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2015/09/12 02:05:18 by dlouise           #+#    #+#             *#
#*   Updated: 2015/09/23 21:59:08 by dlouise          ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

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
