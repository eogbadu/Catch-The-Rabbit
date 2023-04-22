/********************************************************************
 ** File:      Proj1.cpp
 ** Project:   CMSC 202 Project 1, Fall 2019
 ** Author:    Ekele Ogbadu
 ** Date:      25 Sep 2019
 ** Section:   
 ** Email:     eogbadu1@umbc.edu
 **
 ** This file contains the main driver program for project 1.
 ** This program is a simple game where a farmer chases a 
 ** rabbit. On each turn, the rabbit can either move in a 
 ** random direction or stay where they are.
 ** The game continues until the farmer catches the rabbit. It 
 ** should then prompt the user for another game.
 *******************************************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
using namespace std;

// Declare constants
const int NUM_ROWS = 10; // The number of rows in the board
const int NUM_COLS = 10; // The number of columns in the board
const int FIRST_POS = 0; // The first position
const int LAST_POS = 9;  // The last position in a 10x10 board
const int NUM_DIRECTIONS = 4; // The number of directions available to move to
const char RABBIT = 'R'; // The symbol for the rabbit on the field
const char FARMER = 'F'; // The symbol for the farmer on the field

//--------------------------------------------------------------------
// Name:          printField
// PreCondition:  A 2-dimensional array already exists.
// PostCondition: Prints out a 2-dimensional array.
//--------------------------------------------------------------------
void printField(char field[][NUM_COLS]);

//--------------------------------------------------------------------
// Name:          initializeRabbit
// PreCondition:  A 2-dimensional array and an initial position
//                exists.
// PostCondition: The letter R, representing a rabbit is placed
//                randomly on the 2-dimentional array.
//--------------------------------------------------------------------
void initializeRabbit(char field[][NUM_COLS], int currentPosition[]);

//--------------------------------------------------------------------
// Name:          initializeFarmer
// PreCondition:  A 2-dimensional array and an initial position
//                exists.
// PostCondition: The letter F, representing a farmer is placed
//                on the 2-dimentional array according to the
//                user preferences.
//--------------------------------------------------------------------
void initializeFarmer(char field[][NUM_COLS], int currentPosition[]);

//--------------------------------------------------------------------
// Name:          moveFarmer
// PreCondition:  The current position of the farmer is known.
//                The direction has been given by the user.
// PostCondition: Farmer is moved to specified location on the
//                2-dimensional field.
//-------------------------------------------------------------------
void moveFarmer(char field[][NUM_COLS], int currentPosition[], int direction);

//--------------------------------------------------------------------
// Name:          moveRabbit
// PreCondition:  The current position of the farmer is known.
//                The current position of the rabbit is known
// PostCondition: Rabbit is either moved to a random location, 1 
//                position from previous location, or remains in
//                the same position of the 2-dimensional field.
//-------------------------------------------------------------------
void moveRabbit(char field[][NUM_COLS], int rPosition[], int fPosition[]);

//-------------------------------------------------------------------
// Name:          whereIsRabbit
// PreCondition:  Farmer and Rabbit location on 2-dimensional field
//                is known.
// PostCondition: The location of the rabbit in terms of the farmer
//                is printed out to the screen.
//-------------------------------------------------------------------
void whereIsRabbit(int fPosition[], int rPosition[]);

//-------------------------------------------------------------------
// Name:          getDirection
// PreCondition:  None
// PostCondition: Returns the direction the user would like the
//                farmer to move in.
//-------------------------------------------------------------------
int getDirection();

int main()
{

  bool moreGames = true; // To check if user wants to keep playing

  // While the user wants to keep playing
  while (moreGames == true)
  {
    
    // Declare varaibles
    int rPosition[2] = {0, 0};  // Rabbit position
    int fPosition[2] = {0, 0};  // Farmer position
    bool isComplete = false;    // Used to check if game is complete
    char answer;                // Holds if player wants to keep playing
    bool goodAnswer = false;     // Checks if the answer given above is correct

    // Declare 2-dimensional array which represents the field.
    char myArray[NUM_ROWS][NUM_COLS] = 
    {
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' '}
   
    };

    // print message to user and get positions of rabbit and farmer
    cout << "Welcome to Chase the Rabbit" << endl;
    initializeRabbit(myArray, rPosition);
    initializeFarmer(myArray, fPosition);

    // While the rabbit has not been caught
    while(isComplete == false)
    {
      // Get direction to move to from user and move farmer
      moveFarmer(myArray, fPosition, getDirection());

      if ((rPosition[0] == fPosition[0]) && (rPosition[1] == fPosition[1]))
      {
	// If farmer and rabbit are in the same position, game is over
	isComplete = true;
      }
      else
      {
	// Else move the rabbit and find its location in terms of
	// the farmer
	moveRabbit(myArray, rPosition, fPosition);
	whereIsRabbit(fPosition, rPosition);
      }

      // Print the 2 dimensional array as a field.
      printField(myArray);
    }

    cout << "You caught the rabbit! Thanks for playing!" << endl;
    

    // Check if the user would like to play again
    while (goodAnswer == false)
    {
      cout << "Would you like to play again? (Y/N)" << endl;
      cin.clear();
      cin >> answer;
      if ((answer == 'y') || (answer == 'Y'))
      {
	// If yes, then start game over
	moreGames = true;
	goodAnswer = true;
      }
      else if ((answer == 'n') || (answer == 'N'))
      {
	// If no, then thank user and end game
	cout << "Thanks once again for playing!";
	cout << " See you again next time" << endl;
	moreGames = false;
	goodAnswer = true;
      }
      else
      {
	// If wrong invalid answer is entered,
	// ask again
	cout << "******Error******" << endl;
	cout << " Please input Y/N" << endl;
	goodAnswer = false;
      }
    }
  }
  return 0;
}

// whereIsRabbit
// Given the positions of farmer and rabbit, prints the
// location of the rabbit in terms of the farmer.
void whereIsRabbit(int fPosition[], int rPosition[])
{
  int verticalLength; // The vertical distance between rabbit and farmer
  int horizontalLength; // The horizontal distance between the rabbit and farmer 

  // subtract rabbit position from farmer position to get distance
  verticalLength = fPosition[0] - rPosition[0];
  horizontalLength = fPosition[1] - rPosition[1];

  if (abs(verticalLength) >= abs(horizontalLength))
  {
    // If vertical distance is greater or equal to horizontal distance
    if (verticalLength > 0)
    {
      // If vertical distance is positive, rabbit is above farmer.
      cout << "The rabbit is north of the farmer." << endl;
    }
    else if (verticalLength < 0)
    {
      // If vertical distance is negative, rabbit is below farmer.
      cout << "The rabbit is south of the farmer." << endl;
    }
  }
  else if (abs(verticalLength) < abs(horizontalLength))
  {
    // If vertical distance is less than horizontal distance
    if (horizontalLength > 0)
    {
      // If horizontal distance is positive, rabbit is left of farmer.
      cout << "The rabbit is west of the farmer." << endl;
    }
    else if (horizontalLength < 0)
    {
      // If horizontal distance is negative, rabbit is right of farmer.
      cout << "The rabbit is east of the farmer." << endl;
    }
  }
}

// moveRabbit
// given the field, rabbit and farmer positions, moves the rabbit to new
// random location.
void moveRabbit(char field[][NUM_COLS], int rPosition[], int fPosition[])
{
  // Declare variables
  int max = NUM_DIRECTIONS; // Maximum number of directions available
  int min = 0;              // Minimum number of directions
  int direction;            // Holds a random direction to move to
  bool badDirection = true; // States where direction is good or bad
  int row;                  // Holds a row position
  int col;                  // Holds a column position

  // Assign rabbit current position to row and positions
  row = rPosition[0];
  col = rPosition[1];

  // Change field in 2-dimensional array from rabbit symbol to blank
  field[row][col] = ' ';

  // Seed for random function
  srand(time(NULL));
  while (badDirection == true)
  {
    // While the direction is bad
    // get a new random direction
    direction = (rand() % max + 1 - min) + min;

    //-------------------------
    // Direction (Case)
    // 1. Move North
    // 2. Move East
    // 3. Move South
    // 4. Move West
    //-------------------------
    switch (direction)
    {
    case 1: 
	if (rPosition[0] > FIRST_POS)
	{
	  // If rabbit is not on the first row,
	  // move up
	  rPosition[0]--;

	  // If rabbit and farmer are in the same position after move
	  // above, move back
	  if ((rPosition[0] == fPosition[0]) && (rPosition[1] == fPosition[1]))
	  {
	    rPosition[0]++;
	  }
	  else
	  {
	    // Else, print out message and set badDirection to false
	    cout << "The rabbit moves to another location ";
	    cout << "in search of food." << endl;
	    badDirection = false;
	  }
	}
	else
	{
	  // If rabbit is on first row, do not move
	  cout << "The rabbit nibbles on some food and does not move." << endl;
	  badDirection = false;
	}
	break;
      case 2:
	if (rPosition[1] < LAST_POS)
	{
	  // If rabbit is not on the last column,
	  // move right
	  rPosition[1]++;
	  

	  // If rabbit and farmer are in the same position after move
          // above, move back  
	  if ((rPosition[0] == fPosition[0]) && (rPosition[1] == fPosition[1]))
	  {
	    rPosition[1]--;
	  }
	  else
	  {
	    // Else, print out message and set badDirection to false
	    cout << "The rabbit moves to another location ";
	    cout << "in search of food." << endl;
	    badDirection = false;
	  }
	}
	else
        {
	  // If rabbit is on last column, do not move
          cout << "The rabbit nibbles on some food and does not move." << endl;
          badDirection = false;
        }
	break;
      case 3:
	if (rPosition[0] < LAST_POS)
	{
	  // If rabbit is not on the last row,
	  // move down
	  rPosition[0]++;
	  
	  // If rabbit and farmer are in the same position after move
          // above, move back  
	  if ((rPosition[0] == fPosition[0]) && (rPosition[1] == fPosition[1]))
	  {
	    rPosition[0]--;
	  }
	  else
	  {
	    // Else, print out message and set badDirection to false
	    cout << "The rabbit moves to another location ";
	    cout << "in search of food." << endl;
	    badDirection = false;
	  }
	}
	else
        {
	  // If rabbit is on last row, do not move
          cout << "The rabbit nibbles on some food and does not move." << endl;
          badDirection = false;
        }
	break;
      case 4:
	if (rPosition[1] > FIRST_POS)
	{
	  // If rabbit is not on the first column,
	  // move left
	  rPosition[1]--;

	  // If rabbit and farmer are in the same position after move
          // above, move back  
	  if ((rPosition[0] == fPosition[0]) && (rPosition[1] == fPosition[1]))
	  {
	    rPosition[1]++;
	  }
	  else
	  {
	    // Else, print out message and set badDirection to false
	    cout << "The rabbit moves to another location ";
	    cout << "in search of food." << endl;
	    badDirection = false;
	  }
	}
	else
        {
	  // If rabbit is on first column, do not move
          cout << "The rabbit nibbles on some food and does not move." << endl;
          badDirection = false;
        }
	break;
    }

    if(badDirection == false)
    {
      // If the direction is good, change field
      // from blank to rabbit symbol
      row = rPosition[0];
      col = rPosition[1];
      field[row][col] = RABBIT;
    }
  }
}

// moveFarmer
// Given the current farmer position and a direction,
// moves the farmer to new position if the position
// is valid and stays in the same position if not valid.
void moveFarmer(char field[][NUM_COLS], int currentPosition[], int direction)
{
  
  int row; // Holds a row position
  int col; // Holds a column position

  // Assign current farmer position to variables then
  // set position to blank space
  row = currentPosition[0];
  col = currentPosition[1];
  field[row][col] = ' ';

  //----------------------
  // Direction (case)
  // Case 1. North
  // Case 2. East
  // Case 3. South
  // Case 4. West
  //----------------------
  switch (direction)
  {
    case 1:
      if (currentPosition[0] > FIRST_POS)
      {
	// If not in the first row,
	// move up
	currentPosition[0]--;
	cout << "The farmer moves north" << endl;
      }
      else
      {
	cout << "The farmer can't leave the field" << endl;
      }
      break;
    case 2:
      if (currentPosition[1] < LAST_POS)
      {
	// If not in last column,
	// move right
	currentPosition[1]++;
	cout << "The farmer moves east" << endl;
      }
      else
      {
	cout << "The farmer can't leave the field" << endl;
      }
      break;
    case 3:
      if (currentPosition[0] < LAST_POS)
      {
	// If not in last row,
	// move down
	currentPosition[0]++;
	cout << "The farmer moves south" << endl;
      }
      else
      {
	cout << "The farmer can't leave the field" << endl;
      }
      break;
    case 4:
      if (currentPosition[1] > FIRST_POS)
      {
	// If not in first column,
	// move left
	currentPosition[1]--;
	cout << "The farmer moves west" << endl;
      }
      else
      {
	cout << "The farmer can't leave the field" << endl;
      }
      break;
  }

  // Assign new current position to variables and
  // change blank space to farmer symbol
  row = currentPosition[0];
  col =	currentPosition[1];
  field[row][col] = FARMER;
}

// getDirection
// Returns a direction given by the user
int getDirection()
{
  int direction = 0;

  cout << "What would you like to do?" << endl;
  cout << "1. Search north." << endl;
  cout << "2. Search east." << endl;
  cout << "3. Search south." << endl;
  cout << "4. Search west." << endl;

  cin >> direction;

  // while the direction entered is not valid
  while ((direction <= 0) || (direction > NUM_DIRECTIONS))
  {
      
    cout << "***Error?***" << endl;
    cout << "Please choose from one of the options below" << endl;
    cout << "1. Search north." << endl;
    cout << "2. Search east." << endl;
    cout << "3. Search south." << endl;
    cout << "4. Search west." << endl;
    
    cin.clear();
    cin >> direction;
  }

  
  return direction;
}

// initializeFarmer
// Given a 2-dimensional array and an initial position,
// Starts the farmer on a position determined by the user
void initializeFarmer(char field[][NUM_COLS], int currentPosition[])
{
  int row;    // Holds a row position
  int column; // Holds a column position

  cout << "Where would you like to start the farmer?" << endl;
  do
  {
    cin.clear();
    cout << "Enter the column(x) (0 - 9)" << endl;
    cin >> column;
  }
  while ((column < FIRST_POS) || (column > LAST_POS));

  do
  {
    cin.clear();
    cout << "Enter the row(y) (0 - 9)" << endl;
    cin >> row;
  }
  while ((row < FIRST_POS) || (row > LAST_POS));

  currentPosition[0] = row;
  currentPosition[1] = column;
  field[row][column] = FARMER;
}

// initializeRabbit
// Given a 2-dimensional array and an initial position
// positions the rabbit in a random position at the
// start of the game.
void initializeRabbit(char field[][NUM_COLS], int currentPosition[])
{
  int max = LAST_POS;
  srand(time(NULL));
  
  int row = (rand() % max);
  int col = (rand() % max);

  currentPosition[0] = row;
  currentPosition[1] = col;
  field[row][col] = RABBIT;
}

// printField
// Given a 2-dimensional array, prints out the field
// with the farmer and rabbit on it as well
void printField(char field[][NUM_COLS])
{
  cout << endl;
  cout << "| |";
  for(int i = 0; i < NUM_COLS; i++)
  {
    cout << i << '|';
  }
  for (int i = 0; i < NUM_ROWS; i++)
  {
    cout << endl << '|' << i << '|';
    for (int j = 0; j < 10; j++)
    {
      cout << field[i][j] << '|'; 
    }
  }
  cout << endl;
  
}
