#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

   // Check for the correct number of command-line arguments
    if (argc != 3) {
        printf("Usage: %s <lineLength> <inputFile>\n", argv[0]);
        return 1;
    }

    int lineLength = atoi(argv[1]);
    char *inputFileName = argv[2];

    // Error message for line length zero and below
    if (lineLength <= 0) {
        printf("Error. The word processor can't display the output.\n");
        return 1;
    }

    // Open the input file
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Failed to open the input file\n");
        return 1;
    }

    // Reads the amount of characters
    int characterCount = 0;
    int ch;
    while((ch = fgetc(inputFile)) != EOF) {
        if(ch != '\n'){
    	    characterCount++;
	}
    }
    
    rewind(inputFile);

    // Read the file 
    char charArray[characterCount];
    char value;
    int count = 0;
 
    // Stores characters from input into charArray
    while((ch = fgetc(inputFile)) != EOF) {	
        if (ch != '\n') {
            charArray[count] = ch;
            count++;
        }
    }

    // Allocates the array memory
    int rows;

    if(characterCount == lineLength){
        rows = characterCount / lineLength;
    } else {
        rows = characterCount / lineLength + 1; 
    }
    char **arr=(char **)malloc(lineLength * sizeof(char *));
    for(int i = 0; i < lineLength; i++){
        arr[i] = (char *)malloc(rows * sizeof(char));
    }

    int charCountArray[rows][1];

    // Sort charArray into arr
    int placeholder = lineLength;
    int remainSize = lineLength;
    int initializedRow = 0;
    int start = 0;
    while(rows != initializedRow){

	if(characterCount == lineLength){
	    for(int i = 0; i < lineLength; i++){
	        arr[initializedRow][i] = charArray[i];
		charCountArray[0][0] = lineLength;
	    }
	}

        if(charArray[placeholder] == ' ' || charArray[placeholder] == '-' || charArray[placeholder + 1] == ' ' || placeholder == characterCount) {
            //Restore charArray element into arr
	    if(charArray[placeholder] == '-'){
	        for(int i = 0; i <= placeholder - start; i++){
		    arr[initializedRow][i] = charArray[start + i];
		}
	    charCountArray[initializedRow][0] = placeholder + 1 - start;
	    } else {
	        for(int i = 0; i < placeholder - start; i++){
	            arr[initializedRow][i] = charArray[start + i];
	        }
	    charCountArray[initializedRow][0] = placeholder - start;
	    }
	    start = placeholder + 1;  
	    placeholder = placeholder + lineLength + 1;
	    initializedRow++;
	    remainSize = lineLength;
        } else if(charArray[placeholder] != ' ' && remainSize != 0){
	    placeholder--;
	    remainSize--;
        } else if(charArray[placeholder] != ' ' && remainSize == 0){
            printf("Error. The word processor can't display the output.\n");
            return 1;
        }
    }

    // Test array
    for(int i = 0 ; i < rows; i++){
	for(int j = 0; j < lineLength; j++){
	    printf("%c", arr[i][j]);
	}
	printf("\n");
    }

    // Getting Space count and Position
    int spaceArray[rows][lineLength + 1]; // [][0] = # of spaces, [][0<] = position of spaces
    for(int i = 0; i < rows; i++){
	int spaces = 0;
        for(int j = 0; j < lineLength; j++){
	    if(arr[i][j] == ' '){
	        spaces++;
		spaceArray[i][spaces] = j;
	    }
	}
	spaceArray[i][0] = spaces;
    }	

    // Test space array
    for(int i = 0; i < rows; i++){
	int spaces = spaceArray[i][0];
	for(int j = 0; j < spaces + 1; j++){
            printf("spaceArray[%d][%d] = %d\n", i, j, spaceArray[i][j]);
	}
    }

    // Adding spacing to arr
    for(int i = 0; i < rows; i++){
	for(int j = 0; j < lineLength; j++){
	    int difference = lineLength - charCountArray[i][0];
	    int position = 0;
	    int positionCount = 0;
	    int positionOffset = 0;
		if(spaceArray[i][0] == 0){
	            while(charCountArray[i][0] != lineLength){
		    
		        // Shift elements down to make room for the new element
                        for (int k = lineLength; k > 0; k--) {
                            arr[i][k] = arr[i][k - 1];
                        }

		        // Insert the new element at the desired position
                        arr[i][0] = ' ';
		        charCountArray[i][0] = charCountArray[i][0] + 1;
		    }
		} else {
		    for(int k = 0; k < difference; k++){
			if(positionCount == spaceArray[i][0]){
			    positionCount = 1;
			} else {
			    positionCount++;
			}	
			position = spaceArray[i][positionCount];
			printf("position: %d\n", position);
			if(positionCount == 1){
		            for(int l = lineLength; l > position; l--){
			        arr[i][l] = arr[i][l - 1];
				arr[i][position] = ' ';
			    }
			} else {
			    for(int l = lineLength; l > position + positionOffset; l--){
			        arr[i][l] = arr[i][l - 1];
				int temp = positionOffset + 1;
			    	arr[i][position + temp] = ' ';
			    }
			    positionOffset++;
			}
			
		        charCountArray[i][0] = charCountArray[i][0] + 1;
		    }		
		}
	    
	}
    }

    // Testing new array
    for(int i = 0 ; i < rows; i++){
        for(int j = 0; j < lineLength; j++){
            printf("%c", arr[i][j]);
        }
        printf("\n");
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
