/*****************************************************************
This is the Game of Life. This program allows users to simiulate
life through various generations, save their progress, and load
a save file.

@author Cade Baker
@version Winter 2018
*****************************************************************/

/** here i include a standard library used for several input/output
    commands */
#include <stdio.h>
/** i also include a library created by me */
#include "file_utilities.h"



/*****************************************************************
    The main function runs the program, which is heavily developed
    in the file_utilities.(c/h) files
    @param argc counts # of arguments
    @param argv contains the arguments
    *****************************************************************/
int main(int argc, char** argv){

  //create a double pointer to hold the array values
  char ** world;
  //create variables for the row and column
  int row = 4;
  int column = 4;

  //command line arguments taken in as row and column (min 4x4)
  if(argv[1] != NULL && argv[2] != NULL
    && atoi(argv[1]) >4 && atoi(argv[2]) > 4){
      row = atoi(argv[1]);
      column = atoi(argv[2]);
  }
  //let user know the command line values were not found or not excepted
  else{
    printf("%s", "\nNOTICE: You either didn't enter values on the command line \
        \nor the values were less than a 4x4 grid.. Running default 4x4..\n\n");
  }

  //print welcome statement
  printf("%s","Welcome to the Game of Life!\n\n");

  //create space for the needed memory
  allocateMem(&world, row, column);
  //places values for the initial board
  initialBoard(&world);

  //print out a message and the board
  printf("%s\n", "Here's your starting board...\n\n" );
  printWorld(world, row, column);

  //create loop to keep asking what to do next
  while(1){
    //create message to ask what is next
    char* message = "\n\nWhats next? \n"
                    "Continue with one generation(n) \n"
                    "Continue with certain # of generations(c) \n"
                    "Save(s) \n"
                    "Load(l) \n"
                    "Quit(q) \n";
    //create variable to see whats next
    char next[5];
    //create variable to see how many iterations the user wants
    int amt;
    //create variable to see what the filename should be
    char filename;
    char fname[1024];
    //print the message
    printf("%s", message);
    //wait for user to respond
    scanf("%s", next);
    //fgets(next, sizeof(next), stdin);
    //ask another question if user wants to run multiple generations
     if(*next == 'c'){
       //print the messages
       printf("%s", "How many generations? ");
       //wait for user input
       scanf("%d", &amt);
       //fgets(fname, sizeof(fname), stdin);
       //amt = atoi(fname);

     }
     if(*next=='s'){
       printf("%s\n", "Name the file to save (include .txt at the end): ");
       scanf("%s", fname);
       //fgets(fname, sizeof(fname), stdin);

     }
     if(*next=='l'){
       printf("%s\n", "Name the file to load (include .txt at the end): ");
       scanf("%s", fname);
       //fgets(fname, sizeof(fname), stdin);
     }
    //send the next step from the user to the nextStep function
    nextStep(&world, &row, &column, *next, amt, fname);

}



  return 0;
}
