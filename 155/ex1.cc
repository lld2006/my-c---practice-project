#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXCAPS 18
#define MAXANS  10000000

static double combo_list[MAXCAPS + 1][MAXANS];
static int n_combos[MAXCAPS + 1];
#define VALUE 60.0

static int cmpf (const void *a, const void *b)
{
    double fa, fb;
    fa = *((double *)a);
    fb = *((double *)b);
    if (fa < fb)
    {
        return -1;
    }
    if (fa > fb)
    {
        return 1;
    }
    return 0;
}

static int dedupe (int n, double *data)
{
    int getter, putter;
    int i;
    double prevf;

    qsort (data, n, sizeof (double), cmpf);

    prevf = -1.0;
    putter = 0;
    for (getter = 0; getter < n; getter++)
    {
        if (data[getter] != prevf)
        {
            double delta;
            delta = fabs ((data[getter] - prevf) / prevf);
            if (delta > .00000000001)
            {
                prevf = data[getter];
                data[putter++] = prevf;
            }
        }
    }
    return putter;
}

static void add_result (int n, double cap)
{
    int i = n_combos[n];
    if (i == MAXANS)
    {
        i = dedupe (i, combo_list[n]);
    }

    if (i == MAXANS)
    {
        fprintf (stderr, "Too many results for %d capacitors.\n", n);
        exit (1);
    }
    combo_list[n][i] = cap;
    n_combos[n] = ++i;
}

int main (int argc, char *argv[])
{
    int i, j, n, sum = 1;

    memset (combo_list, 0, sizeof (combo_list));
    memset (n_combos, 0, sizeof (n_combos));
    add_result (1, VALUE);

    for (n = 2; n <= 18; n++)
    {
        for (i = 1; i <= n/2; i++)
        {
            j = n - i;

            int i1, i2;
            double c1, c2;

            for (i1 = 0; i1 < n_combos[i]; i1++)
            {
                c1 = combo_list[i][i1];
                for (i2 = 0; i2 < n_combos[j]; i2++)
                {
                    c2 = combo_list[j][i2];
                    add_result (n, c1 + c2);
                    add_result (n, 1.0/(1.0/c1 + 1.0/c2));
                }
            }
        }
        n_combos[n] = dedupe (n_combos[n], combo_list[n]);
        printf ("%d caps - %d possibilities\n", n, n_combos[n]);
        fflush (stdout);
        for (i = 0; i < n_combos[n]; i++)
        {
            add_result (0, combo_list[n][i]);
        }
    }
    n_combos[0] = dedupe (n_combos[0], combo_list[0]);
    printf ("Answer: %d\n", n_combos[0]);
    return 0;
}
