/* ppm.c
 * -----
 * Authors: Darwin Jacob Groskleg, Dr Laurence T. Yang
 *
 * Purpose: implementation for writing and reading Portable Pix Map (ppm)
 *          image format files.
 */
#include "ppm.h"

#include <errno.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

/*
 * Input arguments:
 *      *fname : filename to open
 *
 * Output arguments:
 *      *xpix : 
 *      *ypix : 
 *      *max  : 
 *      data[] : 
 */
int read_ppm(const char* fname, int* xpix, int* ypix, int* max, char* data) {
    char ftype[40];
    char ctype[40] = "P6";  // binary data, more efficient than P3
    char line[80];

    FILE * fp;
    errno = 0;

    if (fname == NULL) fname = "\0";
    fp = fopen(fname, "r");
    if (fp == NULL) {
        fprintf(stderr,
                "read_ppm failed to open %s: %s\n", fname, strerror(errno));
        return 1;
    }

    fgets(line, 80, fp);        // first 80 char or until newline
    sscanf(line, "%s", ftype);  // assign string from `line` to ftype[]

    while ( fgets(line, 80, fp) && (line[0] == '#') );  // skip comments

    // grab the pixel width/height numbers from `line`
    sscanf(line, "%d%d", xpix, ypix);

    // grab the next number from the stream,
    // the maximum value on the colour range
    fscanf(fp, "%d\n", max);

/*
    fprintf(stderr, "typ= %s xmax= %d  ymax= %d intensity max= %d\n",
         ftype, *xpix, *ypix, *max);
    fflush(stderr);
*/

    assert(*xpix * *ypix <= PPM_MAX_PIXELS);

    if (strncmp(ftype, ctype, 2) == 0) {
        size_t pixel_channels = *xpix * *ypix * 3;  // pixels x 3
        size_t position = fread(data, sizeof (char), pixel_channels, fp);
        if (position != pixel_channels) {
            perror("Read failed");
            fclose(fp);
            return 2;
        }
    } else {
        fprintf(stderr, "Wrong file format: %s\n", ftype);
    }

    if (fclose(fp) == EOF) {
        perror("Close failed");
        return 3;
    }

    return 0;
}


int write_ppm(const char * fname, int xpix, int ypix, char * data) {
    FILE * fp;
    errno = 0;

    if (fname == NULL) fname = "\0";
    fp = fopen(fname, "w");
    if (fp == NULL) {
        fprintf(stderr,
                "write_ppm failed to open %s: %s\n", fname, strerror(errno));
        return 1;
    }

    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d 255\n", xpix, ypix);
    size_t pixel_channels = xpix * ypix * 3;  // pixels x 3
    if (fwrite(data, sizeof (char), pixel_channels, fp) != pixel_channels) {
        perror("Write failed");
        fclose(fp);
        return 2;
    }
    if (fclose(fp) == EOF) {
        perror("Close failed");
        return 3;
    }
    return 0;
}

int fib(int n) {
    for (int i=0; i<n; i++)=
}

int write_pgm(const char * fname, int xpix, int ypix, char * data) {
    FILE * fp;
    errno = 0;

    if (fname == NULL) fname = "\0";
    fp = fopen(fname, "w");
    if (fp == NULL) {
        fprintf(stderr, "write_ppm failed to open %s: %s\n", fname,
             strerror(errno));
      return 1;
    }

    fprintf(fp, "P5\n");
    fprintf(fp, "%d %d 255\n", xpix, ypix);
    size_t pixels = xpix * ypix;
    if (fwrite(data, sizeof (char), pixels, fp) != pixels) {
        perror("Write failed");
        fclose(fp);
        return 2;
    }
    if (fclose(fp) == EOF) {
        perror("Close failed");
        return 3;
    }
    return 0;
}
