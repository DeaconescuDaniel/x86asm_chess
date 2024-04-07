#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 512

int main() {
    // Open the input file for reading
    FILE *input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("Failed to open input file!\n");
        return 1;
    }
    
    // Open the output file for writing
    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Failed to open output file!\n");
        return 1;
    }
    
    // Read the input file line by line
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        int line_length = strlen(line);
        
        // If the line is shorter than 2 characters, just write it to the output file as-is
        if (line_length < 2) {
            fprintf(output_file, "\t%s,", line);
        }
        // Otherwise, split the line in half and write each half on a separate line in the output file
        else {
            int half_length = (line_length + 1) / 2;
            char first_half[half_length];
            char second_half[half_length];
            strncpy(first_half, line, half_length);
            strncpy(second_half, line + half_length, half_length);
            fprintf(output_file, "\tDD %s \n\tDD %s", first_half, second_half);
        }
    }
    
    // Close the input and output files
    fclose(input_file);
    fclose(output_file);
    
    return 0;
}
