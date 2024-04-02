#ifndef PALINDROME_H
#define PALINDROME_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#define EXIT_NO_INPUT 2
#define EXIT_INVALID_INPUT 3
#define MAX_BUFFER_SIZE 512
#define LOWER_CASE_A 97
#define LOWER_CASE_Z 122

enum end_of_line_char {
    periord,
    exclamation_mark,
    question_mark,
};

extern unsigned int verify_files_exist_and_readable(int, char **);
extern const char *check_palindrome(char*);

#endif
