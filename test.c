#define PLALLOC_IMPLEMENTATION
#define PLALLOC_DEBUG 0
#include "plalloc.h"

struct buzz {
	int hit;
	int val;
};

int fuzz_allocs = 0;
int fuzz_frees  = 0;

#define HIT 350
#define LIMIT 5
#define SPEED 1

#define ABS(x) (x)>0?(x):-(x)

static void fuzzer(void) {
	FILE *RND = fopen("/dev/random", "r");
	assert(RND != NULL);

	struct buzz* arr[200] = {0};
	plalloc_t A = plalloc_initialize(sizeof(struct buzz), 50);
	//srand(clock() * time(NULL));

	while (fuzz_allocs < HIT || fuzz_frees < HIT) {
		int idx = getc(RND)%200;//rand()%300;
		if (!arr[idx] && fuzz_allocs < HIT) {
			arr[idx] = (struct buzz*)plalloc_alloc(A);
			arr[idx]->val = (int)arr[idx];
			putchar('a');
			fuzz_allocs++;
		} else if (arr[idx]) {
			int action = (rand() % (SPEED+1))*2 - SPEED;
			assert(arr[idx]->val == (int)arr[idx]);
			arr[idx]->hit += action;
			if (arr[idx]->hit > LIMIT || arr[idx]->hit < -LIMIT) {
				(arr[idx]->hit>0)? putchar('z') : putchar('h');
				plalloc_free(A, arr[idx]);
				fuzz_frees++;
				arr[idx] = NULL;
			} else if (ABS(arr[idx]->hit) > LIMIT-SPEED*2) putchar('o');
		} 
	}

	plalloc_uninitialize(A);
	fclose(RND);
}

int main() {
	plalloc_t A = plalloc_initialize(sizeof(int), 100);
	int* arr[100];
	assert(A);
	
	for (int i = 0; i < 100; i++) {
		arr[i] = (int*)plalloc_alloc(A);
		*arr[i] = i;
	}

	// SANITY CHECK
	int *old = arr[1];
	int diff = arr[1] - arr[0];
	for (int i = 2; i < 100; i++) {
		assert(diff == (arr[i] - old));
		diff = (arr[i] - old);
		old = arr[i];
	}

	for (int i = 2; i < 100; i += 6) {
		plalloc_free(A, arr[i]);
		arr[i] = plalloc_alloc(A);
		*arr[i] = i;
	}
		
	for (int i = 0; i < 100; i++) {
		assert(*arr[i] == i);
	}

	for (int i = 0; i < 100; i++) {
		plalloc_free(A, arr[i]);
		arr[i] = NULL;
	}

	plalloc_uninitialize(A);
	fuzzer();
}
