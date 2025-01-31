#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Maximum length for a word
#define LENGTH 45
// Maximum length for a front of a word
#define N 2

// Copy N characters from src to dest at most(maybe less than 3)
char* strcpy_mostN(char *dest, const char *src);
// compare 3 characters between s and cmp(the length of s <= 3)
bool strcmp_mostN(const char *s, const char *cmp);

int main(int argc, char *argv[])
{
    // Check for correct number of args
    if (argc != 3)
    {
        printf("Usage: ./letter infile outfile\n");
        return 1;
    }

    // Open infile
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Cound not open %s.", argv[1]);
        return 1;
    }

    // Open outfile
    FILE *outfile = fopen(argv[2], "w");
    if (outfile == NULL)
    {
        printf("Cound not open %s.", argv[2]);
    }

    // Store word plus '\n' & '\0'
    char *buffer = malloc(LENGTH + 2);
    // Record order
    int num = 1;
    // record the count of words with same front
    int count = 0;
    // Store front of word
    char *front = malloc(4);

    while (fgets(buffer, LENGTH + 2, infile))
    {
        // Remove '\n'
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            // Add '\0' at the end
            buffer[strlen(buffer) - 1] = '\0';
        }

        // First word
        if (num == 1)
        {
            fprintf(outfile, "%06i", num);
            strcpy_mostN(front, buffer);
            count++;
        }
        // The front of new word don't change
        else if (strcmp_mostN(front, buffer))
        {
            count++;
        }
        // The front of new word don't change
        else
        {
            fprintf(outfile, "~%06i   ", num);
            fprintf(outfile, "%s: %i\n", front, count);

            fprintf(outfile, "%06i", num + 1);
            strcpy_mostN(front, buffer);
            count = 1;
        }
        num++;
    }
    // Print infromation for the count with last front
    fprintf(outfile, "~%06i   ", num);
    fprintf(outfile, "%s: %i\n", front, count);

    // Free momory
    free(buffer);
    free(front);

    // Close the opened files
    fclose(infile);
    fclose(outfile);

    return 0;
}

char *strcpy_mostN(char *dest, const char *src)
{
    int i;
    for (i = 0; i < N && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';

    return dest;
}

bool strcmp_mostN(const char *s, const char *cmp)
{
    for (int i = 0; i < N; i++)
    {
        if (s[i] != cmp[i])
        {
            return false;
        }
    }

    return true;
}
