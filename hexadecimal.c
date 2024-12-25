#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations
void fetchBinaryFromFile(char *filename, char *binaryData);
void binaryToHexConverter(char *binaryData, char *hexResult);

int main() {
    char binaryData[100];  // Buffer to hold binary input from file
    char hexResult[100];   // Buffer to store the resulting hexadecimal value

    // Step 1: Fetch the binary input from a file
    fetchBinaryFromFile("binary.txt", binaryData);

    // Step 2: Convert the binary data to hexadecimal
    binaryToHexConverter(binaryData, hexResult);

    // Step 3: Output the hexadecimal result
    printf("Hexadecimal: %s\n", hexResult);

    return 0;
}

// Function to read binary input from a file
void fetchBinaryFromFile(char *filename, char *binaryData) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open the file!\n");
        exit(1);
    }
    fgets(binaryData, 100, file);
    fclose(file);
}

// Function to convert binary input to hexadecimal without adding leading zeros
void binaryToHexConverter(char *binaryData, char *hexResult) {
    int length = strlen(binaryData);
    int hexPos = 0;

    // Trim any newline character at the end of the binary string
    if (binaryData[length - 1] == '\n') {
        binaryData[--length] = '\0';  // Reduce length to ignore the newline
    }

    // Start index for processing groups of four
    int start = (length % 4 == 0) ? 4 : length % 4;
    int i = 0;

    // Process the initial group if it's less than 4 bits
    if (start > 0) {
        int decimalValue = 0;
        for (i = 0; i < start; i++) {
            decimalValue = decimalValue * 2 + (binaryData[i] - '0');
        }
        hexResult[hexPos++] = (decimalValue < 10) ? ('0' + decimalValue) : ('A' + decimalValue - 10);
    }

    // Process remaining groups of 4 bits
    for (; i < length; i += 4) {
        int decimalValue = 0;
        for (int j = 0; j < 4; j++) {
            decimalValue = decimalValue * 2 + (binaryData[i + j] - '0');
        }
        hexResult[hexPos++] = (decimalValue < 10) ? ('0' + decimalValue) : ('A' + decimalValue - 10);
    }

    // Null-terminate the hexadecimal result string
    hexResult[hexPos] = '\0';
}