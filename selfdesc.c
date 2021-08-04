#include <stdio.h>
#include <stdlib.h>

#define BASE_MIN 2

void selfdesc(int, int, int, int);

int *nums, *inds, base, cost;

int main(int argc, char *argv[]) {
	int base_min, base_max;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s base_min base_max\n", argv[0]);
		fflush(stderr);
		return EXIT_FAILURE;
	}
	base_min = atoi(argv[1]);
	if (base_min < BASE_MIN) {
		fprintf(stderr, "Invalid base_min\n");
		fflush(stderr);
		return EXIT_FAILURE;
	}
	base_max = atoi(argv[2]);
	if (base_max < base_min) {
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
	for (base = base_min; base <= base_max; base++) {
		cost = 0;
		selfdesc(base-1, base, base, 0);
		printf("Cost %d\n", cost);
		fflush(stdout);
	}
	free(inds);
	free(nums);
	return EXIT_SUCCESS;
}

void selfdesc(int pos, int target_sum, int target_val, int delta_sum) {
	int i;
	cost++;
	if (pos >= 0) {
		int lower = nums[pos], upper, upper_alt, delta;
		if (pos > 0) {
			upper = target_val/pos+nums[pos];
			upper_alt = target_sum-nums[0]-pos+1;
			if (upper_alt < upper) {
				upper = upper_alt;
			}
		}
		else {
			upper = target_sum;
			upper_alt = target_sum;
		}
		if (upper == base) {
			upper--;
		}
		if (pos > upper) {
			for (i = lower; i <= upper; i++) {
				delta = i-nums[pos];
				if (target_val-i < delta*pos || delta_sum+delta > pos) {
					break;
				}
				if (i == 0 || nums[i] < upper_alt) {
					nums[i]++;
					inds[pos] = i;
					selfdesc(pos-1, target_sum-i, target_val-i-delta*pos, delta_sum+delta);
					nums[i]--;
				}
			}
		}
		else if (pos >= lower && pos <= upper) {
			for (i = lower; i < pos; i++) {
				delta = i-nums[pos];
				if (target_val-i < delta*pos || delta_sum+delta > pos) {
					break;
				}
				if (i == 0 || nums[i] < upper_alt) {
					nums[i]++;
					inds[pos] = i;
					selfdesc(pos-1, target_sum-i, target_val-i-delta*pos, delta_sum+delta);
					nums[i]--;
				}
			}
			delta_sum--;
			delta = pos-nums[pos];
			if (delta_sum+delta <= pos && nums[pos] < pos) {
				nums[pos]++;
				inds[pos] = pos;
				selfdesc(pos-1, target_sum-pos, target_val-delta*pos, delta_sum+delta);
				nums[pos]--;
			}
			for (i = pos+1; i <= upper; i++) {
				delta = i-nums[pos];
				if (delta_sum+delta > pos) {
					break;
				}
				if (nums[i] < inds[i]) {
					nums[i]++;
					inds[pos] = i;
					selfdesc(pos-1, target_sum-i, target_val-delta*pos, delta_sum+delta);
					nums[i]--;
				}
			}
		}
		else {
			delta_sum--;
			for (i = lower; i <= upper; i++) {
				delta = i-nums[pos];
				if (delta_sum+delta > pos) {
					break;
				}
				if (nums[i] < inds[i]) {
					nums[i]++;
					inds[pos] = i;
					selfdesc(pos-1, target_sum-i, target_val-delta*pos, delta_sum+delta);
					nums[i]--;
				}
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
