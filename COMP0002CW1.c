#include "graphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>



const int grid_start_x = 100;
const int grid_start_y = 100;
const int square_size = 30;
const int rowsandcolumns = 10;
// Creating a 2D array that represents the grid. It will store either a 0, 1 or 2 depending on what square a specific object is
int grid_underlay[rowsandcolumns+1][rowsandcolumns+1];



struct robot{
 int row;
 int col;
 int direction;
};

struct robot bot_pos;



void creategrid()
{
 for (int counter = 0; counter < rowsandcolumns + 1; counter++)
 {
  background();
  // Drawing the grid lines
  drawLine(grid_start_x, grid_start_x + (square_size * counter), grid_start_x + (square_size * rowsandcolumns), grid_start_x + (square_size * counter));
  drawLine(grid_start_x + (square_size * counter), grid_start_y, grid_start_x + (square_size * counter), grid_start_y + (square_size * rowsandcolumns));
 }
}



void create_redblocks(int num_total_redblocks)
{
 int num_redblocks = 0;
 srand(time(NULL));
 while (num_redblocks++ < num_total_redblocks)
 {
  setColour(red);
  // Random position generated for the red blocks
  int x = rand() % 10;
  int y = rand() % 10;

  if (grid_underlay[y][x] != 1) // Checking to see if there is already a red block in this position before drawing. Otherwise generate new value for x and y
  {
    background();
    fillRect(grid_start_x + (x * square_size), grid_start_y + (y * square_size), square_size, square_size);
    grid_underlay[y][x] = 1; // Assigns the value 1 to the position of a red block in the 2D array

  } else
  {
    num_redblocks--;
  }
 }
}



void create_marker()
{
 srand(time(NULL));
 for (int counting = 0; counting < 1; counting++)
 {
  setColour(green);
  // Random position for the marker
  int x1 = rand() % 10;
  int y1 = rand() % 10;

  if (grid_underlay[y1][x1] != 1) // Checking to see if there is a red block in this position before drawing. Otherwise re generate new points
  {
   background();
   fillRect(grid_start_x + (x1 * square_size), grid_start_y + (y1 * square_size), square_size, square_size);
   grid_underlay[y1][x1] = 2; // Assigns the value 2 to the position of the marker in the 2D array
  
  } else
  {
    counting--;
  }  
 }
}



void create_robot_pos()
{
 foreground();
 for (int attempt = 0; attempt < 1; attempt++)
 {
  int x2 = rand() % 9;
  int y2 = rand() % 9;
  int z = rand() % 4;
  // Generates random numbers for the robot's row, column and direction then assigns these values to the struct variable 'bot_pos'
  bot_pos.row = y2 + 1;
  bot_pos.col = x2 + 1;
  bot_pos.direction = z;
  // Checking if there is either a marker or a red block at the position generated. Otherwise generate new points
  if (grid_underlay[bot_pos.col][bot_pos.row] == 2 || grid_underlay[bot_pos.row][bot_pos.col] == 1) 
  {
   attempt--;
  }
 }
}



void create_robot()
{
 foreground();
 for (int counts = 0; counts < 1; counts++)
 {
  setColour(black);
  // Drawing the robot using the values assigned to the struct variable 'bot_pos' in the function create_robot_pos()
  // Drawing the robot depending on the direction its facing
  if (bot_pos.direction == 0 && grid_underlay[bot_pos.row][bot_pos.col] != 1) // 0 is North direction
  {
   int xcoordinates[] = {grid_start_x + (bot_pos.col * square_size),  grid_start_x + (bot_pos.col * square_size) + square_size,  grid_start_x + (bot_pos.col * square_size) + square_size / 2};
   int ycoordinates[] = {grid_start_y + (bot_pos.row * square_size) + square_size,  grid_start_y + (bot_pos.row * square_size) + square_size,  grid_start_y + (bot_pos.row*square_size)};
   fillPolygon(3, xcoordinates, ycoordinates);
  
  
  } else if (bot_pos.direction == 1 && grid_underlay[bot_pos.row][bot_pos.col] != 1) // 1 is East direction
  {
   int xcoordinates[] = {grid_start_x + (bot_pos.col * square_size),  grid_start_x + (bot_pos.col * square_size),  grid_start_x + (bot_pos.col * square_size) + square_size};
   int ycoordinates[] = {grid_start_y + (bot_pos.row * square_size),  grid_start_y + (bot_pos.row * square_size) + square_size,  grid_start_y + (bot_pos.row * square_size) + square_size / 2};  
   fillPolygon(3, xcoordinates, ycoordinates);  
  
  
  } else if (bot_pos.direction == 2 && grid_underlay[bot_pos.row][bot_pos.col] != 1) // 2 is South direction
  {
   int xcoordinates[] = {grid_start_x + (bot_pos.col * square_size), grid_start_x + (bot_pos.col * square_size) + square_size, grid_start_x + (bot_pos.col * square_size) + square_size / 2};
   int ycoordinates[] = {grid_start_y + (bot_pos.row * square_size), grid_start_y + (bot_pos.row * square_size), grid_start_y + (bot_pos.row * square_size) + square_size};
   fillPolygon(3, xcoordinates, ycoordinates); 
  
  
  } else if (bot_pos.direction == 3 && grid_underlay[bot_pos.row][bot_pos.col] != 1) // 3 is West direction
  {
   int xcoordinates[] = {grid_start_x + (bot_pos.col * square_size) + square_size,  grid_start_x + (bot_pos.col * square_size) + square_size,  grid_start_x + (bot_pos.col * square_size)};
   int ycoordinates[] = {grid_start_y + (bot_pos.row * square_size),  grid_start_y + (bot_pos.row * square_size) + square_size,  grid_start_y + (bot_pos.row * square_size) + square_size / 2};
   fillPolygon(3, xcoordinates, ycoordinates);
  
  } else
  {
    counts--;
  }
 }
}



int atMarker()
{
 if (grid_underlay[bot_pos.row][bot_pos.col] == 2) // Checking for number 2 in the 2D array (2 represents the marker)
 {
  return 1;
 } else
 {
  return 0;
 }
}



int canMoveForward()
{
 // Depedning on the direction the robot is facing, this function checks if the ahead square is either a redblock or the end of the grid
 if (bot_pos.direction == 0 && grid_underlay[bot_pos.row-1][bot_pos.col] != 1 && bot_pos.row != 0)
 {
  return 1;
 
 } else if (bot_pos.direction == 1 && grid_underlay[bot_pos.row][bot_pos.col+1] != 1 && bot_pos.col != 9)
 {
  return 1;
 
 } else if (bot_pos.direction == 2 && grid_underlay[bot_pos.row+1][bot_pos.col] != 1 && bot_pos.row != 9)
 {
  return 1;
 
 } else if (bot_pos.direction == 3 && grid_underlay[bot_pos.row][bot_pos.col-1] != 1 && bot_pos.col != 0)
 {
  return 1;
 
 } else
 {
  return 0;
 }
} 



void right()
{
 foreground();

 if (atMarker() == 0)
 {
  // Changing the value of the direction variable, if we turn right
  if (bot_pos.direction == 0 || bot_pos.direction == 1 || bot_pos.direction == 2)
  {
   bot_pos.direction++;
  } else
  {
   bot_pos.direction = 0; // If direction was equal to 3, then it is set equal to 0, as cant add 1
  }
 }

 clear();
 create_robot(); // This will redraw the robot with the new direction variable assigned to it. So it will be facing the desired direction
 sleep(300);
}



void left()
{
 foreground();

 if (atMarker() == 0)
 {
  if (bot_pos.direction == 1 || bot_pos.direction == 2 || bot_pos.direction == 3)
  {
   bot_pos.direction--;
  } else
  {
   bot_pos.direction = 3;
  }
 }

 clear();
 create_robot();
 sleep(300);
}



void forward()
{
 foreground();
 sleep(300);

 if (atMarker() == 0 && canMoveForward())
 {
  clear();

  if (bot_pos.direction == 0) // According to the direction, the robot will shift row/column then get redrawn
  {
   bot_pos.row--;
   create_robot(); // Redraw in new position

  } else if (bot_pos.direction == 1)
  {
   bot_pos.col++;
   create_robot();
 
  } else if (bot_pos.direction == 2)
  {
   bot_pos.row++;
   create_robot();
 
  } else if (bot_pos.direction == 3)
  {
   bot_pos.col--;
   create_robot();
  }
 }
}



int hitredblock()
{
 // Evaluating if the robot is going into a red block. Function either returns a true or false value
 if (bot_pos.direction == 0 && grid_underlay[bot_pos.row - 1][bot_pos.col] != 1)
 {
  return 0;
 
 } else if (bot_pos.direction == 1 && grid_underlay[bot_pos.row][bot_pos.col + 1] != 1)
 {
  return 0;
 
 } else if (bot_pos.direction == 2 && grid_underlay[bot_pos.row + 1][bot_pos.col] != 1)
 {
  return 0;
 
 } else if (bot_pos.direction == 3 && grid_underlay[bot_pos.row][bot_pos.col - 1] != 1)
 {
  return 0;
 
 } else
 {
  return 1;
 }
}



void bypass_redblock()
{
 // This function executes a sequence of steps that will allow the robot to navigate past a red block or a series of red blocks joined together, no matter the position
 if ((bot_pos.direction == 1 || bot_pos.direction == 3 || (bot_pos.direction == 0 && bot_pos.col == 0)) && hitredblock())
 {
  int count, counter = 0;
  while (canMoveForward() == 0)
  {
   right();
   forward();
   left();
   count++; // count helps track amount of blocks the robot has to bypass
  }
  
  forward();
  if (canMoveForward())
  {
   forward();
   left();
  }
  
  while (canMoveForward() == 0 && hitredblock()) // Whilst going round the red block(s), robot will keep moving forward until theres no block on its side
  {
   right();
   forward();
   left();
  }

  while (counter < count - 1) // Robot will move forward, until its back on the row it was originally on - before any contact with a red block
  {
   forward();
   counter++;
  }
  right();
  
 } else if (bot_pos.direction == 2 && bot_pos.col == 9 && hitredblock()) // Separate instructions for the robot whilst moving down between rows
 {
  while (canMoveForward() == 0)
  {
   right();
   forward();
   left();
  }
  forward();
  right();
   
 } else if (bot_pos.direction == 2 && bot_pos.col == 0 && hitredblock()) 
 {
  while (canMoveForward() == 0)
  {
   left();
   forward();
   right();
  }
  forward();
  left();
 }
}



void move()
{
 while (canMoveForward() == 0)
 {
  right();
 }  
 
 // Following if statement gets the robot to the top left corner, where it will start zigzagging the grid
 if (bot_pos.row != 0 && bot_pos.col != 0)
 {
  while (bot_pos.direction != 3)
  {
   left();
  }
  while (bot_pos.col != 0)
  {
   bypass_redblock();
   forward();
  }
  right();
  while (bot_pos.row != 0)
  {
   bypass_redblock();
   forward();
  }
 }


 while (bot_pos.direction != 1)
 {
  right();
 }

 
 for (int i = 0; i < rowsandcolumns; i++)
 {  
  // Both for loops, means the robot will iterate through every grid square
  for (int f = 0; f < rowsandcolumns - 1; f++)
  {
   if (canMoveForward())
   {
    forward();
    if (hitredblock())
    {
     bypass_redblock();
    }
   } else
   {
    f++; // Increment this variable as the robot has reached the end of the grid, so it should stop executing function forward() into a wall whilst going no where
   }
  }
  
  //After going across the row, the robot needs to go down 1 row, then face the correct direction. Then the for loop can iterate again
  while (bot_pos.direction != 2) 
  {
   right(); // Keep turning until facing downwards
  }
  if (hitredblock()) // If there is a red block then the robot will go around it, otherwise (else if) it will go down
  {
   bypass_redblock();
  } else if (bot_pos.direction == 2)
  {
   forward();
   right();
   bypass_redblock();
  }
  if (canMoveForward() == 0) // In the above loop, the robot goes down then turns right to get ready for the next iteration
                             // But on the left side of the grid the robot will face the wall if it turns right. So it has to do a 180 degree turn to face the correct direction
  {
   right();
   right();
   bypass_redblock();
  } 
 }
}



int main(void)
{
 setWindowSize(500, 500);
 creategrid();
 create_redblocks(3);
 create_marker();
 create_robot_pos();
 create_robot();
 atMarker();
 canMoveForward();
 move();
 return 0;
}