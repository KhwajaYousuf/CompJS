/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2024
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (F24)  |"
# ECHO "=---------------------------------------="
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "    @@                             @@    �
# ECHO "    @@           %&@@@@@@@@@@@     @@    �
# ECHO "    @@       @%% (@@@@@@@@@  @     @@    �
# ECHO "    @@      @& @   @ @       @     @@    �
# ECHO "    @@     @ @ %  / /   @@@@@@     @@    �
# ECHO "    @@      & @ @  @@              @@    �
# ECHO "    @@       @/ @*@ @ @   @        @@    �
# ECHO "    @@           @@@@  @@ @ @      @@    �
# ECHO "    @@            /@@    @@@ @     @@    �
# ECHO "    @@     @      / /     @@ @     @@    �
# ECHO "    @@     @ @@   /@/   @@@ @      @@    �
# ECHO "    @@     @@@@@@@@@@@@@@@         @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@         S O F I A           @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
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
 ***********************************************************
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
 *************************************************************
 */

BufferPointer readerCreate(cjs_intg size, cjs_intg increment, cjs_char mode) {
	BufferPointer readerPointer;


	// Defensive programming: Validate parameters
	if (size <= 0) size = READER_DEFAULT_SIZE;  // Use default if size is negative
	if (increment <= 0) increment = READER_DEFAULT_INCREMENT; // Use default if increment is negative
	if (mode != MODE_FIXED && mode != MODE_ADDIT && mode != MODE_MULTI) {
		return CJS_INVALID; // Invalid mode, return NULL
	}

	// Allocate memory for the reader structure
	readerPointer = (BufferPointer)calloc(1, sizeof(Buffer));
	if (!readerPointer) {
		return CJS_INVALID; // Memory allocation failure
	}


	// Allocate memory for the content buffer
	readerPointer->content = (cjs_string)malloc(size);
	if (!readerPointer->content) {
		free(readerPointer); // Free previously allocated memory
		return CJS_INVALID; // Memory allocation failure
	}

	// Initialize the histogram
	for (int i = 0; i < NCHAR; i++) {
		readerPointer->histogram[i] = 0; // Set each element of the histogram to 0
	}

	// Initialize fields
	readerPointer->size = size; // Set reader size to the given value
	readerPointer->increment = increment; // Set increment for buffer growth
	readerPointer->mode = mode; // Set reader mode for buffer behavior

	// Initialize flags
	readerPointer->flags.isEmpty = CJS_TRUE;  // Initially the reader is empty
	readerPointer->flags.isFull = CJS_FALSE;  // Initially the reader is not full
	readerPointer->flags.isRead = CJS_FALSE;  // No data has been read yet
	readerPointer->flags.isMoved = CJS_FALSE; // No movement has occurred yet

	readerPointer->content[0] = READER_TERMINATOR; // Initialize content with terminator
	readerPointer->positions.wrte = 0; // Initialize write position
	readerPointer->positions.mark = 0; // Initialize mark position
	readerPointer->positions.read = 0; // Initialize read position

	return readerPointer; // Return the newly created reader pointer
}


/*
***********************************************************
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
*************************************************************
*/

BufferPointer readerAddChar(BufferPointer readerPointer, cjs_char ch) {
    cjs_string tempReader = CJS_INVALID;
    cjs_intg newSize = 0;


    //Defensive programming: Ensure valid pointer and character 
    if (!readerPointer) return CJS_INVALID;
    if (ch < 0) return CJS_INVALID;

    //Check if the buffer is full 
    if (readerPointer->positions.wrte * (cjs_intg)sizeof(cjs_char) >= readerPointer->size) {
        //Buffer is full, reallocate if necessary 
        switch (readerPointer->mode) {
            case MODE_FIXED:
                //In fixed mode, no reallocation is allowed 
                //readerPointer->flags.isFull = 1;
                return CJS_INVALID;

            case MODE_ADDIT:
                //Additive mode: Increase size by increment 
                newSize = readerPointer->size + readerPointer->increment;
                break;

            case MODE_MULTI:
                //Multiplicative mode: Increase size by multiplying 
                newSize = readerPointer->size * readerPointer->increment;
                break;

            default:
                //Invalid mode 
                return CJS_INVALID; 
        }

        //Check if the new size is valid and within the limit 
        if (newSize <= 0 || newSize > READER_MAX_SIZE) return CJS_INVALID;

        //Reallocate memory defensively 
        tempReader = (cjs_string)realloc(readerPointer->content, newSize * sizeof(cjs_char));
        if (!tempReader) return CJS_INVALID;  //Reallocation failed 

        //Check if memory address has changed 
		if (tempReader != readerPointer->content) {
			readerPointer->flags.isMoved = CJS_TRUE; 
		}

        //Update buffer with the new size and content 
        readerPointer->content = tempReader;
        readerPointer->size = newSize;
        readerPointer->flags.isFull = 0;  //Reset the full flag
    }


    //Add the character to the buffer 
    readerPointer->content[readerPointer->positions.wrte++] = ch;
	if (ch >= 0 && ch < NCHAR) {
		readerPointer->histogram[ch]++; 
	}

    return readerPointer;
}


/*
***********************************************************
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
*************************************************************
*/
cjs_boln readerClear(BufferPointer const readerPointer) {
	// Defensive programming: Check for NULL pointer
	if (readerPointer == CJS_INVALID)
		return CJS_FALSE;

	// Resetting positions to zero
	readerPointer->positions.wrte = 0;
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;

	// Resetting flags to default values
	readerPointer->flags.isEmpty = 1;   // Buffer is now empty
	readerPointer->flags.isFull = 0;    // Buffer is not full
	readerPointer->flags.isRead = 0;    // Nothing has been read
	readerPointer->flags.isMoved = 0;   // Memory has not been changed

	memset(readerPointer->histogram, 0, sizeof(readerPointer->histogram));
	readerPointer->numReaderErrors = 0;
	readerPointer->checksum = 0; 

	return CJS_TRUE; // Return�success
}
/*
***********************************************************
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
*************************************************************
*/
cjs_boln readerFree(BufferPointer const readerPointer) {
	// Defensive programming: Check for NULL pointer
	if (readerPointer == CJS_INVALID) {
		return CJS_FALSE; // Return false if the pointer is NULL
	}

	// Free the readerPointer itself
	free(readerPointer); // Free the main structure

	return CJS_TRUE; // Return true to indicate successful�deallocation
}

/*
***********************************************************
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
*************************************************************
*/
cjs_boln readerIsFull(BufferPointer const readerPointer) {
	// Defensive programming: Check if readerPointer is NULL
	if (readerPointer == CJS_INVALID) {
		return CJS_FALSE; // Consider NULL as not full
	}

	// Check the isFull flag
	if (readerPointer->flags.isFull) {
		return CJS_TRUE; // Buffer is full
	}

	// Buffer is not full
	return CJS_FALSE;
}


/*
***********************************************************
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
*************************************************************
*/
cjs_boln readerIsEmpty(BufferPointer const readerPointer) {
	// Defensive programming: Check if readerPointer is NULL
	if (readerPointer == CJS_INVALID) {
		return CJS_FALSE; // Return false if the pointer is invalid
	}

	// Check the isEmpty flag
	if (readerPointer->flags.isEmpty) {
		return CJS_TRUE; // Return true if the buffer is empty
	}

	// Buffer is not empty
	return CJS_FALSE;
}

/*
***********************************************************
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
*************************************************************
*/
cjs_boln readerSetMark(BufferPointer const readerPointer, cjs_intg mark) {
    // Defensive programming: Check for NULL pointer
    if (readerPointer == CJS_INVALID) {
        return CJS_FALSE; // Return false if readerPointer is NULL
    }

    // Check boundary conditions for the mark
    if (mark < 0 || mark > readerPointer->positions.wrte) {
        return CJS_FALSE; // Return false if mark is out of valid range
    }

    // Set the mark position
    readerPointer->positions.mark = mark; 
    return CJS_TRUE; // Return true indicating�success
}


/*
***********************************************************
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
*************************************************************
*/
cjs_intg readerPrint(BufferPointer const readerPointer) {
	cjs_intg cont = 0;
	cjs_char c;

	// Defensive programming: Check if readerPointer is NULL
	if (readerPointer == CJS_INVALID) {
		return 0; // Return 0 if the pointer is null
	}
	while (cont < readerPointer->positions.wrte) { 

		cont++;
		c = readerGetChar(readerPointer); 
		printf("%c", c);

		if (c < 0 || c >= NCHAR)c = 0; 
		if (readerPointer->flags.isRead)break;

	}
	return cont;
}

/*
***********************************************************
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
*************************************************************
*/
cjs_intg readerLoad(BufferPointer readerPointer, FILE* const fileDescriptor) {
	cjs_intg size = 0;
	cjs_char c;

	// Defensive programming: Check if readerPointer or fileDescriptor is NULL
	if (readerPointer == CJS_INVALID) {
		return 0; // Return 0 if the pointer is null
	}

	if (fileDescriptor == CJS_INVALID) {
		return 0; // Return 0 if the file descriptor is invalid
	}

	c = (cjs_char)fgetc(fileDescriptor);  // Read the first character from the file
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return CHARSEOF; // Return EOF indicator
		}
		c = (char)fgetc(fileDescriptor); // Read the next character

		size++;
	}
	return size; // Return the total number of characters read
}   

/*
***********************************************************
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
*************************************************************
*/
cjs_boln readerRecover(BufferPointer const readerPointer) {
	// Defensive programming: Check if readerPointer is NULL
	if (readerPointer == CJS_INVALID) {
		return CJS_FALSE; // Return FALSE if the pointer is null
	}

	// Reset read and mark offsets to zero
	readerPointer->positions.read = 0;
	readerPointer->positions.mark = 0;

	return CJS_TRUE; // Return TRUE if operation is successful
}


/*
***********************************************************
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
*************************************************************
*/
cjs_boln readerRetract(BufferPointer const readerPointer) {
	// Defensive programming: Check if readerPointer is NULL
	if (readerPointer == CJS_INVALID) {
		return CJS_FALSE; // Return FALSE if the pointer is null
	}
	if (readerPointer->positions.read--); { // Decrement read position
		return CJS_TRUE;
	}
}

/*
***********************************************************
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
*************************************************************
*/
cjs_boln readerRestore(BufferPointer const readerPointer) {
	if (readerPointer == CJS_INVALID)
		return CJS_FALSE; // Return false if the reader pointer is invalid
	readerPointer->positions.read = readerPointer->positions.mark; // Restore the read position to the marked position
	return CJS_TRUE;
}



/*
***********************************************************
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
*************************************************************
*/
cjs_char readerGetChar(BufferPointer const readerPointer) {
    // Defensive programming: Check if the readerPointer is NULL
    if (readerPointer == CJS_INVALID) {
        return CHARSEOF; // Return EOF code as an indication of error
    }

    // Check if read position has reached or exceeded write position
    if (readerPointer->positions.read >= readerPointer->positions.wrte) {
        // Set the END flag to true
        readerPointer->flags.isRead = CJS_TRUE; // Mark as read
        readerPointer->flags.isEmpty = CJS_TRUE; // Mark as empty
        return READER_TERMINATOR; // Return end of string character
    } else {
        // Reset the END flag to false
        readerPointer->flags.isRead = CJS_FALSE;
    }

    // Return the character at the current read position and increment read position
    return readerPointer->content[readerPointer->positions.read++];
}


/*
***********************************************************
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
*************************************************************
*/
cjs_string readerGetContent(BufferPointer const readerPointer, cjs_intg pos) {
    // Defensive programming: Check if readerPointer is NULL
    if (readerPointer == CJS_INVALID) {
        return CJS_INVALID; // Return NULL to indicate an error
    }

    // Check if the position is valid
    if (pos < 0 || pos >= readerPointer->positions.wrte) {
        return CJS_INVALID; // Return NULL for invalid position
    }

    // Return the pointer to the content starting from the specified position
    return readerPointer->content + pos;
}



/*
***********************************************************
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
*************************************************************
*/
cjs_intg readerGetPosRead(BufferPointer const readerPointer) {
	// Defensive programming: Check if readerPointer is NULL
	if (readerPointer == CJS_INVALID) {
		return -1; // Return -1 to indicate an error
	}

	// Return the read position offset
	return readerPointer->positions.read;
}

/*
***********************************************************
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
*************************************************************
*/
cjs_intg readerGetPosWrte(BufferPointer const readerPointer) {
    // Defensive programming: Check if readerPointer is NULL
    if (readerPointer == CJS_INVALID) {
        return -1; // Return -1 to indicate an error
    }

    // Return the write position
    return readerPointer->positions.wrte;
}


/*
***********************************************************
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
*************************************************************
*/
cjs_intg readerGetPosMark(BufferPointer const readerPointer) {
	// Defensive programming: Check if readerPointer is NULL
	if (readerPointer == CJS_INVALID) {
		return -1; // Return -1 to indicate an error
	}

	// Return the mark position
	return readerPointer->positions.mark;
}


/*
***********************************************************
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
*************************************************************
*/
cjs_intg readerGetSize(BufferPointer const readerPointer) {
	// Defensive programming: Check if readerPointer is NULL
	if (readerPointer == CJS_INVALID) {
		return -1; // Return -1 to indicate an error
	}

	// Return the size of the buffer
	return readerPointer->size;
}

/*
***********************************************************
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
*************************************************************
*/
cjs_intg readerGetInc(BufferPointer const readerPointer) {
	// Defensive programming: Check if readerPointer is NULL
	if (readerPointer == CJS_INVALID) {
		return -1; // Return -1 to indicate an error
	}

	// Return the buffer increment value
	return readerPointer->increment; 
}

/*
***********************************************************
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
*************************************************************
*/
sofia_char readerGetMode(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Return mode */
	return '\0';
}

/*
***********************************************************
* Function name: readerShowStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
sofia_void readerPrintStat(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Updates the histogram */
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
sofia_intg readerGetNumErrors(BufferPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Returns the number of errors */
	return 0;
}

/*
***********************************************************
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
*************************************************************
*/

sofia_void readerCalcChecksum(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Calculate checksum */
}

/*
***********************************************************
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
*************************************************************
*/

sofia_boln readerPrintFlags(BufferPointer readerPointer) {
	/* TO_DO: Defensive programming */
	/* TO_DO: Shows flags */
	return SOFIA_TRUE;
}
