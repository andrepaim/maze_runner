#ifndef MAZE_HPP
#define MAZE_HPP

#include <stdio.h>
#include <stack>
#include <string>

// Representação de uma posição
struct pos_t {
    size_t i;
    size_t j;
};

class maze
{
public:
    maze(std::string_view filepath);
    ~maze();

    pos_t get_initial_pos();
    void print_maze();
    bool walk(pos_t pos);
private:

    pos_t load_maze(const char* file_name);

    // Matriz de char representnado o labirinto
    char** maze_data; // Voce também pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

    // Numero de linhas e colunas do labirinto
    size_t num_rows;
    size_t num_cols;

    std::stack<pos_t> valid_positions;
    pos_t initial_position;
    /* data */
};

#endif //MAZE_HPP
