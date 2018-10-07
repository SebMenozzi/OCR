.PHONY : clean, fclean, re
.SUFFIXES :

CFLAGS = -Wall -Werror -Wextra -std=c99

OS = $(shell uname)
ifeq ($(OS), Darwin)
    LDFLAGS = -framework OpenGL -framework GLUT -F/Library/Frameworks -framework SDL2
    IFLAGS = -I/Library/Frameworks/SDL2.framework/Headers/
else
    LDFLAGS = -lglut -lGLU -lGL -lm -lSDL2
endif
NAME = mmgd
SRC =	src/main.c src/xor.c src/ocr.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(OBJ) $(CFLAGS) $(LDFLAGS) -o $@

%.o : %.c
	gcc -c $^ $(CFLAGS) $(IFLAGS) -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
