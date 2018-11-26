#include "image_operations.h"

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *)p;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *)p;
  }
  return 0;
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
    case 1:
      *p = pixel;
      break;
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
    case 4:
      *(Uint32 *)p = pixel;
      break;
  }
}

void greyscale(SDL_Surface *image)
{
  for(int y = 0; y < image->h; y++) {
    for(int x = 0; x < image->w; x++) {
      Uint32 pixel = get_pixel(image, x, y);
      Uint8 r = 0, g = 0, b = 0;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      Uint8 sum = r * 0.3 + g * 0.59 + b * 0.11;
      pixel = SDL_MapRGB(image->format, sum, sum, sum);
      put_pixel(image, x, y, pixel);
    }
  }
}

void black_and_white(SDL_Surface *image)
{
  for(int y = 0; y < image->h; y++) {
    for(int x = 0; x < image->w; x++) {
      Uint32 pixel = get_pixel(image, x, y);
      Uint8 r = 0, g = 0, b = 0;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      r = (r >= 127) ? 255 : 0;
      g = (g >= 127) ? 255 : 0;
      b = (b >= 127) ? 255 : 0;
      pixel = SDL_MapRGB(image->format, r, g, b);
      put_pixel(image, x, y, pixel);
    }
  }
}


SDL_Surface* black_and_white2(SDL_Surface* img, int split) {
  if(!split)
    return otzu(img, 0, img->w, 0, img->h);
  int w = img->w, h = img->h, w_sp = 0, h_sp = 0;
  if(w > h) {
    w_sp = 3 * split;
    h_sp = 2 * split;
  }
  else if(w < h) {
    w_sp = 2 * split;
    h_sp = 3 * split;
  }
  else {
    w_sp = 2 * split;
    h_sp = 2 * split;
  }
  int w_r = w/w_sp, h_r = h/h_sp;
  for(int i = 0; i < w_sp; i++)
    for(int j = 0; j < h_sp; j++)
      img = otzu(img, i * w_r, (i+1) * w_r, j * h_r, (j+1) * h_r);
  return img;
}

// Otzu method for Black and White
SDL_Surface* otzu(SDL_Surface* img, int w_min, int w_max, int h_min, int h_max)
{
  Uint32 pixl;
  Uint8 r, g, b;
  int sigsq, max_intensity = 255, histogram[256];
  int N = (h_max - h_min) * (w_max - w_min); // img->h * img->w;
  int threshold=0, var_max=0, sum=0, sumB=0, q1=0, q2=0, m1=0, m2=0;

  for(int i = 0; i <= max_intensity; i++)
    histogram[i] = 0;

  // We build the histogram
  for(int i = w_min; i < w_max; i++) {
    for(int j = h_min; j < h_max; j++) {
      pixl = get_pixel(img, i, j);
      SDL_GetRGB(pixl, img->format, &r, &g, &b);

      histogram[(int)r]++;
    }
  }

  // update qi(t)
  for(int t = 0; t <= max_intensity; t++) {
    sum += t * histogram[t]; // auxiliary value for computing μ2
    q1 += histogram[t];
    q2 = N - q1;
    sumB += t * histogram[t];

    if(q1 != 0)
      m1 = sumB / q1;
    if(q2 != 0)
      m2 = (sum - sumB) / q2;

    sigsq = q1 * q2 * (m1 - m2) * (m1 - m2);

    if(sigsq > var_max) {
      threshold = t;
      var_max = sigsq;
    }
  }

  // We apply the changes
  for(int h = h_min; h < h_max; h++) {
    for(int w = w_min; w < w_max; w++) {
      SDL_GetRGB(get_pixel(img, w, h),img->format, &r, &g, &b);
      if(r <= threshold)
        put_pixel(img, w, h, SDL_MapRGB(img->format, 0, 0, 0));
      else
        put_pixel(img, w, h, SDL_MapRGB(img->format, 255, 255, 255));
    }
  }
  return img;
}
/*
SDL_Surface* resize(SDL_Surface* image)
{
  SDL_Surface* imageIn28x28;
  SDL_Rect rect;

  double width = image->w;
  double height = image->h;
  double aspectRatio = dWidth/dHeight;

  rect.x = 0;
  rect.y = 0;

  if (image->h > 28 && image->w > 28) {
    rect.h = 28;
    rect.w = 28;
    size_t h = image->h;
    size_t w = image->w;

    while (h > 28 || w > 28) {
      h--;
      w--;
    }
  }
  else if (image->h > 28 && image->w < 28) {

  }
  else if (image->h < 28 && image->w > 28) {

  }
  else if (image->h < 28 && image->w < 28) {

  }
  SDL_BlitScaled(image, NULL, imageIn28x28, &rect);

  return imageIn28x28;
}
*/

double get_value_pixel(SDL_Surface* img, size_t x, size_t y)
{
  Uint32 pixel = get_pixel(img, x, y);

  Uint8 r = 0, g = 0, b = 0;
  SDL_GetRGB(pixel, img->format, &r, &g, &b);

  return (double) 1.0 - (r / 255);
}

SDL_Surface* scaleSurface(SDL_Surface* img, int width, int height)
{
  if(!img || !width || !height)
    return 0;

  SDL_Surface* new_img = SDL_CreateRGBSurface(
    0,
    width,
    height,
    img->format->BitsPerPixel,
    img->format->Rmask,
    img->format->Gmask,
    img->format->Bmask,
    img->format->Amask
  );

  //double stretch_factor_x = width / img->w;
  //double stretch_factor_y = height / img->h;

  for(int y = 0; y < height; ++y)
  {
    for(int x = 0; x < width; ++x)
    {
      Uint32 pixel = get_pixel(img, x, y);
      put_pixel(new_img, x, y, pixel);
    }
  }

  return new_img;
}
