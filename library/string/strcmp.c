#include "strcmp.h"
#include "console.h"
/**
 * A simple string library
*/

/**
 * Compares two strings.
 * Returns 0 if they are equal.
 * Returns a negative number if str1 is less than str2.
 * Returns a positive number if str1 is greater than str2.
*/
int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    // Return the difference between the two strings
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

/**
 * 
 * allocate memory for a string
*/
void* malloc(unsigned int size) {
    // Allocate memory
    void* ptr = (void*) 0x100000;
    // Return the pointer
    return ptr;
}

/**
 * Copy a string to another string
*/
void strcpy(char* dest, char* src) {
    // Copy the string
    while (*src) {
        *dest++ = *src++;
    }
    // Add the null terminator
    *dest = '\0';
}

/**
 * get the length of the string
*/
int strlen(char* str) {
    // Get the length of the string
    int len = 0;
    while (*str++) {
        len++;
    }
    // Return the length
    return len;
}

/**
 * Append a character to a string
*/
char* append_char(char* str, char c) {
    // Get the length of the string
    int len = strlen(str);
    // Create a new string with the length of the old string + 1
    char* new_str = malloc(len + 1);
    // Copy the old string to the new string
    strcpy(new_str, str);
    // Append the character to the new string
    new_str[len] = c;
    // Return the new string
    return new_str;
}

/**
 * Clear all memory addresses in string until null terminator
*/
void clear_string(char* str) {
    // Clear the string
    while (*str) {
        *str++ = '\0';
    }
}

/**
 * Find if a string contains a substring
*/
int str_contains(char* str, char* substr) {
    // Find if the string contains the substring
    while (*str) {
        char* str1 = str;
        char* str2 = substr;
        while (*str1 && *str2 && !(*str1 - *str2)) {
            str1++;
            str2++;
        }
        if (!*str2) {
            return 1;
        }
        str++;
    }
    // Return false
    return 0;
}
