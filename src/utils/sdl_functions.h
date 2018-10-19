#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

#include <err.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/*SDL_Surface *SDL_SetVideoMode(int width, int height, int bpp, Uint32 flags);
void SDL_UpdateRect(SDL_Surface *screen, Sint32 x, Sint32 y, Sint32 w, Sint32 h);*/
void SDL_FreeSurface(SDL_Surface *surface);
void init_sdl(void);
void wait_for_keypressed(void);
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *image);
void greyscale(SDL_Surface* image);
void black_and_white(SDL_Surface* image);
//Uint32 get_pixel(SDL_Surface *surface, int x, int y);
//void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);


#endif
