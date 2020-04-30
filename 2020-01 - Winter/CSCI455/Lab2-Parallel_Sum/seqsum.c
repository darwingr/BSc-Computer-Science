/* seqsum.c
 * --------
 * Authors: Darwin Jacob Groskleg
 *
 * Sums up numbers in a given file sequentially.
 */
#include <stdio.h>
#include <stdlib.h>

void show_usage(char* pgm) {
    printf("Usage: %s path/to/datafile.txt\n", pgm);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        show_usage(argv[0]);
    }

    //char* datafilename = "given/rand_data.txt";
    char* datafilename = argv[1];
    FILE *fp;
    if ((fp = fopen(datafilename,"r")) == NULL) {
        printf("Can't open the input file: %s\n\n", datafilename);
        exit(1);
    }

    int z, count = 0;
    long long running_sum = 0;
    fscanf(fp, "%d", &z);
    while (!feof(fp)) {
        count++;
        running_sum += z;
        fscanf(fp, "%d", &z);
    }
    fclose(fp);

    printf("%s contains %d numbers.\n", datafilename, count);
    printf("Global sum: %lld\n", running_sum);

    return 0;
}
