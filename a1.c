#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void justifyLine(const char *line, int lineLength) {
   
    int len = strlen(line);

    if (len > lineLength) { 
        printError("Error. The word `processor can't display the output.");
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

    int lineLength = atoi(argv[2]);
    char *inputFileName = argv[3];

    // Open the input file
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printError("Error opening input file");
    }

    char line[1024]; // Might Change

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

    // A numbers of everyone. AXXXX_AXXXX_AXXXX format. 
    // Accordance to D2L Provided Snippet
    char *ANum = "A01069532_A01350336";

    FILE *outputFile = fopen(ANum, "w");

    if (outputFile == NULL) {
         printf("Failed to create the output file.\n");
         return 1;
    }

    fclose(outputFile);
    
    return 0;
}
