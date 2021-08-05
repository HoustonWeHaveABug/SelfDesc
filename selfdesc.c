#include <stdio.h>
#include <stdlib.h>

#define BASE_MIN 2

void selfdesc(int, int, int);
void choose_ind(int, int, int, int, int);

int *nums, *inds, base;

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
		selfdesc(base-1, base, base);
	}
	free(inds);
	free(nums);
	return EXIT_SUCCESS;
}

void selfdesc(int pos, int target_sum, int target_val) {
	int i;
	if (pos >= 0) {
		int zeros = nums[0], lower = nums[pos], upper;
		if (pos > 0) {
			int upper_alt;
			if (target_sum < base) {
				while (pos > 2) {
					nums[0]++;
					inds[pos--] = 0;
				}
			}
			else {
				if (pos < base-3 && lower == 0) {
					lower++;
				}
			}
			upper = target_val/pos+nums[pos];
			upper_alt = target_sum-nums[0]-pos+1;
			if (upper_alt < upper) {
				upper = upper_alt;
			}
		}
		else {
			upper = target_sum;
		}
		if (upper == base) {
			upper--;
		}
		if (pos > upper) {
			for (i = lower; i <= upper; i++) {
				int delta = i+(i-nums[pos])*pos;
				if (target_val < delta) {
					break;
				}
				choose_ind(pos, target_sum, target_val, i, delta);
			}
		}
		else if (pos >= lower && pos <= upper) {
			for (i = lower; i < pos; i++) {
				int delta = i+(i-nums[pos])*pos;
				if (target_val < delta) {
					break;
				}
				choose_ind(pos, target_sum, target_val, i, delta);
			}
			if (nums[pos] < pos) {
				choose_ind(pos, target_sum, target_val, pos, (pos-nums[pos])*pos);
			}
			for (i = pos+1; i <= upper; i++) {
				if (nums[i] < inds[i]) {
					choose_ind(pos, target_sum, target_val, i, (i-nums[pos])*pos);
				}
			}
		}
		else {
			for (i = lower; i <= upper; i++) {
				if (nums[i] < inds[i]) {
					choose_ind(pos, target_sum, target_val, i, (i-nums[pos])*pos);
				}
			}
		}
		nums[0] = zeros;
		return;
	}
	printf("Base %d [ %d", base, inds[0]);
	for (i = 1; i < base; i++) {
		printf(", %d", inds[i]);
	}
	puts(" ]");
	fflush(stdout);
}

void choose_ind(int pos, int target_sum, int target_val, int ind, int delta) {
	nums[ind]++;
	inds[pos] = ind;
	selfdesc(pos-1, target_sum-ind, target_val-delta);
	nums[ind]--;
}
