#include "dynamic_array.h"
#include <stdlib.h>

d_array *create_dynamic_array(size_t initial_length, size_t element_size) {
	d_array* arr = malloc(sizeof(d_array));
	
	initial_length = initial_length<1?1:initial_length;
	
	arr->raw = malloc(initial_length*element_size);
	arr->count = 0;

	arr->_length = initial_length;
	arr->_element_size = element_size;
	return arr;
}

void add_to_dynamic_array(d_array* arr, const void* item) {
	if(arr->count >= arr->_length) {
		arr->_length += 10;
		arr->raw = realloc(arr->raw, arr->_element_size * arr->_length);
	}
	
	char* raw = arr->raw;
	for(size_t i = 0; i < arr->_element_size; i++) {
		unsigned char byte = ((char*)item)[i];
		raw[arr->count*arr->_element_size+i] = byte;
	}
	arr->count ++;
}

void delete_dynamic_array(d_array* arr) {
	free(arr->raw);
	free(arr);
}