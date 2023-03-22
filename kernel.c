// Include Headers
#include "console.h"

void main(void) {
    clear_terminal();
    // for each possible font and background color
    // print a character with that color
    // on a new background print new line
    for(int i=0; i < 16; i++) {
        for(int j=0; j < 16; j++) {
            print_character_with_color('A', i, j);
        }
        print_line("");
    }
}
