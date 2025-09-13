#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATUS_OK 0

int string_rpad(const char* source_str, char pad_char, int len, char* dest_str)
{
    unsigned int src_len;
    src_len = strlen(source_str);
    if (src_len > len)
    { 
        printf("string length longer than expected\n");
        return -1;
    }
    memset(dest_str, pad_char, len);
    memcpy(dest_str, source_str, src_len);
    dest_str[len] = '\0';
    return STATUS_OK;
}

int main()
{
    const int SOURCE_LEN = 10000;
    const int DEST_LEN = 4096;
    char* source;
    char* dest;
    int ret;
    int test_pass;
    int i;

    source = (char*)malloc(SOURCE_LEN + 1);
    if (source == NULL)
    {
        perror("malloc source failed");
        return 1;
    }
    memset(source, 'A', SOURCE_LEN);
    source[SOURCE_LEN] = '\0';

    dest = (char*)malloc(DEST_LEN + 16);
    if (dest == NULL)
    {
        perror("malloc dest failed");
        free(source);
        return 1;
    }
    memset(dest, 0xCC, DEST_LEN + 16);

    printf("=== Testing: Source string (10000 bytes) Destination buffer (4096 bytes) ===\n");
    ret = string_rpad(source, 'X', SOURCE_LEN, dest);

    test_pass = 1;
    if (ret != -1)
    {
        printf("Error: Return value should be -1, actual is %d\n", ret);
        test_pass = 0;
    }
    else
    {
        printf("Correct: Return value is -1 (source length exceeds destination)\n");
    }

    for (i = 0; i < DEST_LEN + 16; i++)
    {
        if (dest[i] != 0xCC)
        {
            printf("Error: Destination buffer byte %d modified unexpectedly (original 0xCC, current 0x%02X)\n", 
                   i, (unsigned char)dest[i]);
            test_pass = 0;
            break;
        }
    }
    if (test_pass)
    {
        printf("Correct: Destination buffer not modified unexpectedly\n");
    }

    free(source);
    free(dest);

    printf("\n=== Test result: %s ===\n", test_pass ? "PASS" : "FAIL");
    return test_pass ? 0 : 1;
}