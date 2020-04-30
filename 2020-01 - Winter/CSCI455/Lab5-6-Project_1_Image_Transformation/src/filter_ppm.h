/* filter_ppm.h
 * ------------
 * Authors: Darwin Jacob Groskleg
 *
 * Purpose: extract filtering methods from both programs to make them more
 *          testable by comparison.
 *          Extension of ppm image struct.
 *
 * Filters: take image data & image metadata (width, height),
 *          mutating the output img pointer data.
 */
#ifndef FILTER_PPM_H_INCLUDED
#define FILTER_PPM_H_INCLUDED

#include "ppm.h"
#include <math.h>

void averaging_filter(const Image img, int x_radius, int y_radius,
        Pixel* extant_img);
void averaging_filter_subset(const Image img, int start_pos, int count,
        int x_radius, int y_radius,
        Pixel* extant_img);

double threshold_filter(const Image img, GPixel* extant_img);
double sum_subset_intensity(const Image img, int start_pos, int count);
void threshold_filter_subset(const Image img, int start_pos, int count,
        double threshold, GPixel* extant_img);


/* Helpers for Subset Filtering
 *  they're only helpers so go ahead and show the implementation for now.
 */

/* how many pixels in a partition? */
inline int img_partition_pixels(int pixel_area, int partitions) {
    return ceil(pixel_area / (float) partitions);
}

/* partition_size == pixels in a partition */
inline int img_partition_head(int partition_size, int kth_subset) {
    return partition_size * kth_subset;
}


#endif // FILTER_PPM_H_INCLUDED
