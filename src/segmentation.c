#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "segmentation.h"

Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[ (y * surface->w ) + x];
}

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    pixels[( y * surface->w ) + x] = pixel;
}


void parcours_vertical(SDL_Surface *image, int startline, int endline);

void remplissage(SDL_Surface *image, int startline, int endline, int startcolum, int endcolum);

void  parcours_horzontal(SDL_Surface *image) 
{
	int oneblack = 0 ; // bool to know if one star char
	int startline = 0; 
	int endline; 
	for(int y=0; y < image->h; y++)
	{
		int oneblank = 1; 
		for(int x=0; x < image->w; x++)
		{
			Uint32 pixel = get_pixel(image, x, y);
	        	Uint8 r = 0, g = 0, b = 0;
                	SDL_GetRGB(pixel, image->format, &r, &g, &b);
			if (r == 0)
			{ 
				oneblank = 0; 
				if (oneblack == 0)
				{
					oneblack = 1;
					startline = y;
					x = image->w; 
				}
				else
				{
					x = image->w; 
				}
			}
		}
		if (oneblack == 1 && oneblank == 1) 
		{
			endline = y - 1; 
			parcours_vertical(image, startline, endline);
			oneblack = 0; 		
		}
		
	}
}

void parcours_vertical(SDL_Surface *image, int startline, int endline)
{
	int oneblack = 0;
	int startcolum = 0;
	int endcolum;  
	for(int x = 0; x < image->w; x++)
	{
		int oneblank = 1;
		for( int y= startline; y<= endline; y++)
		{
			Uint32 pixel = get_pixel(image, x, y);
                        Uint8 r = 0, g = 0, b = 0;
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
                        if (r == 0)
                        {
                                oneblank = 0;
                                if (oneblack == 0)
                                {
                                        oneblack = 1;
                                        startcolum = x;
                                        y = endline+1;
                                }
                                else
                                {
                                        y= endline+1;
                                }
			}
		}
		if (oneblack == 1 && oneblank == 1)
         	{
                        endcolum = x - 1;
                        remplissage(image, startline, endline, startcolum, endcolum);
			oneblack = 0;
        	}
	}
} 

void remplissage(SDL_Surface *image, int startline, int endline, int startcolum, int endcolum)
{
	for (int y = startline; y < endline; y++)
	{	
		for (int x = startcolum; x < endcolum; x++)
		{
			Uint32 pixel = get_pixel(image, x, y);
                        Uint8 r = 0, g = 0, b = 0;
                        SDL_GetRGB(pixel, image->format, &r, &g, &b);
			r = 0;
			g = 0;
			b = 0;
			pixel = SDL_MapRGB(image->format, r, g, b); 
			put_pixel(image, x, y, pixel); 
		}
	}
}


