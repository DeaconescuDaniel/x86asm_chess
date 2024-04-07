#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 512

int main() {
    FILE *input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("Failed to open input file!\n");
        return 1;
    }
    
    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Failed to open output file!\n");
        return 1;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, input_file) != NULL) {
        int line_length = strlen(line);
        
        if (line_length < 2) {
            fprintf(output_file, "\t%s,", line);
        }
        else {
            int half_length = (line_length + 1) / 2;
            char first_half[half_length];
            char second_half[half_length];
            strncpy(first_half, line, half_length);
            strncpy(second_half, line + half_length, half_length);
            fprintf(output_file, "\tDD %s \n\tDD %s", first_half, second_half);
        }
    }
    
    fclose(input_file);
    fclose(output_file);
    
    return 0;
}
