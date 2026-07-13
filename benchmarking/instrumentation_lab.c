#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 50000
#define SEED_VALUE 42u

static int dataset[DATASET_SIZE];

static unsigned int next_value(unsigned int *state)
{
	*state = (*state * 1103515245u) + 12345u;
	return *state;
}

static void build_dataset(void)
{
	unsigned int state;
	int i;

	state = SEED_VALUE;

	for (i = 0; i < DATASET_SIZE; i++)
		dataset[i] = (int)(next_value(&state) % 100000);
}

static void process_dataset(void)
{
	int i;
	int v;

	for (i = 0; i < DATASET_SIZE; i++)
	{
		v = dataset[i];
		v = (v * 3) + (v / 7) - (v % 11);
		if (v < 0)
			v = -v;
		dataset[i] = v;
	}
}

static unsigned long reduce_checksum(void)
{
	unsigned long sum;
	int i;

	sum = 0;
	for (i = 0; i < DATASET_SIZE; i++)
		sum = (sum * 131ul) + (unsigned long)dataset[i];

	return sum;
}

int main(void)
{
	unsigned long checksum;
	clock_t t0, t1, t2, t3;
	double total, build, process, reduce;

	t0 = clock();
	build_dataset();
	t1 = clock();
	process_dataset();
	t2 = clock();
	checksum = reduce_checksum();
	t3 = clock();

	build = (double)(t1 - t0) / (double)CLOCKS_PER_SEC;
	process = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;
	reduce = (double)(t3 - t2) / (double)CLOCKS_PER_SEC;
	total = (double)(t3 - t0) / (double)CLOCKS_PER_SEC;

	if (checksum == 0ul)
		printf("impossible\n");

	printf("TOTAL seconds: %.6f\n", total);
	printf("BUILD_DATA seconds: %.6f\n", build);
	printf("PROCESS seconds: %.6f\n", process);
	printf("REDUCE seconds: %.6f\n", reduce);

	return 0;
}
