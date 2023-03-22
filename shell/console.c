/**
 * console.c File
 * Handles Console Functionality
 * 
 * Set the VGA buffer to the address 0xb8000
 * 
 * VGA_BUFFER - This is the name in which we will reference our VGA memory space
 *              0xb8000; - The address that maps to the VGA buffer in memory
 * 
 * If our video memory is dictated to us by VGA_BUFFER then we can place a character
 * into the buffer using it like an array.
 * The base address of the buffer at 0xb8000 refers to the upper left character slot.
 * Therefore if we want to “print” a character to the screen in the upper left,
 * in the first spot, we can do VGA_BUFFER[0] = character;
*/

// Include Headers
#include "console.h"

// VGA Buffer Constants
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define BYTES_PER_CHAR 2
#define VGA_BYTES_PER_ROW (VGA_WIDTH*BYTES_PER_CHAR)
#define VGA_TOTAL_BYTES (VGA_BYTES_PER_ROW*VGA_HEIGHT)
#define DEFAULT_STYLE_BYTE 0x07

// VGA BUGGER Address
char* const VGA_BUFFER = (char*) 0xb8000;

// Terminal/Cursor Position
int terminal_position = 0;

/**
 * get the current index relative to the current line
 * move cursor to the next line and same index
 * then subtract that index to get to the line start
*/
void handle_new_line_character() {
    terminal_position = terminal_position + VGA_BYTES_PER_ROW - (terminal_position % (VGA_BYTES_PER_ROW));
}

/**
 * Handle special characters on print_character
*/
void handle_special_characters(char c) {
    switch(c) {
        case '\n':
            handle_new_line_character();
            break;
        case '\t':
            break;
        case '\r':
            break;
        case '\b':
            break;
        default:
            break;
    }
}

/**
 * Clear all characters from the terminal and reset style to default (0x07)
*/
void clear_terminal() {
	for(int i=0; i < VGA_TOTAL_BYTES; i+=2) {
		VGA_BUFFER[i] = 0;
		VGA_BUFFER[i+2] = DEFAULT_STYLE_BYTE;
	}
}

/**
 * Print a single character to the terminal
 * and set the style to default (0x07)
*/
void print_character(char c){
    // if it's a special character, handle it
    if(c < 32 || c == 127) {
        handle_special_characters(c);
        return;
    }
	VGA_BUFFER[terminal_position++] = c;
	VGA_BUFFER[terminal_position++] = 0x07;
	
}

/**
 * Use the print_character function to print a string to the terminal
*/
void print_string(char* str) {
    for(int i=0; str[i] != '\0'; i++) {
        print_character(str[i]);
    }
}

/**
 * print a string followed by a new line
*/
void print_line(char* str) {
    print_string(str);
    print_character('\n');
}

/** print character with a background color and a font color*/
void print_character_with_color(char c, VGA_Color background, VGA_Color font) {
    // if it's a special character, handle it
    if(c < 32 || c == 127) {
        handle_special_characters(c);
        return;
    }
    // Take the background color and shift it 4 bits to the left
    // Then OR it with the font color
    // This will give us the color byte
    char color_byte = (background << 4) | font;
    // print the character
    VGA_BUFFER[terminal_position++] = c;
    VGA_BUFFER[terminal_position++] = color_byte;
}