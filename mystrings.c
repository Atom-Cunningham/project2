#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Title: mystrings
Author: Adam Cunningham
Class: CSC352
project2, fall 2019

tldr;
Mystrings looks for characters in a file (possibly full of gibberish).
enter the name of the file to parse as an argument when the exe is run

ex: ./mystrings filename.txt

if it finds more than 4 chars in a row, 
it prints out the entire found string on a line

program SPECIFICATIONS:
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

/*takes an integer value.
returns true if that value is a printable ascii
else returns false
*/
int is_char(int curr){
    //check to see if the byte is a printable char
    return (curr >= 32 && curr <= 126);
}

/*takes a file pointer
looks at the next three characters in the file
returns false if any of them are not characters
else returns true
side effect: modifies the cursor
*/
int is_string(FILE * fp){
    int c;
    int i;
    for (i = 0; i <4; i++){
        c = getc(fp);                   //get next char
        if (c == EOF || !is_char(c)){   //return false if invalid char
            return 0;
        }
    }
    return 1;
}

/*takes a file pointer
prints characters starting at the file pointer
until an unprintable character is reached
returns the modified frame pointer
*/
int print_curr_string(FILE * fp){
    //prints the current string
    int c = getc(fp);
    while (c != EOF && is_char(c)){
        printf("%c", c);
        c = getc(fp);
    }
    return ftell(fp);
}

/*gets a file pointer, from cmd arg1
loops through the file looking for chars of len 4 or more
prints them out for the user
the solution involves resetting the frame pointer after looking
ahead for a series of chars
*/
int main(int argc, char ** argv){
    //take a filename from the command line
    //open it as bytes
    FILE* fp;
    if (argc < 2 || (fp = fopen(argv[1], "rb+")) == NULL) {
        printf("\nEnter a valid filename as a second argument\n");
        exit(1);
    }

    int curr;   //current character
    int pos;    //cursor index
    while (curr != EOF){
        pos  = ftell(fp);
        curr = getc(fp);
        if (is_char(curr) && is_string(fp)){
            fseek(fp, pos, SEEK_SET);   //reset to curr idx 
                                        //after is_string
            pos = print_curr_string(fp);
            fseek(fp, pos, SEEK_SET);   //reset to curr idx
            printf("\n");               //after print_curr_string
        }
    }
    fclose(fp);
    return 0;
}
