#include <stdio.h>
#include <string.h> // Required for memcpy

int main() {
    char small_buffer[10]; // A buffer of size 10 bytes
	int adjacent_variable = 12345;
    char large_string[] = "This is a very long string that will overflow the buffer.";
	
	printf("Value of adjacent_variable: %d\n", adjacent_variable);

    printf("Attempting to copy a large string into a small buffer...\n");

    // This memcpy call will cause memory corruption
    // because strlen(large_string) + 1 (for null terminator)
    // is greater than sizeof(small_buffer).
    memcpy(small_buffer, large_string, strlen(large_string) + 1);

    printf("Copy operation completed (potentially with corruption).\n");
    // Accessing small_buffer after the overflow might lead to undefined behavior
    // or a crash, depending on what memory was overwritten.
    printf("Content of small_buffer: %s\n", small_buffer); 

    // To observe potential effects, you might declare another variable
    // near small_buffer and see if its value changes unexpectedly.
    // int adjacent_variable = 12345;
    printf("Value of adjacent_variable: %d\n", adjacent_variable);

    return 0;
}