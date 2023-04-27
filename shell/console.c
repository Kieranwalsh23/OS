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
#include "stdint.h"
#include "portmap.h"

// VGA Buffer Constants
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define BYTES_PER_CHAR 2
#define VGA_BYTES_PER_ROW (VGA_WIDTH*BYTES_PER_CHAR)
#define VGA_TOTAL_BYTES (VGA_BYTES_PER_ROW*VGA_HEIGHT)
// Default Style Byte
char DEFAULT_STYLE_BYTE =  0x07;
VGA_Color DEFAULT_FONT_COLOR = 0x07;
VGA_Color DEFAULT_BACKGROUND_COLOR = 0x00;
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
    // set cursor position to 0
    terminal_position = 0;
    // update the cursor on screen
    update_cursor();
}

/**
 * Print a single character to the terminal
 * and set the style to default (0x07)
*/
void print_character(char c){
    // check if we are at the end of the screen
    if(terminal_position >= VGA_TOTAL_BYTES) {
        shift_terminal_up();
    }
    // if it's a special character, handle it
    if(c < 32 || c == 127) {
        handle_special_characters(c);
        update_cursor();
        return;
    }
	VGA_BUFFER[terminal_position++] = c;
	VGA_BUFFER[terminal_position++] = DEFAULT_STYLE_BYTE;
    update_cursor();
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
        update_cursor();
        return;
    }
    // Take the background color and shift it 4 bits to the left
    // Then OR it with the font color
    // This will give us the color byte
    char color_byte = (background << 4) | font;
    // print the character
    VGA_BUFFER[terminal_position++] = c;
    VGA_BUFFER[terminal_position++] = color_byte;
    update_cursor();
}

/**
 * What we want to do is to take the current position,
 * translate it into two 8-bit binary numbers,
 * and write those binary numbers at the appropriate high and low control registers.
 * Note that the position is in the 80x25 grid and does NOT take into account the style byte.
 * Therefore, the position we want to write is terminal_position >> 1.
*/
void update_cursor() {
    uint16_t cursor_position = terminal_position >> 1;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(cursor_position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((cursor_position >> 8) & 0xFF));
}

/**
 * Get the current cursor position
*/
uint16_t get_cursor_position() {
	uint16_t cursor_position = 0;
	outb(0x3D4, 0x0F);
	cursor_position |= inb(0x3D5);
	outb(0x3D4, 0x0E);
	cursor_position |= ((uint16_t)inb(0x3D5)) << 8;
	return cursor_position;
}

/**
 * Convert int to string, print string
*/
void print_int(int num) {
    char str[12];
    itoa(num, str, 10);
    print_string(str);
}

/**
 * Implement itoa function as a helper function for: print_int(int num)
*/
void itoa(int num, char* str, int base) {
    // Handle 0 explicitely, otherwise empty string is printed for 0
    int i = 0;
    int isNegative = 0;
    // Process individual digits
    if(num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }
    // if the number is negative, make it positive and set the isNegative flag
    if(num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }
    // Process individual digits
    while(num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem-10) + 'a' : rem + '0';
        num = num / base;
    }
    // If number is negative, append '-'
    if(isNegative) {
        str[i++] = '-';
    }
    // Append string terminator
    str[i] = '\0';
    // reverse the string
    reverse(str, i);
}

/**
 * return string in reverse order
*/
void reverse(char* str, int length) {
    // start from two corners
    int start = 0;
    // end index of the string
    int end = length - 1;
    // swap characters starting from two corners
    while(start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

/**
 * Change the default font color
*/
void change_default_font_color(VGA_Color color) {
    // set the new default font color
    DEFAULT_FONT_COLOR = color;
    DEFAULT_STYLE_BYTE = (DEFAULT_BACKGROUND_COLOR << 4) | DEFAULT_FONT_COLOR;
}

/**
 * Change the default background color
*/
void change_default_background_color(VGA_Color color) {
    // set the new default background color
    DEFAULT_BACKGROUND_COLOR = color;
    DEFAULT_STYLE_BYTE = (DEFAULT_BACKGROUND_COLOR << 4) | DEFAULT_FONT_COLOR;
}

/**
 * Shift terminal up one line
*/
void shift_terminal_up() {
    // copy the contents of the VGA buffer up one line
    for(int i=0; i < VGA_TOTAL_BYTES - VGA_BYTES_PER_ROW; i++) {
        VGA_BUFFER[i] = VGA_BUFFER[i+VGA_BYTES_PER_ROW];
    }
    // clear the last line
    for(int i=VGA_TOTAL_BYTES - VGA_BYTES_PER_ROW; i < VGA_TOTAL_BYTES; i++) {
        VGA_BUFFER[i] = 0;
    }
    // set the terminal position to the start of the last line
    terminal_position = VGA_TOTAL_BYTES - VGA_BYTES_PER_ROW;
    // update the cursor
    update_cursor();
}

