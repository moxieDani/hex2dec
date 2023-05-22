#include <ctype.h>
#include <stdlib.h>

unsigned char div10(unsigned char *hex, unsigned int size);
char* get_descstr(unsigned char* byte_stream, size_t byte_stream_size);
size_t get_byte_stream(const char *in_stream, unsigned char **out_stream);
int is_all_zeros(const char *str);