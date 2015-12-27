// Written By: Christina Tkatchenko
// Project 3
// Text Manipipulation 

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main(int argc, char** argv) {
    if (argc < 3 || argc > 4) { //putting errors on the arguments, if they are not stated in the command window
        printf("Error, see usage\n");
        printf("./filter <from> <to> <file>\n");
        printf("<from> - mandatory parameter on what text to replace\n");
        printf("<to> - optional paramter on what to replace the <from> to\n");
        printf("<file> - mandatory parameter to read from file\n");
        return 1;
    }

    char from[1024]; //declaring the list of characters to hold in one line, this is the from string
    strcpy(from, argv[1]);
    char to[1024] = ""; //declaring the list of characters to hold in one line, this is the to string

    FILE *stdin; //file pointer used here to store the composite information about the file that we will manipulate
    if (argc == 3) {
        stdin = fopen(argv[2], "r");
    } else {
        strcpy(to, argv[2]);
        stdin = fopen(argv[3], "r");
    }

    char buffer[1024]; //declaring the list of characters to hold in one line
    char out[1024]; //declaring the list of characters to hold in one line
    while (fgets(buffer, sizeof(buffer), stdin)) { //loop which will read the next line from the standard input
        out[0] = '\0';
        if (strlen(buffer) < strlen(from)) { //if length of 'buffer' string is less than the length of 'from' string
            strcpy(out, buffer); //coping the string
            printf("%s", out);
            continue;
        }
        int loopbuffer, last; 
        last = 0;
        for (loopbuffer = 0; loopbuffer < strlen(buffer) - strlen(from); loopbuffer++) { 
            if (strlen(out) >= 1024) break; //breaks if the length of 'out' string is greater or equal to 1024
            if (strncmp(from, buffer + loopbuffer, strlen(from)) == 0) {
                if (strlen(out) + (loopbuffer - last) >= 1024) {
                    strncat(out, buffer + last, loopbuffer - last - (1023 - strlen(out)));
                } else {
                    strncat(out, buffer + last, loopbuffer - last);
                }
                if (strlen(to) > 0 && strlen(out) < 1024) {
                    if (strlen(out) + strlen(to) > 1024) {
                        strncat(out, to, 1023 - strlen(out));
                    } else {
                        strcat(out, to);
                    }
                }
                last = loopbuffer + strlen(from);
            }
        }
        strcat(out, buffer + last); //The 'buffer + last' string is stored in the 'out' string 
        printf("%s\n", out); //The final text is printed in terminal
    }
    return 0;
}
