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

void handle_font_color_choice(char* color) {
    // Do a string compare to see if the color is valid,
    // then get the color code and set the font color
    if (strcmp(color, "0") == 0 || strcmp(color, "black") == 0) {
        change_default_font_color(BLACK);
    }
    else if (strcmp(color, "1") == 0 || strcmp(color, "blue") == 0) {
        change_default_font_color(BLUE);
    }
    else if (strcmp(color, "2") == 0 || strcmp(color, "green") == 0) {
        change_default_font_color(GREEN);
    }
    else if (strcmp(color, "3") == 0 || strcmp(color, "cyan") == 0) {
        change_default_font_color(CYAN);
    }
    else if (strcmp(color, "4") == 0 || strcmp(color, "red") == 0) {
        change_default_font_color(RED);
    }
    else if (strcmp(color, "5") == 0 || strcmp(color, "magenta") == 0) {
        change_default_font_color(MAGENTA);
    }
    else if (strcmp(color, "6") == 0 || strcmp(color, "brown") == 0) {
        change_default_font_color(BROWN);
    }
    else if (strcmp(color, "7") == 0 || strcmp(color, "light_gray") == 0) {
        change_default_font_color(LIGHT_GRAY);
    }
    else if (strcmp(color, "8") == 0 || strcmp(color, "dark_gray") == 0) {
        change_default_font_color(DARK_GRAY);
    }
    else if (strcmp(color, "9") == 0 || strcmp(color, "light_blue") == 0) {
        change_default_font_color(LIGHT_BLUE);
    }
    else if (strcmp(color, "10") == 0 || strcmp(color, "light_green") == 0) {
        change_default_font_color(LIGHT_GREEN);
    }
    else if (strcmp(color, "11") == 0 || strcmp(color, "light_cyan") == 0) {
        change_default_font_color(LIGHT_CYAN);
    }
    else if (strcmp(color, "12") == 0 || strcmp(color, "light_red") == 0) {
        change_default_font_color(LIGHT_RED);
    }
    else if (strcmp(color, "13") == 0 || strcmp(color, "light_magenta") == 0) {
        change_default_font_color(LIGHT_MAGENTA);
    }
    else if (strcmp(color, "14") == 0 || strcmp(color, "yellow") == 0) {
        change_default_font_color(YELLOW);
    }
    else if (strcmp(color, "15") == 0 || strcmp(color, "white") == 0) {
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
    else if(strcmp(command_buffer, "set-terminal-font-color") == 0) {
        // TODO: Handle font color choice
        // // if args is empty, print a color must be provided
        // if (strcmp(args, "") == 0) {
        //     print_line("A color must be provided!");
        // }
        // else {
        //     handle_font_color_choice(args);
        // }
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
    // Print Welcome and prompt
    print_line(welcome_msg);
    print_string(command_prompt);
    // Read commands until the OS is exited
    while (running) {
        read_command();
    }
}
