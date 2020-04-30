/* transform-parall.c
 * ------------------
 * Authors: Darwin Jacob Groskleg
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <mpi.h>

#include "ppm.h"
#include "filter_ppm.h"

enum TaskRanks {
    ConsoleIORank = 0
};

void make_ppm_pixel_dt(MPI_Datatype* MPI_PIXEL);
char* append_to_basename(const char* filename, const char* appendix);

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int cluster_size;
    MPI_Comm_size(MPI_COMM_WORLD, &cluster_size);

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
    if (rank == ConsoleIORank)
        printf("[%d]: infile name: %s\n", rank, image_filename);

    /* Create Pixel datatype for MPI */
    MPI_Datatype MPI_PIXEL;
    make_ppm_pixel_dt(&MPI_PIXEL);

    double t0,tf,t_delta_seconds;
    double seconds_per_tick = MPI_Wtick();

/*
 * Read and Share Initial PPM Image Data
 *
 */
    Pixel* in_image = (Pixel *) malloc(PPM_MAX_PIXELS * sizeof (Pixel));
    assert(in_image != 0);

    int width, height, max;
    int err = 0;
    if (rank == ConsoleIORank) {
        err = read_ppm(image_filename, &width, &height, &max, (char *)in_image);
        if (err != 0) MPI_Abort(MPI_COMM_WORLD, err);
        printf("[%d]: file read, %d pixels, %dpx wide, %dpx in height\n",
                rank, width*height, width, height);
    }
    MPI_Bcast(&width,  1, MPI_INT, ConsoleIORank, MPI_COMM_WORLD);
    MPI_Bcast(&height, 1, MPI_INT, ConsoleIORank, MPI_COMM_WORLD);
    MPI_Bcast(&max,    1, MPI_INT, ConsoleIORank, MPI_COMM_WORLD);
    MPI_Bcast(in_image, width*height, MPI_PIXEL, ConsoleIORank, MPI_COMM_WORLD);

    const Image img  = { .pixels=in_image, width, height, max };
    int subset_size  = img_partition_pixels(img.width*img.height, cluster_size);
    int subset_start = img_partition_head(subset_size, rank);


/*
 * The "fuzzy" transformation
 *
 */
    Pixel* out_image_fuzzy = (Pixel *) malloc(PPM_MAX_PIXELS * sizeof (Pixel));
    assert(out_image_fuzzy != 0);

    t0 = MPI_Wtime();
    int xradius = 5, yradius = 5;
    averaging_filter_subset(img, subset_start, subset_size, xradius, yradius,
            out_image_fuzzy);
    MPI_Gather(out_image_fuzzy+subset_start, subset_size, MPI_PIXEL,
               out_image_fuzzy,              subset_size, MPI_PIXEL,
               ConsoleIORank, MPI_COMM_WORLD);
    tf = MPI_Wtime();

    if (rank == ConsoleIORank) {
        char* fuzzy_fname = append_to_basename(image_filename,
                                               "-parall-fuzzy.ppm");
        err = write_ppm(fuzzy_fname, width, height, (char *) out_image_fuzzy);
        if (err != 0) MPI_Abort(MPI_COMM_WORLD, err);

        printf("[%d]: Averaging Filter: Neighborhood radius |x y|: %d %d\n",
                rank,                             xradius, yradius);

        t_delta_seconds = (tf - t0) * seconds_per_tick;
        printf("[%d]: Averaging Filter: %d node parallel computation time: ",
                rank,             cluster_size);
        printf("%g seconds\n", t_delta_seconds);
    }


/*
 * The threshold transformation
 *
 */
    GPixel* out_image_thresh = (GPixel *) malloc(PPM_MAX_PIXELS * sizeof (GPixel));
    assert(out_image_thresh != 0);

    t0 = MPI_Wtime();
    double local_intensity=sum_subset_intensity(img, subset_start, subset_size);
    double global_threshold;
    MPI_Allreduce(&local_intensity, &global_threshold, 1, MPI_DOUBLE, MPI_SUM,
            MPI_COMM_WORLD);
    global_threshold /= img.width * img.height;
    threshold_filter_subset(img, subset_start, subset_size, global_threshold,
            out_image_thresh);

    MPI_Gather(out_image_thresh + subset_start, subset_size, MPI_UNSIGNED_CHAR,
               out_image_thresh,                subset_size, MPI_UNSIGNED_CHAR,
               ConsoleIORank, MPI_COMM_WORLD);
    tf = MPI_Wtime();

    if (rank == ConsoleIORank) {
        char* threshold_fname = append_to_basename(image_filename,
                                                   "-parall-threshold.pgm");
        err = write_pgm(threshold_fname, width, height,
                        (char *) out_image_thresh);
        if (err != 0) exit(err);

        printf("[%d]: Threshold Filter: Overall average intensity is: %f\n",
                rank, global_threshold);
        t_delta_seconds = (tf - t0) * seconds_per_tick;
        printf("[%d]: Threshold Filter: %d node parallel computation time: ",
                rank, cluster_size);
        printf("%g seconds\n", t_delta_seconds);
        fflush(stdout);
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}

void make_ppm_pixel_dt(MPI_Datatype* MPI_PIXEL) {
    int lengths[3] = {1,1,1};
    const MPI_Aint displacements[3] = {
        0,
        sizeof (unsigned char),
        2 * sizeof (unsigned char)
    };
    MPI_Datatype types[3] = {
        MPI_UNSIGNED_CHAR, MPI_UNSIGNED_CHAR, MPI_UNSIGNED_CHAR
    };
    MPI_Type_create_struct(3, lengths, displacements, types, MPI_PIXEL);
    MPI_Type_commit(MPI_PIXEL);
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

