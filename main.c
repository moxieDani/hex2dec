#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
unsigned char *get_byte_stream(const char *in_stream, size_t *byte_stream_length)
{
    size_t in_stream_length = strlen(in_stream);
    *byte_stream_length = (in_stream_length + 1) / 2;
    unsigned char *ret = (unsigned char *)malloc(*byte_stream_length);
    memset(ret, 0, *byte_stream_length);

    int start_index = 0;

    if (in_stream_length % 2)
    {
        ret[0] = (isalpha(in_stream[0]) ? tolower(in_stream[0]) - 'a' + 10 : in_stream[0] - '0');
        start_index++;
    }

    for (int i = start_index; i < in_stream_length; i += 2)
    {
        ret[start_index] = (isalpha(in_stream[i]) ? tolower(in_stream[i]) - 'a' + 10 : in_stream[i] - '0') << 4;
        ret[start_index] += (isalpha(in_stream[i + 1]) ? tolower(in_stream[i + 1]) - 'a' + 10 : in_stream[i + 1] - '0');
        start_index++;
    }

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

// Convert hex string to decimal string
char *hexstr_to_decstr(const char *hexstr)
{
    char *ret = NULL;
    if (is_all_zeros(hexstr))
    {
        size_t ret_size = 2;
        ret = (char *)malloc(ret_size);
        strncpy(ret, "0", ret_size);
    } else {
        // Get byte stream and byte stream size from char stream.
        size_t byte_stream_size = 0;
        unsigned char *byte_stream = get_byte_stream(hexstr, &byte_stream_size);
        ret = get_descstr(byte_stream, byte_stream_size);
    }

    return ret;
}
 
struct test_case {
    const char *hexstr;
    const char *decstr;
};
 
int main(void)
{
    // Test cases for hexstr_to_decstr()
    const struct test_case cases[] = {
        {"0", "0"},
        {"000", "0"},
        {"FFFFFFFF", "4294967295"},
        {"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "5444517870735015415413993718908291383295"},
        {NULL, NULL}
    };
    const struct test_case *t;
 
    for (t = cases; t->hexstr != NULL; t++) {
        char *decstr;
 
        decstr = hexstr_to_decstr(t->hexstr);
 
        if (strcmp(decstr, t->decstr) == 0) {
            printf("[pass] %s -> %s\n", t->hexstr, decstr);
        } else {
            printf("[fail] %s -> %s (expected %s)\n", t->hexstr, decstr, t->decstr);
        }
 
        free(decstr);
    }
 
    return 0;
}