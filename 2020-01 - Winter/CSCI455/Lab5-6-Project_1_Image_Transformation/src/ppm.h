/* ppm.h
 * -----
 * Authors: Darwin Jacob Groskleg, Dr Laurence T. Yang
 * Purpose: interface writing and reading Portable Pix Map (ppm) image format
 *          files, the datatypes to hold it in.
 */
#ifndef PPM_H_INCLUDED
#define PPM_H_INCLUDED

#define PPM_MAX_PIXELS (1000*1000)


/* image.h : MPI agnostic */
typedef struct Pixel {
    unsigned char red, green, blue;
} Pixel;

/* Gray Pixel: 0 (black) – 255 (white) */
typedef unsigned char GPixel;

typedef struct Image {
    /* PPM Body */
    Pixel* pixels;
    /* PPM Header */
    int width;
    int height;
    int max_color;
} Image;


/* ppm.h : Single Threaded Only! */
int  read_ppm(const char * fname, int* xpix, int* ypix, int* max, char* data);
int write_ppm(const char * fname, int  xpix, int  ypix,           char* data);
int write_pgm(const char * fname, int  xpix, int  ypix,           char* data);

#endif // PPM_H_INCLUDED
