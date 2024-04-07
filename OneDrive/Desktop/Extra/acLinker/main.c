#include <stdio.h>
#include "tokens.h"
#include <string.h>
#include <stdbool.h>

void binary_convert(uint32_t num, char *binary_string) {
    for (int i = 31; i >= 0; i--) {
        binary_string[31 - i] = ((num >> i) & 1) ? '1' : '0';
    }
    binary_string[32] = '\0';
}

int parseInputFile(const char *infile, const char *outFile, bool vhdl) {
    int line = 0;
    uint32_t currop = 0;
    FILE *fd = fopen(infile, "r");
    if (fd == NULL) {
        printf("Error reading file");
        return -2;
    }
    char buffer[256];
    char programBuffer[4096];
    char linebuffer[33];
    while (fgets(buffer, sizeof(buffer), fd) != NULL) {
        line++;
        TOK token;
        if ((token = findFirstToken(buffer)) == -1) {
            printf("Syntax error at line %d", line);
            fclose(fd);
            return -1;
        }
        currop = parseOperation(token, buffer);
        if (currop == -1) {
            printf("Syntax error at line %d", line);
            fclose(fd);
            return -1;
        } else {
            binary_convert(currop, linebuffer);
            if (vhdl) {
                snprintf(programBuffer + 36 * (line - 1), 38, "\"%s\",\n", linebuffer);
            } else {
                snprintf(programBuffer + 33 * (line - 1), 35, "%s\n", linebuffer);
            }
        }
    }
    FILE *fd2 = fopen(outFile, "w");
    if (vhdl) {
        fwrite(programBuffer, sizeof(char), line * sizeof(char) * 36, fd2);
    } else {
        fwrite(programBuffer, sizeof(char), line * sizeof(char) * 33, fd2);
    }
    fclose(fd);
    fclose(fd2);
    return 0;
}


int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: .\\acLinker.exe filename.txt filenameout [-v, --vhdl]");
        return -1;
    }
    bool vhdl = false;
    char *fileIn = NULL;
    char *fileOut = NULL;
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-v", 2) == 0 || strncmp(argv[i], "--vhdl", 6) == 0) {
            vhdl = true;
        } else if (fileIn == NULL) {
            fileIn=argv[i];
        } else if (fileOut == NULL) {
            fileOut=argv[i];
        }else{
            printf("Usage: .\\acLinker.exe filename.txt filenameout [-v, --vhdl]");
            return -1;
        }
    }
    parseInputFile(fileIn, fileOut, vhdl);
    return 0;
}
