#include <stdio.h>

// update this with your A number
char a_num[] = "A01350336";
char a_num1[] = "A01069532";


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void justifyLine(char *line, int lineLength) {
    // Your justifyLine function remains the same
 


    printf("%s\n", line);
}



int main(int argc, char *argv[]) {

    // Check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lineLength> <inputFile>\n", argv[0]);
        return 1;
    }

    int lineLength = atoi(argv[1]);
    char *inputFileName = argv[2];

    FILE *file = fopen(inputFileName, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    char *lines[1000]; // An array of pointers to store lines, assuming up to 1000 lines

    int line_count = 0; // Keep track of the number of lines read

    char buffer[1024]; // Temporary buffer for reading lines


    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Remove the trailing newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (strlen(buffer) > lineLength) {
            fprintf(stderr, "Error. The word processor can't display the output.\n");
            return 1;
        }

        // Allocate memory for the line and copy it
        lines[line_count] = strdup(buffer);
        if (lines[line_count] == NULL) {
            perror("Error allocating memory");
            return 1;
        }

        line_count++;
    }

    fclose(file); // Close the file

    // Now, 'lines' contains all the lines from the file as an array of strings

    // Process and justify each line if needed
    for (int i = 0; i < line_count; i++) {
        // Process or manipulate lines[i] as needed
        justifyLine(lines[i], lineLength);
        free(lines[i]); // Free the memory for each line
    }


    return 0;
    
}
