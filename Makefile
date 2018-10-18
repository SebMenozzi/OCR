.PHONY : clean, fclean, re
.SUFFIXES :

CFLAGS = -Wall -Werror -Wextra -std=c99

OS = $(shell uname)
ifeq ($(OS), Darwin) # if os is macos
    LDFLAGS = -framework OpenGL -framework GLUT -F/Library/Frameworks -framework SDL2 -framework SDL2_image
    IFLAGS = -I/Library/Frameworks/SDL2.framework/Headers/ -I/Library/Frameworks/SDL2_image.framework/Headers/
    SDL2FLAGS = ``
else
    LDFLAGS = -lSDL2 -lSDL2_image
    SDL2FLAGS = `sdl2-config --libs --cflags`
endif
NAME = mmgd
SRC =	src/main.c src/xor.c src/ocr.c src/utils/sdl_functions.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(OBJ) $(CFLAGS) $(LDFLAGS) -o $@ $(SDL2FLAGS)

%.o : %.c
	gcc -c $^ $(CFLAGS) $(IFLAGS) -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
