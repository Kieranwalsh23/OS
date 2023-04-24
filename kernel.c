// Include Headers
#include "console.h"
#include "keyboard.h"
#include "strcmp.h"

/**
 * Welcome message to show when the OS starts
*/
char* welcome_msg = "Welcome to the OS!\nType 'help' to see a list of commands.";
/**
 * Help message to show what the user can do
*/
char* help_msg = "Possible commands:\nhelp - Displays this message\nclear - Clears the screen\nset-terminal-font-color - Sets Font Color\nexit - Exits the OS";
/**
 * Used to keep the OS running, when set to 0, the OS will exit (No more keyboard input)
*/
int running = 1;
/**
 * Symbol to show the user that they can type
*/
char* command_prompt = "~> ";
/**
 * Used to store command input
*/
char* command_buffer = "";

void handle_font_color_choice() {
    // Check if color or color number is contained in the command_buffer
    if(str_contains(command_buffer, "black") || str_contains(command_buffer, "0")) {
        change_default_font_color(BLACK);
    }
    else if(str_contains(command_buffer, "blue") || str_contains(command_buffer, "1")) {
        change_default_font_color(BLUE);
    }
    else if(str_contains(command_buffer, "green") || str_contains(command_buffer, "2")) {
        change_default_font_color(GREEN);
    }
    else if(str_contains(command_buffer, "cyan") || str_contains(command_buffer, "3")) {
        change_default_font_color(CYAN);
    }
    else if(str_contains(command_buffer, "red") || str_contains(command_buffer, "4")) {
        change_default_font_color(RED);
    }
    else if(str_contains(command_buffer, "magenta") || str_contains(command_buffer, "5")) {
        change_default_font_color(MAGENTA);
    }
    else if(str_contains(command_buffer, "brown") || str_contains(command_buffer, "6")) {
        change_default_font_color(BROWN);
    }
    else if(str_contains(command_buffer, "light gray") || str_contains(command_buffer, "7")) {
        change_default_font_color(LIGHT_GRAY);
    }
    else if(str_contains(command_buffer, "dark gray") || str_contains(command_buffer, "8")) {
        change_default_font_color(DARK_GRAY);
    }
    else if(str_contains(command_buffer, "light blue") || str_contains(command_buffer, "9")) {
        change_default_font_color(LIGHT_BLUE);
    }
    else if(str_contains(command_buffer, "light green") || str_contains(command_buffer, "10")) {
        change_default_font_color(LIGHT_GREEN);
    }
    else if(str_contains(command_buffer, "light cyan") || str_contains(command_buffer, "11")) {
        change_default_font_color(LIGHT_CYAN);
    }
    else if(str_contains(command_buffer, "light red") || str_contains(command_buffer, "12")) {
        change_default_font_color(LIGHT_RED);
    }
    else if(str_contains(command_buffer, "light magenta") || str_contains(command_buffer, "13")) {
        change_default_font_color(LIGHT_MAGENTA);
    }
    else if(str_contains(command_buffer, "yellow") || str_contains(command_buffer, "14")) {
        change_default_font_color(YELLOW);
    }
    else if(str_contains(command_buffer, "white") || str_contains(command_buffer, "15")) {
        change_default_font_color(WHITE);
    }
    else {
        print_line("Invalid color!");
    }
}

/**
 * Handle Command based on the command string
*/
void handle_command() {
    // If the command is 'help', print the help message
    if (strcmp(command_buffer, "help") == 0) {
        print_line(help_msg);
    }
    // If the command is 'clear', clear the screen
    else if (strcmp(command_buffer, "clear") == 0) {
        clear_terminal();
    }
    // If the command is 'exit', exit the OS
    else if (strcmp(command_buffer, "exit") == 0) {
        print_line("Exiting OS...");
        running = 0;
        return;
    }
    // set the terminal font color to the color specified
    else if(str_contains(command_buffer, "set-terminal-font-color")) {
        handle_font_color_choice();
    }
    // else command not found error
    else {
        print_string("Command not found: ");
        print_line(command_buffer);
    }
    //clear data from command buffer
    clear_string(command_buffer);
    // Print the command prompt for next command
    print_character('\n');
    print_string(command_prompt);
}

/**
 * Read the keyboard for input and handle the command when a carriage return is pressed
*/
void read_command() {
    unsigned char byte;
    // while loop to scan keyboard for input
    while ((byte = scan())) {
        // If the byte is a carriage return, execute the command
        if (charmap[byte] == '\n') {
            // print new line
            print_character(charmap[byte]);
            // Handle the command
            handle_command(command_buffer);
        }
        // If the byte is not a carriage return, append it to the buffer
        else {
            // Append the byte to the buffer
            command_buffer = append_char(command_buffer, charmap[byte]);
            // Print the byte to the screen
            print_character(charmap[byte]);
        }
    }
}



/**
 * Main function
*/
void main(void) {
    // Clear Terminal
	clear_terminal();
    // Set the default font color to cyan (Because I like cyan and you can't stop me)
    change_default_font_color(CYAN);
    // Print Welcome and prompt
    print_line(welcome_msg);
    print_string(command_prompt);
    // Read commands until the OS is exited
    while (running) {
        read_command();
    }
}
