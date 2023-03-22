#ifndef H_CONSOLE
#define H_CONSOLE
typedef enum {
    BLACK=0,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GRAY,
    DARK_GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    WHITE
} VGA_Color;
void clear_terminal();
void print_character(char c);
void print_string(char* str);
void print_line(char* str);
void print_character_with_color(char c, VGA_Color background, VGA_Color font);
#endif