/*
********************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2024
* Author: TO_DO
* Professors: Paulo Sousa
********************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F24)  |"
# ECHO "=---------------------------------------="
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@           %&@@@@@@@@@@@     @@    ”
# ECHO "    @@       @%% (@@@@@@@@@  @     @@    ”
# ECHO "    @@      @& @   @ @       @     @@    ”
# ECHO "    @@     @ @ %  / /   @@@@@@     @@    ”
# ECHO "    @@      & @ @  @@              @@    ”
# ECHO "    @@       @/ @*@ @ @   @        @@    ”
# ECHO "    @@           @@@@  @@ @ @      @@    ”
# ECHO "    @@            /@@    @@@ @     @@    ”
# ECHO "    @@     @      / /     @@ @     @@    ”
# ECHO "    @@     @ @@   /@/   @@@ @      @@    ”
# ECHO "    @@     @@@@@@@@@@@@@@@         @@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@         S O F I A           @@    ”
# ECHO "    @@                             @@    ”
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    ”
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
*********************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
********************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * - Please check the "TODO" labels to develop your activity.
 * - Review the functions to use "Defensive Programming".
 *.............................................................................
 */

#include <ctype.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 *********************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Svillen Ranev / Paulo Sousa
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to inicial (default) values.
 * TODO ......................................................
 *	- Adjust datatypes for your LANGUAGE.
 *   - Use defensive programming
 *	- Check boundary conditions
 *	- Check flags.
 *********************
 */

BufferPointer readerCreate(cjs_intg size, cjs_intg increment, cjs_char mode) {
	BufferPointer readerPointer;
	cjs_intg count = 0;
	/* TO_DO: Defensive programming */
	if (!size)
		size = READER_DEFAULT_SIZE;
	if (!increment)
		increment = READER_DEFAULT_INCREMENT;
	if (!mode)
		mode = MODE_FIXED;
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!readerPointer)
		return CJS_INVALID;
	readerPointer->content = (cjs_string)malloc(size);
	/* TO_DO: Defensive programming */
	/* TO_DO: Initialize the histogram */
	/* TO_DO: Initialize errors */
	readerPointer->mode = mode;
	readerPointer->size = size;
	readerPointer->increment = increment;
	/* TO_DO: Initialize flags */
	/* TO_DO: Default checksum */
	return readerPointer;
}


/*
*********************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/

BufferPointer readerAddChar(BufferPointer readerPointer, cjs_char ch) {
	cjs_string tempReader = CJS_INVALID;
	cjs_intg newSize = 0;
	cjs_char tempChar = ' ';
	/* TO_DO: Defensive programming */
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->positions.wrte * (cjs_intg)sizeof(cjs_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
	}
	else {
		/* TO_DO: Reset Full flag */
		switch (readerPointer->mode) {
		case MODE_FIXED:
			/* TO_DO: Update the last position with Terminator */
			break;
		case MODE_ADDIT:
			/* TO_DO: Update size for Additive mode */
			/* TO_DO: Defensive programming */
			break;
		case MODE_MULTI:
			/* TO_DO: Update size for Additive mode */
			/* TO_DO: Defensive programming */
			break;
		default:
			return CJS_INVALID;
		}
		/* TO_DO: Reallocate */
		/* TO_DO: Defensive programming */
		return readerPointer;
	}
	/* TO_DO: Update the flags */
	readerPointer->content[readerPointer->positions.wrte++] = ch;
	/* TO_DO: Updates histogram */
	return readerPointer;
}

/*
*********************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_boln readerClear(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust the write, mark and read to zero */
	/* TO_DO: Adjust flags */
	return CJS_TRUE;
}

/*
*********************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_boln readerFree(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Free pointers */
	return CJS_TRUE;
}

/*
*********************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_boln readerIsFull(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is FUL */
	return 0;
}


/*
*********************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_boln readerIsEmpty(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check flag if buffer is EMP */
	return 0;
}

/*
*********************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_boln readerSetMark(BufferPointer const readerPointer, cjs_intg mark) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Adjust mark */
	return CJS_TRUE;
}


/*
*********************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_intg readerPrint(BufferPointer const readerPointer) {
	cjs_intg cont = 0;
	cjs_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	while (cont < readerPointer->positions.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
*********************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_intg readerLoad(BufferPointer readerPointer, FILE* const fileDescriptor) {
	cjs_intg size = 0;
	cjs_char c;
	/* TO_DO: Defensive programming */
	while (!feof(fileDescriptor)) {
		c = (cjs_char)fgetc(fileDescriptor);
		readerPointer = readerAddChar(readerPointer, c);
		size++;
	}
	/* TO_DO: Defensive programming */
	return size;
}

/*
*********************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_boln readerRecover(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Recover positions: read and mark must be zero */
	/* TO_DO: Update flags */
	return CJS_TRUE;
}


/*
*********************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_boln readerRetract(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Retract (return 1 pos read) */
	return CJS_TRUE;
}


/*
*********************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_boln readerRestore(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Restore positions (read to mark) */
	return CJS_TRUE;
}



/*
*********************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_char readerGetChar(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Check condition to read/wrte */
	return readerPointer->content[readerPointer->positions.read++];
}


/*
*********************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_string readerGetContent(BufferPointer const readerPointer, cjs_intg pos) {
	/* TO_DO: Defensive programming */
	return readerPointer->content + pos;
}



/*
*********************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_intg readerGetPosRead(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return read */
	return 0;
}


/*
*********************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_intg readerGetPosWrte(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return wrte */
	return 0;
}


/*
*********************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_intg readerGetPosMark(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mark */
	return 0;
}


/*
*********************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_intg readerGetSize(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return size */
	return 0;
}

/*
*********************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_intg readerGetInc(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return increment */
	return 0;
}

/*
*********************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_char readerGetMode(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mode */
	return '\0';
}

/*
*********************
* Function name: readerShowStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_void readerPrintStat(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
}

/*
*********************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*********************
*/
cjs_intg readerGetNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Returns the number of errors */
	return 0;
}

/*
*********************
* Function name: readerCalcChecksum
* Purpose: Calculates the checksum of the reader (8 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/

cjs_void readerCalcChecksum(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Calculate checksum */
}

/*
*********************
* Function name: readerPrintFlags
* Purpose: Sets the checksum of the reader (4 bits).
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	[None]
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*********************
*/

cjs_boln readerPrintFlags(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Shows flags */
	return CJS_TRUE;
}
