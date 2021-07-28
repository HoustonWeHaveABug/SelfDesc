#include <stdio.h>
#include <stdlib.h>

#define BASE_MIN 2

void selfdesc(int, int, int, int);

int *nums, *inds, base;

int main(int argc, char *argv[]) {
	int base_max;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <base_max>\n", argv[0]);
		fflush(stderr);
		return EXIT_FAILURE;
	}
	base_max = atoi(argv[1]);
	if (base_max < BASE_MIN) {
		fprintf(stderr, "Invalid base_max\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	nums = calloc((size_t)base_max, sizeof(int));
	if (!nums) {
		fprintf(stderr, "Could not allocate memory for nums\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	inds = malloc(sizeof(int)*(size_t)base_max);
	if (!inds) {
		fprintf(stderr, "Could not allocate memory for inds\n");
		fflush(stderr);
		free(nums);
		return EXIT_FAILURE;
	}
	for (base = BASE_MIN; base <= base_max; base++) {
		selfdesc(base-1, base, base, 0);
	}
	free(inds);
	free(nums);
	return EXIT_SUCCESS;
}

void selfdesc(int pos, int inds_sum, int inds_val, int delta) {
	int i;
	if (pos >= 0) {
		int lower = nums[pos], upper;
		if (lower == pos) {
			lower++;
		}
		if (pos > 0) {
			upper = inds_val/pos;
		}
		else {
			upper = inds_sum;
		}
		if (upper == base) {
			upper--;
		}
		for (i = lower; i <= upper; i++) {
			if (i > pos) {
				if (nums[i] >= inds[i]) {
					continue;
				}
				delta--;
			}
			nums[i]++;
			inds[pos] = i;
			if (delta+i-nums[pos] <= pos) {
				selfdesc(pos-1, inds_sum-i, inds_val-i*pos, delta+i-nums[pos]);
			}
			nums[i]--;
			if (i > pos) {
				delta++;
			}
		}
		return;
	}
	printf("Base %d [ %d", base, inds[0]);
	for (i = 1; i < base; i++) {
		printf(", %d", inds[i]);
	}
	puts(" ]");
	fflush(stdout);
}
