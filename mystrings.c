#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*The mystrings program 
should take a filename from the command line 
and read the bytes of the file, looking for 
strings of printable characters 
(ASCII values between 32 and 126 decimal).
 A string is a run of at least 4 consecutive
  printable characters and ends whenever a 
  non-printable character is encountered. 
   Whenever you find such a string, print it out,
    one per line.

You can check the operation of your 
program via the real strings program, 
and do a man strings to learn about how it works.
 You do not need to support all of the features
  of the real strings program. It has knowledge 
  of executables that makes it print out less
   strings than your program will. 
    You do should not do anything
     special based upon the file
      type for your program.

Make sure your program can handle
 strings that are arbitrarily long.
*/
int is_char(int curr){
    //check to see if the byte is a printable char
    return (curr >= 32 && curr <= 126);
}

int is_string(FILE * fp){
    int c;
    int i;
    for (i = 0; i <4; i++){
        c = getc(fp);
        if (c == EOF || !is_char(c)){
            return 0;
        }
    }
    return 1;
}

void print_curr_string(FILE * fp){
    //prints the current string
    int c = getc(fp);
    while (c != EOF && is_char(c)){
        printf("%c\n", c);
        c = getc(fp);
    }
}

int main(int argc, char ** argv){
    //take a filename from the command line

    //open it as bytes
    FILE* fp;
    if ((fp = fopen(argv[1], "rb+")) == NULL) {
        printf("\nFile not found");
        exit(1);
    }
    //scan for printable characters
    int curr;
    int pos;


    while (curr != EOF){
        pos  = ftell(fp);
        curr = getc(fp);
        if (is_char(curr) && is_string(fp)){
            fseek(fp, pos, SEEK_SET);   //reset to curr idx -1 
                                        //after is_string
            //print_curr_string(fp);
            fseek(fp, pos+1, SEEK_SET); //reset to curr idx
                                        //after print_curr_string
        }

    }fclose(fp);
    return 0;
}