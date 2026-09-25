#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define WIDTH 1000
#define HEIGHT 1000
#define MAX_ITER 2000

int main(int argc, char *argv[]) {

    int num_threads = 1;

    if (argc > 1)
        num_threads = atoi(argv[1]);

    omp_set_num_threads(num_threads);

    int inside = 0;

    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:inside)
    for (int y = 0; y < HEIGHT; y++) {

        double ci = -1.5 + 3.0 * y / (HEIGHT - 1);

        for (int x = 0; x < WIDTH; x++) {

            double cr = -2.0 + 2.5 * x / (WIDTH - 1);

            double zr = 0.0;
            double zi = 0.0;

            int iter;

            for (iter = 0; iter < MAX_ITER; iter++) {

                double zr2 = zr * zr;
                double zi2 = zi * zi;

                if (zr2 + zi2 > 4.0)
                    break;

                zi = 2.0 * zr * zi + ci;
                zr = zr2 - zi2 + cr;
            }

            if (iter == MAX_ITER)
                inside++;
        }
    }

    double end_time = omp_get_wtime();

    double area = (double)inside / (WIDTH * HEIGHT) * 2.0 * 2.5;

    printf("Threads: %d\n", num_threads);
    printf("Points inside: %d\n", inside);
    printf("Estimated area: %.6f\n", area);
    printf("Time: %.6f seconds\n", end_time - start_time);

    return 0;
}
