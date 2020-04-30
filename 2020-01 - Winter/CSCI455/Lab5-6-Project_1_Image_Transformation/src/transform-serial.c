/* transform-serial.c
 * ------------------
 * Derived from: serial.c (L.T. Yang)
 * Authors: Darwin Jacob Groskleg, Dr Laurence T. Yang
 *
 * Usage:
 *      transform-serial [input.ppm]
 * Output:
 *  - file:     input-fuzzy.ppm
 *  - file:     input-threshold.pgm
 *  - stdout:   average intensity calculated for the fuzzy filter.
 */
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "ppm.h"
#include "filter_ppm.h"

char* append_to_basename(const char* filename, const char* appendix);

int main(int argc, char *argv[]) {
    const char* default_image_filename = "./im1.ppm";
    char* image_filename;
    if (argc > 1) {
        image_filename = (char *) malloc( sizeof (char) * strlen(argv[1]));
        strcpy(image_filename, argv[1]);
    } else {
        size_t default_len = strlen(default_image_filename);
        image_filename = (char *) malloc( sizeof (char) * default_len);
        strcpy(image_filename, default_image_filename);
    }
    printf("infile name: %s\n", image_filename);


    Pixel* in_image = (Pixel *) malloc(PPM_MAX_PIXELS * sizeof (Pixel));
    assert(in_image != 0);

    int err = 0;

    int width, height, max;
    err = read_ppm(image_filename, &width, &height, &max, (char *) in_image);
    if (err != 0) exit(err);
    const Image img = { .pixels=in_image, width, height, max };

/*
 * The "fuzzy" transformation
 *
 */
    Pixel* out_image_fuzzy = (Pixel *) malloc(PPM_MAX_PIXELS * sizeof (Pixel));
    assert(out_image_fuzzy  != 0);

    int xradius = 5, yradius = 5;
    printf("Neighborhood pixel radius |x y|: %d %d\n", xradius, yradius);
    averaging_filter(img, xradius, yradius, out_image_fuzzy);

    char* fuzzy_fname = append_to_basename(image_filename, "-serial-fuzzy.ppm");
    err = write_ppm(fuzzy_fname, width, height, (char *) out_image_fuzzy);
    if (err != 0) exit(err);


/*
 * The thresholding
 *
 */
    GPixel* out_image_thresh = (GPixel *) malloc(PPM_MAX_PIXELS * sizeof (GPixel));
    assert(out_image_thresh != 0);

    double intensity = threshold_filter(img, out_image_thresh);
    printf("Average intensity is: %f\n", intensity);
    fflush(stdout);

    char* threshold_fname = append_to_basename(image_filename,
            "-serial-threshold.pgm");
    err = write_pgm(threshold_fname, width, height, (char *) out_image_thresh);
    if (err != 0) exit(err);


    return 0;
}

/* example:
 *
 *  append_to_basename("img.ppm", "-fuzzy.pgm")
 *      ->"img-fuzzy.pgm"
 */
char* append_to_basename(const char* filename, const char* appendix) {
    size_t newlen = strlen(filename) + strlen(appendix);
    char* newfile = (char *) malloc(sizeof (char) * newlen);
    char* ft_extension = strrchr(filename, '.');
    size_t basename_len = strlen(filename) - strlen(ft_extension);
    strncpy(newfile, filename, basename_len); // without the file extension
    strcat(newfile, appendix);
    //strcat(newfile, ft_extension);
    //printf("outfile name: %s\n", newfile);

    return newfile;
}
