#include <cstdio>

/* Prints out a combination like {1, 2} */
void printc(int comb[], int k) {
	printf("{");
	int i;
	for (i = 0; i < k; ++i)
		printf("%d, ", comb[i] + 1);
	printf("\b\b}\n");
}

/*
	next_comb(int comb[], int k, int n)
		Generates the next combination of n elements as k after comb

	comb => the previous combination ( use (0, 1, 2, ..., k) for first)
	k => the size of the subsets to generate
	n => the size of the original set

	Returns: 1 if a valid combination was found
		0, otherwise
*/
int next_comb(int comb[], int k, int n) {
	int i = k - 1;
	++comb[i];
	while ((i >= 0) && (comb[i] >= n - k + 1 + i)) {
		--i;
		++comb[i];
	}

	if (comb[0] > n - k) /* Combination (n-k, n-k+1, ..., n) reached */
		return 0; /* No more combinations can be generated */

	/* comb now looks like (..., x, n, n, n, ..., n).
	Turn it into (..., x, x + 1, x + 2, ...) */
	for (i = i + 1; i < k; ++i)
		comb[i] = comb[i - 1] + 1;

	return 1;
}

int main(int argc, char *argv[]) {
	int n = 5; /* The size of the set; for {1, 2, 3, 4} it's 4 */
	int k = 3; /* The size of the subsets; for {1, 2}, {1, 3}, ... it's 2 */
	int comb[16]; /* comb[i] is the index of the i-th element in the
			combination */

	/* Setup comb for the initial combination */
	int i;
	for (i = 0; i < k; ++i)
		comb[i] = i;

	/* Print the first combination */
	printc(comb, k);

	/* Generate and print all the other combinations */
	while (next_comb(comb, k, n))
		printc(comb, k);

	return 0;
}
