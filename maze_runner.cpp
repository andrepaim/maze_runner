#include <stack>
#include <iostream>
#include <unistd.h>

using namespace std;

char **maze;

int num_rows;
int num_cols;

struct pos_t
{
  int i;
  int j;
};

stack<pos_t> valid_positions;

/**
 * The function checks if a given position is valid in a maze by ensuring it is
 * within the maze boundaries and not blocked by walls or obstacles.
 * 
 * @param pos The parameter `pos` is of type `pos_t`, which is likely a custom
 * struct or class representing a position in a maze. It likely has two members
 * `i` and `j`, representing the row and column indices respectively.
 * 
 * @return The function is_valid() returns a boolean value. It returns true if the
 * given position (pos) is valid, and false otherwise.
 */

bool is_valid(pos_t pos)
{
  if (pos.i < 0 || pos.i >= num_rows || pos.j < 0 || pos.j >= num_cols)
  {
    return false;
  }
  if (maze[pos.i][pos.j] == '#' || maze[pos.i][pos.j] == 'o')
  {
    return false;
  }
  return true;
}

/**
 * The function adds a valid position to a collection of valid positions if the
 * position is valid.
 * 
 * @param pos The parameter "pos" is of type "pos_t", which is likely a custom
 * data type representing a position.
 */

void add_valid_position(pos_t pos)
{
  if (is_valid(pos))
  {
    valid_positions.push(pos);
  }
}

/**
 * The function "load_maze" reads a maze from a file and returns the initial
 * position of the player.
 * 
 * @param file_name A string representing the name of the file containing the maze
 * data.
 * 
 * @return a variable of type `pos_t`, which represents the initial position in
 * the maze.
 */

pos_t load_maze(const char *file_name)
{
  pos_t initial_pos;
  FILE *file = fopen(file_name, "r");

  fscanf(file, "%d %d", &num_rows, &num_cols);

  maze = (char **)malloc(num_rows * sizeof(char *));
  for (int i = 0; i < num_rows; ++i)
  {
    maze[i] = (char *)malloc(num_cols * sizeof(char));
  }

  for (int i = 0; i < num_rows; ++i)
  {
    for (int j = 0; j < num_cols; ++j)
    {
      fscanf(file, " %c", &maze[i][j]);
      if (maze[i][j] == 'e')
      {
        initial_pos.i = i;
        initial_pos.j = j;
      }
    }
  }

  return initial_pos;
}

/**
 * The function `print_maze` prints a maze, highlighting certain characters based
 * on whether they have been found or not.
 * 
 * @param isFound The parameter `isFound` is a boolean variable that indicates
 * whether the maze has been solved or not. If `isFound` is true, it means the
 * maze has been solved and the path to the exit has been found. If `isFound` is
 * false, it means the maze has not
 */

void print_maze(bool isFound)
{
  for (int i = 0; i < num_rows; ++i)
  {
    for (int j = 0; j < num_cols; ++j)
    {
      if (isFound && (maze[i][j] == 'o' || maze[i][j] == 's')) printf("\033[1;32m%c\033[0m", maze[i][j]);
      else if (isFound && maze[i][j] == '#') printf("\033[31m%c\033[0m", maze[i][j]);
      else
      {
        if (maze[i][j] == 'o') printf("\033[31m%c\033[0m", maze[i][j]);
        else printf("%c", maze[i][j]);
      }
    }
    printf("\n");
  }
}

/**
 * The function "walk" recursively explores a maze, marking visited positions with
 * 'o' and returning true if it reaches the goal position 's'.
 * 
 * @param pos The parameter `pos` is of type `pos_t`, which represents a position
 * in the maze. It has two members: `i` and `j`, which represent the row and
 * column indices of the position in the maze, respectively.
 * 
 * @return a boolean value.
 */

bool walk(pos_t pos)
{
  system("clear");
  print_maze(false);
  usleep(10000);

  if (maze[pos.i][pos.j] == 's')
  {
    system("clear");
    print_maze(true);
    return true;
  }
  maze[pos.i][pos.j] = 'o';

  pos_t new_pos;

  new_pos.i = pos.i - 1;
  new_pos.j = pos.j;
  add_valid_position(new_pos);

  new_pos.i = pos.i + 1;
  new_pos.j = pos.j;
  add_valid_position(new_pos);

  new_pos.i = pos.i;
  new_pos.j = pos.j - 1;
  add_valid_position(new_pos);

  new_pos.i = pos.i;
  new_pos.j = pos.j + 1;
  add_valid_position(new_pos);

  if (valid_positions.empty())
  {
    return false;
  }

  pos_t next_pos = valid_positions.top();
  valid_positions.pop();

  return walk(next_pos);
}

int main(int argc, char *argv[])
{

  pos_t initial_pos = load_maze(argv[1]);

  bool exit_found = walk(initial_pos);

  if (exit_found)
  {
    printf("Exit found!\n");
  }
  else
  {
    printf("Exit not found!\n");
  }

  return 0;
}
