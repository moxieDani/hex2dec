#include <stdlib.h>
#include <string.h>
#include "apis.h"
#include "utils.h"

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
        unsigned char *byte_stream = NULL;
        size_t byte_stream_size = get_byte_stream(hexstr, &byte_stream);
        ret = get_descstr(byte_stream, byte_stream_size);
    }

    return ret;
}
