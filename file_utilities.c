/*****************************************************************
This is the c file for file utilities. This file is used
in the Game of Life to allocate memory, print the world, complete
a generation, move on to the next step, and more.

@author Cade Baker
@version Winter 2018
*****************************************************************/

/** here i include the header for this library */
#include "file_utilities.h"

/**two global variables for row and column*/
int row;
int column;

/*****************************************************************
    The read_file function reads data from a file and imports it
    to use for the game of life
    @param filename the pointer for the filename to load
    @param world the triple pointer to the board
    *****************************************************************/
int read_file( char* filename, char ***world){
  //open a file for reading
  FILE *fileIn;
  fileIn = fopen(filename, "r");
  //check if the file exists or not
  if(fileIn == NULL)
    printf("%s\n", "File either doesn't exist, or we cannot access it.");
  else{

    //let user know the file exists
    printf("%s\n", "File Exists.");

    //scan the first two rows for the number of rows and columns
    fscanf(fileIn, "%d\n", &row);
    fscanf(fileIn, "%d\n", &column);

    //allocate the memory for the loaded board
    allocateMem(world, row, column);

    //run a loop to add all the values from the file to the board
    for (int i = 0; i < row; i++){
      for (int j = 0; j < column; j++){
          //create char to store value from the scan position
			    char l;
          //scan the value at the position i,j and store it in l
        	fscanf(fileIn, "%c",&l);
          //if it is NOT a newline character, add it to the world
	 		    if(l!='\n')
	 			     (*world)[i][j] = l;
          //if it is, deincrement j by one and continue the loop
			    else
				      j--;
      }
    }

  //print out the new world
  printWorld(*world, row, column);

  //let user know the load was successful
  printf("%s\n\n", "Load Successful.");
  }

  return 0;
}

/*****************************************************************
    The write_File function saves the current board to a file
    @param filename the pointer to the filename to save as
    @param world the double pointer value for the world
    @param size the amount of rows and columns in the board
    *****************************************************************/
int write_file( char* filename, char **world, int size){
  //utilized stackoverflow
  //stackoverflow.com/questions/13235412/saving-multidimensional-arrays-in-c

  //open a file for writing
  FILE * fileOut;
  fileOut = fopen(filename, "w");

  //check if we couldn't open the file
  if(fileOut == NULL){
    printf("%s\n", "File either doesn't exist, or we cannot access it.");
  }

  //if we can, start writing
  else{
    //print number of rows on the first line
    fprintf(fileOut, "%d\n", row);
    //print number of columns on the second line
    fprintf(fileOut, "%d\n", column);
    //save the world on the rest of the lines
    for (int i = 0; i < row; i++){
        for (int j = 0; j < column; j++){
          fprintf(fileOut, "%c", world[i][j]);
        }
        //add a new line between the rows
        fprintf(fileOut, "\n");
    }
  //notify user file was saved, then quit
   printf("%s\n", "Save Successful.");;
   exit(0);
 }

  return 0;
}


/*****************************************************************
    The allocateMem function allocates the memory needed to store
    the board requested
    @param world the double pointer value for the world
    @param r the amount of rows in the board
    @param c the amount of columns in the board
    *****************************************************************/
int allocateMem(char *** world, int r, int c){
  //create ints to store the row, column, and iterators
  row = r;
  column = c;
  int i, j;

  //use malloc to allocate the memory for the pointers
  *world = (char **)malloc(row * sizeof(char *));

  //use malloc to create the memory for the rows
  for (i=0; i < row; i++)
    (*world)[i] = (char *)malloc(column * sizeof(char));
  //populate the rows
   for (i = 0; i <  row; i++)
      for (j = 0; j < column; j++)
          (*world)[i][j] = '-';

  return 0;
}

/*****************************************************************
    The generation function checks surrounding values to either declare
    a cell as dead or alive
    @param world the triple pointer value for the world
    @param r number of rows in the board
    @param c number of columns in the baord
    *****************************************************************/
int generation(char*** world, int r, int c){
  //create double pointer to store amount of surrounding cells
  char ** worldNums;
  //allocate memory for the worldNums double pointer
  allocateMem(&worldNums, r, c);

  //run for loop to count the number of surrounding cells
  for(int i = 0; i < r; i++){
    for(int j = 0; j < c; j++){
      //if the cell is alive or dead
      if((*world)[i][j] == 'o' || (*world)[i][j] == 'x'){
        //counter for the number of cells surrounding
        int counter = 0;
        //check if row is at least 1
        if(i >0){
          //check if there} is value above the cell
          if((*world)[i - 1][j] == 'o'){
            counter++;
          }
        }
        //check if there is another row below
        if((i+1) < r){
          //check if there is value below
          if((*world)[i + 1][j] == 'o'){
            counter++;
          }
        }
        //check if there is a column to the left
        if(j > 0){
          //check if there is value to the left
          if((*world)[i][j - 1] == 'o'){
            counter++;
          }
        }
        //check if there is a column to the right
        if((j+1) < c){
          //check if there is a value to the left
          if((*world)[i][j + 1] == 'o'){
            counter++;
          }
        }

        //check if there is a upper-left
        if(i > 0 && j >0){
          //check if there is a value in the upper-left
          if((*world)[i - 1][j - 1] == 'o'){
            counter++;
          }
        }

        //check if there is an upper right
        if(i > 0 && (j+1) < c){
          //check if there is a value in the upper-right
          if((*world)[i - 1][j + 1] == 'o'){
            counter++;
          }
        }

        //check if there is a bottom-left
        if(((i+1) < r) && (j > 0)){
          //check if there is a value in the bottom-left
          if((*world)[i + 1][j - 1] == 'o'){
            counter++;
          }
        }

        //check if there is a bottom right
        if((i+1) < r && (j+1) < c){
          //check if there is a value in the bottom-right
          if((*world)[i + 1][j + 1] == 'o'){
            counter++;
          }
        }

        //if theres less than 2 surrounding cells, write a L
        if (counter < 2)
          (worldNums)[i][j] = 'l';

        //if theres more than 3 surronding cells, write a G
        if (counter > 3)
          (worldNums)[i][j] = 'g';

        //if there are two surrounding cells, write an e
        if (counter == 2)
          (worldNums)[i][j] = 'e';

        //if there are three surrounding cells, write a t
        if (counter == 3)
          (worldNums)[i][j] = 't';
        //reset the counter for the next set
        counter = 0;

      }

    }
  }
      //for loop to update the original cells after counting surrounding cells
      for(int i = 0; i< r; i++){
        for(int j = 0; j<c; j++){
          //if cell has <2 neighbors, it dies
          if((*world)[i][j] == 'o' && (worldNums)[i][j] == 'l')
            (*world)[i][j] = 'x';

          //if cell has >3 neighbors, it dies
          if((*world)[i][j] == 'o' && (worldNums)[i][j] == 'g')
            (*world)[i][j] = 'x';

          //if cell has 2 - 3 neighbors, it lives
          if((*world)[i][j] == 'o' && ((worldNums)[i][j] == 'e' ||
              (worldNums)[i][j] == 't')){
                (*world)[i][j] = 'o';
          }

          //if cell is dead with 3 live neighbors, it becomes live
          if((*world)[i][j] == 'x' && (worldNums)[i][j]  == 't')
            (*world)[i][j] = 'o';

        }
      }

  //free the temportary board from memory
  free(worldNums);
  return 0;
}


/*****************************************************************
    The printWorld function prints the current state of the double
    pointer / world
    @param world the double pointer value for the world
    *****************************************************************/
int printWorld(char** world, int r, int c){
  int row = r, column = c, i, j;
  //loop through the rows and columns and print them out
  for (i = 0; i <  row; i++){
     for (j = 0; j < column; j++)
         printf("%c", world[i][j]);
    //print a new line in between the rows
     printf("\n");
  }
  return 0;
}

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
int nextStep(char *** world, int* r, int* c, char next, int amt, char* filename){
  // save, load, continue another generation, continue some number of
  // iterations, or quit.

  //if user types 'n', run another generation and print it
  if(next == 'n'){
    generation(&(*world), *r, *c);
    printWorld(&(**world), *r, *c);
  }

  //if user types 'c', run a certain number of generations
  else if(next == 'c'){
    //iteration counter
    int iteration = 1;
    //notify user how many iterations are going to run
    printf("%s%d%s\n\n", "Running ", amt, " Generations...");
    //loop for running generations and printing them
    for(int i = 0; i < amt; i++){
      generation(&(*world), *r, *c);
      printf("%s%d\n","Iteration: ", iteration);
      printWorld(&(**world), *r, *c);
      iteration ++;
    }
  }

  //if user types 's', try to save the file and quit
  else if(next == 's'){
    //if file saves successfully, notify user and quit
    write_file(filename, *world,(*r) * (*c));

  }

  else if(next == 'l'){
    //read the file and replace the current world
    read_file(filename, (&(*world)));
    //update the number of rows and columns in the main function
    updateRowColumn(r,c);
  }

  //if user types 'q', exit the program and free the memory
  else if(next == 'q'){
    //free the memory
    free(&(**world));
    //exit
    exit(0);
  }

  return 0;
};

/*****************************************************************
    The updateRowColumn function updates the number of rows and
    columns after loading a new board
    @param *r pointer to the number of rows from the main function
    @param *c pointer to the number of columns from the main function
    *****************************************************************/
int updateRowColumn(int* r, int* c){
  *r = row;
  *c = column;
  return 0;
}

/*****************************************************************
    The initialBoard function places inital live cells on the board
    @param world the triple pointer value for the world
    *****************************************************************/
int initialBoard(char *** world){

  //set inital spots on board to an alive cell 'o'
  (*world)[1][1] = 'o';
  (*world)[2][2] = 'o';
  (*world)[0][2] = 'o';
  (*world)[1][2] = 'o';
  (*world)[3][2] = 'o';
  //(*world)[0][2] = 'o';

  return 0;
}
