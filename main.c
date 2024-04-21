#include "vec.h"

int main(void) {
	Vec vec = vec_new_with_cap(sizeof(int), 1);

	for (int i = 0; i < 10; i += 1) {
		vec_push(&vec, &i);
	}

	for (int i = 0; i < 5; i += 1) {
		vec_pop(&vec, NULL);
	}

	for (int i = 0; i < 5; i += 1) {
		int result;
		vec_pop(&vec, &result);
		printf("%d,cap=%zu|", result, vec.cap);
	}
	printf("\n");

	return 0;
}
