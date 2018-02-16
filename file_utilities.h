/*****************************************************************
This is the header file for file utilities. This file is used
in the Game of Life to allocate memory, print the world, complete
a generation, move on to the next step, and more.

@author Cade Baker
@version Winter 2018
*****************************************************************/

/** here i complete a definition for this library */
#ifndef FILE_UTILITIES_H
#define FILE_UTILITIES_H

/** here i include a standard library used for several input/output
    commands */
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************
    The read_file function reads data from a file and imports it
    to use for the game of life
    @param filename the pointer for the filename to load
    @param world the triple pointer to the board
    *****************************************************************/
int read_file( char* filename, char ***world );

/*****************************************************************
    The write_File function saves the current board to a file
    @param filename the pointer to the filename to save as
    @param world the double pointer value for the world
    @param size the amount of rows and columns in the board
    *****************************************************************/
int write_file( char* filename, char **world, int size);

/*****************************************************************
    The allocateMem function allocates the memory needed to store
    the board requested
    @param world the double pointer value for the world
    @param r the amount of rows in the board
    @param c the amount of columns in the board
    *****************************************************************/
int allocateMem(char*** world, int r, int c);

/*****************************************************************
    The generation function checks surrounding values to either declare
    a cell as dead or alive
    @param world the triple pointer value for the world
    @param r number of rows in the board
    @param c number of columns in the baord
    *****************************************************************/
int generation(char*** world, int r, int c);

/*****************************************************************
    The printWorld function prints the current state of the double
    pointer / world
    @param world the double pointer value for the world
    *****************************************************************/
int printWorld(char** world, int r, int c);

/*****************************************************************
    The nextStep function allows the user to run another generation,
    run X number of generations, quit the game, or save / load a game
    @param world the triple pointer value for the world
    @param r the number of rows in the board
    @param c the number of columns in the board
    @param next the coresponding char value for what the user wants
           to do next
    @param amt the amount of generations a user wants to run
           (if user selects the 'c' char value)
    @param filename the name of the file to either load or save
    *****************************************************************/
int nextStep(char *** world, int* r, int* c, char next, int amt, char* filename);

/*****************************************************************
    The updateRowColumn function updates the number of rows and
    columns after loading a new board
    @param *r pointer to the number of rows from the main function
    @param *c pointer to the number of columns from the main function
    *****************************************************************/
int updateRowColumn(int* r, int* c);

/*****************************************************************
    The initialBoard function places inital live cells on the board
    @param world the triple pointer value for the world
    *****************************************************************/
int initialBoard(char *** world);


#endif
