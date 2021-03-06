.PHONY : clean, fclean, re
.SUFFIXES :

CFLAGS = -Wall -Wextra -std=c99 -g

OS = $(shell uname)
ifeq ($(OS), Darwin) # if os is macos
    LDFLAGS = -framework OpenGL -framework GLUT -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf
    IFLAGS = -I/Library/Frameworks/SDL2.framework/Headers/ -I/Library/Frameworks/SDL2_image.framework/Headers/
    SDL2FLAGS = ``
    GTKFLAGS = ``
    GLADEFLAGS = ``
else
    LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lm
    IFLAGS = ``
    SDL2FLAGS = `sdl2-config --libs --cflags`
    GTKFLAGS = `pkg-config --libs --cflags gtk+-3.0`
    GLADEFLAGS = `pkg-config --libs gmodule-2.0`
endif
NAME = mmgd
SRC =	src/main.c src/ocr.c src/ocr_ui.c src/xor.c src/train_ocr.c src/gtd.c src/gtd_from_seg.c src/gtk.c src/utils/matrix.c src/utils/neural_network.c src/utils/sdl_functions.c src/utils/image_operations.c src/utils/segmentation.c src/utils/tools.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(OBJ) $(CFLAGS) $(LDFLAGS) -o $@ $(SDL2FLAGS) $(GTKFLAGS) $(GLADEFLAGS) 

%.o : %.c
	gcc -c $^ $(CFLAGS) $(IFLAGS) $(SDL2FLAGS) $(GTKFLAGS) $(GLADEFLAGS) -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
