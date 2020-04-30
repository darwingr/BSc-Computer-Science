/* test_filter.c
 * -------------
 * Authors: Darwin Jacob Groskleg
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>   // ceil & fmin
#include <stdio.h>

#include "ppm.h"
#include "filter_ppm.h"

int main() {
/*
 * Read and Share Initial PPM Image Data
 *
 */
    Pixel* in_image = (Pixel *) malloc(PPM_MAX_PIXELS * sizeof (Pixel));
    assert(in_image != 0);

    int width, height, max;
    int err = 0;

    err = read_ppm("./im1.ppm", &width, &height, &max, (char *)in_image);
    if (err != 0) exit(err);
    printf("INFO: file read, %d pixels, %dpx wide, %dpx in height\n",
            width*height, width, height);

    const Image img = { .pixels=in_image, width, height, max };

/*
 * The "fuzzy" transformation
 *
 */
    int radius = 5;

    Pixel* out_image_fuzzy = (Pixel *) malloc(PPM_MAX_PIXELS * sizeof (Pixel));
    assert(out_image_fuzzy != 0);

    averaging_filter(img, radius, radius, out_image_fuzzy);
    err = write_ppm("./im1-test-fuzzy.ppm", width, height,
                    (char *) out_image_fuzzy);
    if (err != 0) exit(err);



    Pixel* out_image_subset = (Pixel *) malloc(PPM_MAX_PIXELS * sizeof (Pixel));
    assert(out_image_subset  != 0);
    memcpy(out_image_subset, in_image, width*height * sizeof(Pixel));

    int subset_size = img_partition_pixels(img.width*img.height, 3);
    // only apply filter to 2nd horizontal strip (center) of the image
    int subset_start = img_partition_head(subset_size, 1);
    averaging_filter_subset(img, subset_start, subset_size, radius, radius,
            out_image_subset);
    err = write_ppm("./im1-test-fuzzy-subset.ppm", width, height,
                    (char *) out_image_subset);
    if (err != 0) exit(err);
    printf("INFO: subset filter done, from pixel %d, %d pixels\n",
            subset_start, subset_size);

/* Assertions:
 * 1. First 3rd of image data should match exactly between ORIGINAL and SUBSET
 *      filter.
 */
    int top = img_partition_head(subset_size, 0);
    assert(out_image_subset[top].red   == in_image[top].red);
    assert(out_image_subset[top].green == in_image[top].green);
    assert(out_image_subset[top].blue  == in_image[top].blue);

    int mid = img_partition_head(subset_size, 1);
    assert(out_image_subset[mid].red   != in_image[mid].red);
    assert(out_image_subset[mid].green != in_image[mid].green);
    assert(out_image_subset[mid].blue  != in_image[mid].blue);

    int btm = img_partition_head(subset_size, 2);
    assert(out_image_subset[btm].red   == in_image[btm].red);
    assert(out_image_subset[btm].green == in_image[btm].green);
    assert(out_image_subset[btm].blue  == in_image[btm].blue);

/* 2. SUBSET vs COMPLETE FILTER
 */
    assert(out_image_subset[top].red   != out_image_fuzzy[top].red);
    assert(out_image_subset[top].green != out_image_fuzzy[top].green);
    assert(out_image_subset[top].blue  != out_image_fuzzy[top].blue);

    assert(out_image_subset[mid].red   == out_image_fuzzy[mid].red);
    assert(out_image_subset[mid].green == out_image_fuzzy[mid].green);
    assert(out_image_subset[mid].blue  == out_image_fuzzy[mid].blue);

    assert(out_image_subset[btm].red   != out_image_fuzzy[btm].red);
    assert(out_image_subset[btm].green != out_image_fuzzy[btm].green);
    assert(out_image_subset[btm].blue  != out_image_fuzzy[btm].blue);


/*
 * The threshold transformation
 *
 */
    GPixel* out_thresh = (GPixel *) malloc(PPM_MAX_PIXELS * sizeof(GPixel));
    assert(out_thresh  != 0);

    threshold_filter(img, out_thresh );
    err = write_pgm("./im1-test-thresh.pgm", width, height,
                    (char *) out_thresh );
    if (err != 0) exit(err);

    // SUBSET
    GPixel* out_thresh_ss = (GPixel *) malloc(PPM_MAX_PIXELS * sizeof(GPixel));
    assert(out_thresh_ss  != 0);

    int pixels = width*height;
    //  TOP & BOTTOM: gray
    GPixel gray_pix = (int) 255/2;
    memset(out_thresh_ss, gray_pix, pixels * sizeof(GPixel));
    //  MIDDLE: apply filter
    double intensity = sum_subset_intensity(img, 0, pixels) / pixels;
    threshold_filter_subset(img, subset_start, subset_size, intensity,
        out_thresh_ss);
    err = write_pgm("./im1-test-thresh-subset.pgm", width, height,
                    (char *) out_thresh_ss );
    if (err != 0) exit(err);

    // ASSERTIONS:  subset vs. full filter
    assert(out_thresh_ss[top] != out_thresh[top]);
    mid = btm - 1;
    assert(out_thresh_ss[mid] == out_thresh[mid]);
    assert(out_thresh_ss[btm] != out_thresh[btm]);


    return 0;
}
