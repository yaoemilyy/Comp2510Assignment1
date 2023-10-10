#include <stdio.h>

// update this with your A number
char a_num[] = "A01350336";
char a_num1[] = "A01069532";


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void justifyLine(const char *line, int lineLength) {
   
    int len = strlen(line);

    if (len > lineLength) { 
        printError("Error. The word processor can't display the output.");
    } else if (len == lineLength) {
        printf("%s\n", line);
    } else {
        // check how much spaces need to be added 
    }



}








int main(int argc, char *argv[]) {
    // Check for the correct number of command-line arguments
    if (argc != 3) {
        printError("Usage: <executable> <lineLength> <inputFile>");
    }

    int lineLength = atoi(argv[1]);
    char *inputFileName = argv[2];

    // Open the input file
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printError("Error opening input file");
    }

    char line[1024];

    // Read and justify each line from the input file
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        // Remove the trailing newline character
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        justifyLine(line, lineLength);
    }

    // Close the input file
    fclose(inputFile);

    return 0;
}