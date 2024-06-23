#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_tree.h"
#ifndef LINUX
#include <Windows.h>
#endif

int main(void)
{
    struct node *root = NULL;

    // initialize random seed
    srand((unsigned) time(NULL));

    #if defined(_WIN32) || defined(_WIN64)
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
    #endif
    for (int i = 5; i <= 25; i += 1)
    {
        int n = 1 << i;
        double interval;

        #if defined(_WIN32) || defined(_WIN64)
            LARGE_INTEGER start;
            LARGE_INTEGER end;

            QueryPerformanceCounter(&start);

            for (int j = 0; j < n; j++)
            {
                int random = rand();
                insert(&root, random);
            }

            QueryPerformanceCounter(&end);
            interval = (double) 1000*(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        #else
            clock_t start = clock();
            for (int j = 0; j < n; j++)
            {
                int random = rand();
                insert(&root, random);
            }

            clock_t end = clock();
            /* clock_t begin = clock(); */
            /* int pos = find(array, n, random); */
            /* clock_t end = clock(); */
            /* double time_spent = (double)(end - begin); */

            /* printf("pow: %i elems: %i pos: %i time: %f\n", i, n, pos, time_spent); */
            interval = (double) 1000 * (end - start) / CLOCKS_PER_SEC;
        #endif

        printf("%i %f\n", i, interval);
        delete_tree(root);
        root = NULL;
    }

    return 0;
}
