/* filter_ppm.c
 * ------------
 * Authors: Darwin Jacob Groskleg
 *
 * Purpose: should be agnostic to using MPI.
 */
#include "filter_ppm.h"

#include <assert.h>
#include <stddef.h>


#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
      __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

/* Provide "external definitions" of the helper functions,
 *  required for proper linking when using C99 inline keyword.
 */
extern inline int img_partition_pixels(int pixel_area, int partitions);
extern inline int img_partition_head(int partition_size, int kth_subset);


/* Averaging / Fuzzy Filter
 *
 * Simplest method for parallel:
 * - (broadcast) send all data to all procs
 * - partition the resulting pixel stream by process number
 * - collect / gather by root, which writes to file
 *
 *
 * Implementation Suggestions:
 *
 * The value for a pixel (x; y) in the output image is the sum of all the pixels
 * in a rectangle in the input image centered around (x; y) divided by the
 * number of pixels in the rectangle.
 *
 * In other words, the pixel in the output image is an average of the
 * rectangle-shaped neighborhood of corresponding pixel in the input image.
 *
 * Your implementation should work with different sizes of the rectangle.
 * Therefore, it is recommended that the function implementing this
 * transformation take parameters specifying the x-radius and y-radius of the
 * rectangle (see Figure 1). It is allowed to use integer limits for the
 * rectangle to avoid the problem of interpolation.
 */
void averaging_filter_subset(const Image img, int start_pos, int count,
        int x_radius, int y_radius,
        Pixel* extant_img)
{
    assert(extant_img != 0);    // memory allocated?

    // radius for averaging
    int xr = x_radius;
    int yr = y_radius;
    assert(xr > 0 && yr > 0);

    int sentinel = min(start_pos + count, img.width * img.height);
    // k indexing = k'th element is a_ij
    for (int x,y,k=start_pos; k < sentinel; k++) {
        // row index = i
        y = (int) k / img.width;    // integer division
        // column index = j
        x = k % img.width;

        int r, g, b, n;
        n = 0; r = 0; g = 0; b = 0;
        for (int xas = x - xr; xas < x + xr; xas++) {
            for (int yas = y - yr; yas < y + yr; yas++) {
                Pixel *pix;

                if (   (xas < 0) || (xas >= img.width)
                    || (yas < 0) || (yas >= img.height))
                {
                    pix = NULL;
                } else {
                    pix = img.pixels + yas*img.width + xas;
                }

                if (pix != NULL) {
                    r += pix->red;
                    g += pix->green;
                    b += pix->blue;
                    n++;
                }
            }
        }

        if (n > 0) {
            extant_img[k].red   = r/n;
            extant_img[k].green = g/n;
            extant_img[k].blue  = b/n;
        }
    }
}

/* Averaging Filter
 *
 * Purpose: makes the image "fuzzy".
 */
void averaging_filter(const Image img, int x_radius, int y_radius,
                      Pixel* extant_img)
{
    assert(extant_img != 0);

    // radius for averaging
    int xr = x_radius;
    int yr = y_radius;
    assert(xr > 0 && yr > 0);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int r, g, b, n;
            n = 0; r = 0; g = 0; b = 0;
            for (int xas = x - xr; xas < x + xr; xas++) {
                for (int yas = y - yr; yas < y + yr; yas++) {
                    Pixel * pix;
                    if (   (xas < 0) || (xas >= img.width)
                        || (yas < 0) || (yas >= img.height))
                    {
                        pix = NULL;
                    } else {
                        pix = img.pixels + yas*img.width + xas;
                    }

                    if (pix != NULL) {
                        r += pix->red;
                        g += pix->green;
                        b += pix->blue;
                        n++;
                    }
                }
            }

            if (n > 0) {
                extant_img->red = r/n;
                extant_img->green = g/n;
                extant_img->blue = b/n;
            }
            extant_img++;
        }
    }
}

double average_intensity(const Image img) {
    Pixel* pix;
    double intensity = 0;
    for (int y=0; y<img.height; y++) {
        for (int x=0; x<img.width; x++) {
            pix = img.pixels + y*img.width + x;
            intensity += ( (1.0 * (double) pix->red
                          + 1.0 * (double) pix->green
                          + 1.0 * (double) pix->blue
                         )/ 3.0);
        }
    }

    intensity /= img.width * img.height;
    return intensity;
}

/* Threshold Filter
 *
 * Purpose: creates a binary-pixel image.
 *
 * The filter computes the average intensity of the whole input image and use
 * this value to threshold the image. The result is an image containing only
 * black and white pixels. The white for those pixels in the input image that
 * are lighter than the threshold and the black for those pixels in the input
 * image that are darker than the threshold.
 */
double threshold_filter(const Image img, GPixel* extant_img) {
    assert(extant_img != 0);

    double intensity = average_intensity(img);

    Pixel* pix;
    for (int y=0; y<img.height; y++) {
        for (int x=0; x<img.width; x++) {
            pix = img.pixels + y*img.width + x;
            double pix_intensity = 0;
            pix_intensity = ( 1.0 * (double) pix->red
                            + 1.0 * (double) pix->green
                            + 1.0 * (double) pix->blue
                            ) / 3;
            if ( pix_intensity > intensity) {
                extant_img[y*img.width + x] = 255;
            } else {
                extant_img[y*img.width + x] = 0;
            }
        }
    }
    return intensity;
}

/* for use in a threshold filter
 */
double sum_subset_intensity(const Image img, int start_pos, int count) {
    Pixel* pix;
    double intensity = 0;
    int sentinel = min(start_pos + count, img.width * img.height);
    // k indexing = k'th element is a_ij
    for (int x,y,k=start_pos; k < sentinel; k++) {
        // row index = i
        y = (int) k / img.width;    // integer division
        // column index = j
        x = k % img.width;
        pix = img.pixels + y*img.width + x;
        intensity +=  ((1.0 * (double) pix->red
                      + 1.0 * (double) pix->green
                      + 1.0 * (double) pix->blue
                      )/ 3.0);
    }

    return intensity;
}

/* Threshold Filter
 *
 * Simplest method:
 * - scatter initial pixel stream, partitioned, to procs
 * - calculate avg in each
 * - Reduce and scatter the result, the average intensity
 * - each proc applies threshold to values
 * - collect / gather by root, which writes to file
 */
void threshold_filter_subset(const Image img, int start_pos, int count,
        double threshold,
        GPixel* extant_img)
{
    assert(extant_img != 0);
    assert(threshold >= 0 && threshold <= 255);

    int sentinel = min(start_pos + count, img.width * img.height);
    // k indexing = k'th element is a_ij
    for (int x,y,k=start_pos; k < sentinel; k++) {
        // row index = i
        y = (int) k / img.width;    // integer division
        // column index = j
        x = k % img.width;

        Pixel *pix = img.pixels + y*img.width + x;
        double pix_intensity = 0;
        pix_intensity = ( 1.0 * (double) pix->red
                        + 1.0 * (double) pix->green
                        + 1.0 * (double) pix->blue
                        ) / 3;
        if ( pix_intensity > threshold) {
            extant_img[y*img.width + x] = 255;
        } else {
            extant_img[y*img.width + x] = 0;
        }
    }
}
