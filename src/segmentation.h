#ifndef SEGMENTION_H
#define SEGMENTATION_H

void parcours_horizontal(SDL_Surface *image);
void parcours_vertical(SDL_Surface *image, int startline, int endline);
void remplissage(SDL_Surface *image, int startline, int endline, int startcolum, int endcolum); 
Uint32 get_pixel(SDL_Surface *surface, int x, int y);
void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif 
