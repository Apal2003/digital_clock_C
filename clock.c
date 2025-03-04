/*Digital Clock*/
#include <stdio.h>      // Includes standard input/output library for printf and scanf
#include <stdlib.h>     // Includes standard library for system calls like system() 
#include <time.h>       // Includes time library for manipulating and formatting time
#include <unistd.h>     // Includes unistd library for the sleep() function

// Function declarations
void fill_time(char*,int);     // Function to fill the time in the given format
void fill_date(char*);         // Function to fill the current date in the buffer
int input_format();            // Function to ask user for the time format choice
void clear_screen();           // Function to clear the screen based on OS

int main()
{
    // Declare variables
    char time[50], date[100];    // Array to store formatted time and date as strings
    int format = input_format(); // Get the time format from the user (24 or 12-hour)

    // Infinite loop to keep updating the time and date
    while(1){
        fill_time(time, format);   // Fill the time in the given format
        fill_date(date);           // Fill the current date
        clear_screen();            // Clear the terminal screen for fresh output
        printf("Current Time: %s\n", time);   // Print the current time
        printf("Date: %s\n", date);           // Print the current date
        sleep(1);                   // Sleep for 1 second to update the time every second
    }
    return 0;  // Return 0 to indicate successful completion (never reached due to infinite loop)
}

// Function to clear the terminal screen
void clear_screen()
{
    #ifdef _WIN32                  // If compiling on Windows, use the "cls" command
        system("cls");
    #else                           // Else (for Unix-based systems like Linux and macOS), use "clear"
        system("clear");
    #endif   
}

// Function to ask the user for time format (12-hour or 24-hour)
int input_format()
{
    int format;                    // Variable to store the chosen time format
    printf("\n Choose the time format: ");
    printf("\n 1. 24 Hours format");
    printf("\n 2. 12 Hours format [Default]"); // Default is 12-hour format
    printf("\n Make a Choice(1/2):");
    scanf("%d", &format);           // Get user input for time format (1 for 24-hour, 2 for 12-hour)
    return format;                  // Return the chosen format to the main function
}

// Function to fill the current date into the buffer
void fill_date(char* buffer)
{
    time_t raw_time;              // Declare a variable to store the raw current time
    struct tm *current_time;      // Declare a pointer to store the formatted current time

    time(&raw_time);              // Get the current raw time (seconds since the epoch)
    current_time = localtime(&raw_time); // Convert raw time to structured local time
    strftime(buffer, 100, "%A %B %d %Y", current_time);  // Format and store the date in the buffer
}

// Function to fill the current time into the buffer based on the chosen format
void fill_time(char* buffer, int format)
{
    time_t raw_time;              // Declare a variable to store the raw current time
    struct tm *current_time;      // Declare a pointer to store the formatted current time

    time(&raw_time);              // Get the current raw time (seconds since the epoch)
    current_time = localtime(&raw_time); // Convert raw time to structured local time

    if (format == 1) {            // If format is 1 (24-hour format)
        strftime(buffer, 50, "%H:%M:%S", current_time);  // Format time as HH:MM:SS
    }
    else {                        // If format is 2 (12-hour format)
        strftime(buffer, 50, "%I:%M:%S %p", current_time); // Format time as HH:MM:SS AM/PM
    }
}

