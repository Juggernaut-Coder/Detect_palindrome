#include "palindrome.h"

unsigned int verify_files_exist_and_readable(int argc, char **argv) {
  /* Returns 0 if all files exists
   * and readable. Otherwise returns
   * number of bad arguments.
   */
  unsigned int ret_val = 0;
  for (int i = 1; i < argc; ++i) {
    if (access(argv[i], F_OK) != 0) {
      ret_val++;
      printf("%s does not exist.\n", argv[i]);
    } else if (access(argv[i], R_OK) != 0) {
      ret_val++;
      printf("%s exists, but you do not have read access.\n", argv[i]);
    }
  }
  return ret_val;
}

const char *check_palindrome(char* buff) {
  /* Copy buff to a local buffer ignoring garbage.
   * Anything but a-z or A-Z is ignored. */
  int i = 0;
  char plaindrome_check_buff[MAX_BUFFER_SIZE] = {};
  while (*buff !='\0') {
    /* Convert everything to lowercase */
    int read_char = tolower(* buff);
    /* Only copy if it satisfies the ascii range below */
    if(read_char>=LOWER_CASE_A && read_char<=LOWER_CASE_Z) {
      plaindrome_check_buff[i++] = (char) read_char;
    }
    *buff++;
  }
  int buff_len = strlen(plaindrome_check_buff);
  /* To check if a string is a palindrome or not, a string needs to be compared with the reverse of itself.  */
  for(i=0;i < buff_len ;i++){
    if(plaindrome_check_buff[i] != plaindrome_check_buff[buff_len-i-1]){
      return "NO";
    }
  }
  return "YES";
}

int main(int argc, char **argv) {
  /* Check if files names are passed as argument strings.
   * If not arguments are passed the program inform the user
   * that the program requires arguments to operate and terminates.
   */
  if (argc == 1) {
    printf("No arguments were passed.\nPlease pass path of files containing "
           "palindrome strings.\n");
    return EXIT_NO_INPUT;
  }
  /* Now we know that arguments were passed.
   * Ensure that all the files exists
   * and can be read. Otherwise terminate.
   */
  unsigned int verification_result =
      verify_files_exist_and_readable(argc, argv);
  if (verification_result != 0) {
    printf("You have entered %u invalid argument(s).\nPlease check the above "
           "error message(s) and re-enter correct argument(s).\n",
           verification_result);
    return EXIT_INVALID_INPUT;
  }
  /*Define characters, which signifies end of a line, in an array */
  int end_of_line_char_arr[] = {'.', '!', '?'};
  /* Open the files sequentially and scan
   * each character. If a end of line character
   * is found the the sentence is consider complete.
   * The program checks if each sentence string
   * each a palindrome. However, the program ignores
   * any character excluding a-z and A-Z
   */
  for (int i = 1; i < argc; ++i) {
    /* Open and print the name of the palindrome string file */
    FILE *panlindrome_str_file = fopen(argv[i], "r");
    assert(panlindrome_str_file != NULL);
    printf("#FILE NAME: %s\n", argv[i]);
    /* Define integer to catch return value of fgetc */
    int read_character;
    /* Define bufffer to store sentences/string */
    char buffer[MAX_BUFFER_SIZE];
	  /* Declare pointer for iteration */
	  char *read_buff = buffer;
    while ((read_character = fgetc(panlindrome_str_file)) != EOF) {
      if (read_character == end_of_line_char_arr[periord] ||
          read_character == end_of_line_char_arr[exclamation_mark] ||
          read_character == end_of_line_char_arr[question_mark]) {
		        /* Store the character that signals the end of a sentence */
            *read_buff++ = (char) read_character;
		        /* End the buffer with a NUL character */
		        *read_buff = '\0';
            /* Check for palindrome */
            const char * palindrome_result = check_palindrome(buffer);
            /* Print result and string */
            printf("%s %s\n",palindrome_result, buffer);
		        /* Reset the pointer */
		        read_buff = buffer;
            /* Restart the loop */
		        continue;
      }
      /* Ignore the first space */
      if (read_buff != buffer || read_character != (int)' ') {
        /* Replace line feed with a space if read_buff > buffer */
        if( read_buff > buffer && read_character == (int)'\n') {
          *read_buff++ = ' ';
        /* Ignore line feed otherwise */  
        } else if (read_character !=(int)'\n') {
          *read_buff++ = (char) read_character;
        }
      }
      
    }
    /* Close the palindrome string file */
    int fclose_res = fclose(panlindrome_str_file);
    assert(fclose_res == 0);
  }
  /* Stop screen from disappearing until you press any character */
  getchar();
  return EXIT_SUCCESS;
}
