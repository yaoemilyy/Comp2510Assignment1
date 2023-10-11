#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void insertSpaces(char *line, int line_len, int total_len) {
    int word_count = 0;
    char *word = line;
    while (*word != '\0') {
        if (*word == ' ') {
            word_count++;
            word++;
        } else {
            word++;
        }
    }

    if (word_count == 0) {
        // Center a single word
        int total_spaces = total_len - line_len;
        int spaces_before = total_spaces / 2;
        int spaces_after = total_spaces - spaces_before;

        for (int i = 0; i < spaces_before; i++) {
            printf(" ");
        }
        printf("%s", line);
        for (int i = 0; i < spaces_after; i++) {
            printf(" ");
        }
        printf("\n");
        return;
    }

    int spaces_to_insert = total_len - line_len + word_count - 1;
    int spaces_before_word = spaces_to_insert / word_count;
    int extra_spaces = spaces_to_insert % word_count;

    int word_started = 0;
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] != ' ') {
            if (word_started) {
                if (extra_spaces > 0) {
                    printf(" ");
                    extra_spaces--;
                }
                for (int j = 0; j < spaces_before_word; j++) {
                    printf(" ");
                }
            }
            word_started = 1;
            printf("%c", line[i]);
        } else {
            printf(" ");
            word_started = 0;
        }
    }

    printf("\n");
}



void justifyLine(const char *line, int lineLength) {
    int len = strlen(line);

    if (len > lineLength) {
        fprintf(stderr, "Error. The word processor can't display the output.\n");
    } else if (len == lineLength) {
        printf("%s\n", line);
    } else {
        insertSpaces(line, len, lineLength);
    }
}




int main(int argc, char *argv[]) {

   // Check for the correct number of command-line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <lineLength> <inputFile>\n", argv[0]);
        return 1;
    }

    int lineLength = atoi(argv[1]);
    if (lineLength <= 0) {
        fprintf(stderr, "Error. The word processor can't display the output.\n");
        return 1;
    }

    char *inputFileName = argv[2];

    // Open the input file
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file\n");
        return 1;
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
