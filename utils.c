#include <string.h>
#include "utils.h"

// Convert hex to 256 base digit.
unsigned char div10(unsigned char *hex, unsigned int size)
{
    unsigned rem = 0;
    for (int i = 0; i < size; i++)
    {
        unsigned n = rem * 256 + hex[i];
        hex[i] = n / 10;
        rem = n % 10;
    }

    return rem;
}

// Convert byte stream to decimal str.
char* get_descstr(unsigned char* byte_stream, size_t byte_stream_size)
{
    size_t ret_size = 1;
    char* ret = (char *)malloc(ret_size);
    ret[0] = '\0';
    
    unsigned char *byte_stream_zero = (unsigned char *)malloc(byte_stream_size);
    memset(byte_stream_zero, 0, byte_stream_size);
    
    while (memcmp(byte_stream, byte_stream_zero, byte_stream_size) != 0)
    {
        ret_size++;
        char *temp_div10 = (char *)malloc(ret_size);
        memcpy(temp_div10 + 1, ret, ret_size - 1);
        temp_div10[0] = div10(byte_stream, byte_stream_size) + '0';
        free(ret);
        ret = temp_div10;
    }
    
    free(byte_stream);
    free(byte_stream_zero);

    return ret;
}

// Convert hex string to byte stream.
size_t get_byte_stream(const char *in_stream, unsigned char **out_stream)
{
    size_t in_stream_length = strlen(in_stream);
    size_t ret = (in_stream_length + 1) / 2;
    unsigned char *byte_stream = (unsigned char *)malloc(ret);
    memset(byte_stream, 0, ret);

    int start_index = 0;

    if (in_stream_length % 2)
    {
        byte_stream[0] = (isalpha(in_stream[0]) ? tolower(in_stream[0]) - 'a' + 10 : in_stream[0] - '0');
        start_index++;
    }

    for (int i = start_index; i < in_stream_length; i += 2)
    {
        byte_stream[start_index] = (isalpha(in_stream[i]) ? tolower(in_stream[i]) - 'a' + 10 : in_stream[i] - '0') << 4;
        byte_stream[start_index] += (isalpha(in_stream[i + 1]) ? tolower(in_stream[i + 1]) - 'a' + 10 : in_stream[i + 1] - '0');
        start_index++;
    }

    *out_stream = byte_stream;

    return ret;
}

// Check if the input string consists of all '0'.
int is_all_zeros(const char *str)
{
    while (*str != '\0')
    {
        if (*str != '0')
        {
            return 0;
        }
        str++;
    }
    return 1;
} 
