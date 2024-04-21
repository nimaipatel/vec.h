#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
	size_t cap;
	size_t len;
	size_t unit_size;
	void *data;
} Vec;

#define VEC_SUCC   0
#define VEC_NO_MEM 1
#define VEC_OFB    2

// TODO: need to make this read only
Vec nil_vec = {0};

Vec vec_new_with_cap(size_t unit_size, size_t cap) {
	assert(cap > 0);
	Vec vec = {0};
	vec.cap = cap;
	vec.len = 0;
	vec.unit_size = unit_size;
	void *data = malloc(vec.cap * vec.unit_size);
	if (data == NULL) {
		return nil_vec;
	}
	vec.data = data;
	return vec;
}

int vec_push(Vec *vec, void *item) {
	assert(item != NULL);
	if (vec->len == vec->cap) {
		size_t cap = vec->cap * 2;
		void *data = realloc(vec->data, cap * vec->unit_size);
		if (data == NULL) {
			return VEC_NO_MEM;
		}
		vec->cap = cap;
		vec->data = data;
	}

	memcpy((uint8_t *)vec->data + (vec->unit_size * vec->len), item, vec->unit_size);
	vec->len += 1;

	return VEC_SUCC;
}

int vec_pop(Vec *vec, void *item) {
	if (vec->len == 0) {
		return VEC_OFB;
	}

	if (item != NULL) {
		memcpy(item, (uint8_t*)vec->data + (vec->unit_size * (vec->len - 1)), vec->unit_size);
	}
	vec->len -= 1;

	if (vec->len < vec->cap / 2) {
		// assumption: realloc can not fail when shrinking
		vec->cap /= 2;
		vec->data = realloc(vec->data, vec->cap * vec->unit_size);
	}

	return VEC_SUCC;
}

int vec_swap_remove(Vec *vec, size_t index, void *item) {
	if (index < vec->len) {
		return VEC_OFB;
	}

	if (item != NULL) {
		memcpy(item, (uint8_t *)vec->data + (vec->unit_size * index), vec->unit_size);
	}

	size_t last_index = vec->len - 1;
	size_t unit_size = vec->unit_size;
	uint8_t *data = vec->data;
	memcpy(data + (unit_size * index), data + (unit_size * last_index), unit_size);
	vec->len -= 1;

	if (vec->len < vec->cap / 2) {
		// assumption: realloc can not fail when shrinking
		vec->cap /= 2;
		vec->data = realloc(vec->data, vec->cap * vec->unit_size);
	}

	return VEC_SUCC;
}
