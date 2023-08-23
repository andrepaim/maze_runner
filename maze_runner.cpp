#include <stdio.h>
#include <stack>
#include <iostream>

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

bool is_valid(pos_t pos)
{
  if (pos.i < 0 || pos.i > num_rows || pos.j < 0 || pos.j > num_cols)
  {
    return false;
  }
  if (maze[pos.i][pos.j] == '#' || maze[pos.i][pos.j] == '.')
  {
    return false;
  }
  return true;
}

void add_valid_position(pos_t pos)
{
  if (is_valid(pos))
  {
    valid_positions.push(pos);
  }
}

pos_t load_maze(const char *file_name)
{
  pos_t initial_pos;
  FILE *file = fopen(file_name, "r");

  char linha[100], coluna[10];
  fscanf(file, "%s %s", linha, coluna);

  num_rows = atoi(linha);
  num_cols = atoi(coluna);

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

void print_maze()
{
  for (int i = 0; i < num_rows; ++i)
  {
    for (int j = 0; j < num_cols; ++j)
    {
      printf("%c", maze[i][j]);
    }
    printf("\n");
  }
}

bool walk(pos_t pos)
{
  system("clear");
  print_maze();

  if (maze[pos.i][pos.j] == 's')
  {
    return true;
  }
  maze[pos.i][pos.j] = '.';

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

  pos_t initial_pos = load_maze("./maze4.txt");

  bool exit_found = walk(initial_pos);

  if (exit_found)
  {
    printf("Saida encontrada!\n");
  }
  else
  {
    printf("Saida nao encontrada!\n");
  }

  return 0;
}
