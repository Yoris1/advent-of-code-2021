#include <stddef.h>
typedef struct d_array {
	void* raw;
	size_t count;
	size_t _element_size;
	size_t _length;
} d_array;
d_array* create_dynamic_array(size_t initial_length, size_t element_size);
void add_to_dynamic_array(d_array* arr, const void* item);
void delete_dynamic_array(d_array* arr);