/*
 * Test Driver to test verifyMIPSInstruction and binToDec.
 *
 * This program reads lines from a file.  For each line, the program
 *      calls verifyMIPSInstruction.  If the line contains a valid
 *      MIPS instruction, the program calls binToDec for various
 *      segments of the instruction to test the binToDec function.
 *
 * Input:
 *      The program reads its input from a file called "testpp1.txt".
 *      To test verifyMIPSInstruction, the file should contain ...
 *
 *              The text file should contain a list of characters that will
 * be tested for MIPS validity.  Each line will represent an instruction. In
 * order for a line to be read correctly there must be a line break at the end
 * of this line.  An example of the code used for this specific test example is
 * shown below.
 *
 *  10110101011011010101101101010110
 *  101101010110110101011011010101101
 *  1011010101101101010110110101
 *  1011010101101101010110110101011
 *  afjsd101011011010101101101010110
 *
 *
 * Output:
 *      For each valid line, the program prints a series of decimal
 *      numbers to test binToDec.
 *
 *      For each invalid line, the program prints an error message to
 *      stderr saying so.  (The program also prints an error message if
 *      it cannot open the file.)
 *
 * Author: Giancarlo Anemone, Caitlin Braun
 *        with assistance from: Will G.
 *
 * Creation Date:  4/11/2013
 *
 */

/* include files go here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deassembleMIPS.h"

int main()
{
    
    char buffer[BUFSIZ];            // line being read in
    FILE* fptr;                     // file pointer
    char* filename = "binary.txt";  // filename
    int lineNum = 0;                // line number
    // Open the file for reading
    if ((fptr = fopen (filename, "r")) == NULL)
    {
        fprintf (stderr, "Error: Cannot open file %s.\n", filename);
        return 1;
    }    
    /* Continuously read next line of input until EOF is encountered.
     * Each line should contain only 32 characters and newline.
     */
    while (fgets (buffer, BUFSIZ, fptr))   /* fgets returns NULL if EOF */
    {
        lineNum++;
        // checks to see if the line has 32 characters
        if (strlen (buffer) == 33 && buffer[32] == '\n')
            buffer[32] = '\0';        /* convert newline to null byte */
        else
        {
            (void) fprintf (stderr, "Error Line%d: Not 32 chars.\n", lineNum);
            continue;                /* error: get next line */
        }
        /* Verify that the string is 32 0's and 1's.  If it is, do
         * various tests to ensure that binToDec works correctly.
         * If the string contains invalid characters, print an error
         * message.
         */
        if(verifyMIPSInstruction(buffer)==1)
        {
           (void)PrintInstruction(buffer, lineNum);
        }
        else
        {
            (void) fprintf (stderr, "Error Line %d: Not a valid MIPS instruction Code\n", lineNum);
            continue;                /* error: get next line */
        }
    }
    
    
    
    /* End-of-file encountered; close the file. */
    fclose (fptr);
    return 0;
}
