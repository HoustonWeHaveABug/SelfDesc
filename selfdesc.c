#include <stdio.h>
#include <stdlib.h>

#define BASE_MIN 2

void selfdesc(int, int, int, int, int);
void choose_val(int, int, int, int, int, int);

int *nums, *inds, base, cost;

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
		cost = 0;
		selfdesc(base-1, base, base, base, 0);
		printf("Cost %d\n", cost);
		fflush(stdout);
	}
	free(inds);
	free(nums);
	return EXIT_SUCCESS;
}

void selfdesc(int pos, int inds_sum, int inds_not0, int inds_val, int delta_sum) {
	int i;
	cost++;
	if (pos >= 0) {
		int lower = nums[pos], upper1, upper2;
		if (lower == pos) {
			lower++;
		}
		if (pos > 0) {
			upper1 = inds_sum-inds_not0+2;
			upper2 = (inds_val+nums[pos]*pos)/pos;
			if (upper2 < upper1) {
				upper1 = upper2;
			}
		}
		else {
			upper1 = inds_sum;
		}
		if (upper1 == base) {
			upper1--;
		}
		for (i = lower; i <= upper1 && i < pos; i++) {
			choose_val(pos, inds_sum, inds_not0, inds_val-i, delta_sum, i);
		}
		if (i <= upper1 && i == pos) {
			choose_val(pos, inds_sum, inds_not0, inds_val, delta_sum, i);
			i++;
		}
		for (; i <= upper1; i++) {
			if (nums[i] < inds[i]) {
				choose_val(pos, inds_sum, inds_not0, inds_val, delta_sum-1, i);
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

void choose_val(int pos, int inds_sum, int inds_not0, int inds_val, int delta_sum, int val) {
	int delta;
	nums[val]++;
	delta = val-nums[pos];
	if (delta_sum+delta <= pos) {
		inds[pos] = val;
		selfdesc(pos-1, inds_sum-val, inds_not0-(val > 0), inds_val-delta*pos, delta_sum+delta);
	}
	nums[val]--;
}
