#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>    
#include <cstdlib>

// Matriz de char representando o labirinto
char** maze;

// Número de linhas e colunas do labirinto
int num_rows;
int num_cols;

// Representação de uma posição
struct pos_t {
    int i;
    int j;
};

// Estrutura de dados contendo as próximas posições a serem exploradas no labirinto
std::stack<pos_t> valid_positions;

// Função que lê o labirinto de um arquivo texto, carrega em memória e retorna a posição inicial
pos_t load_maze(const char* file_name) {
    pos_t initial_pos;

    // Abre o arquivo para leitura
    FILE *file = fopen(file_name, "r");
    if (file == nullptr) {
        printf("Erro ao abrir o arquivo.\n");
        //exit(EXIT_FAILURE);
      exit(1);
    }

    // Lê o número de linhas e colunas
    fscanf(file, "%d %d", &num_rows, &num_cols);

    // Aloca a matriz maze
    maze = (char**)malloc(num_rows * sizeof(char*));
    for (int i = 0; i < num_rows; ++i) {
        maze[i] = (char*)malloc(num_cols * sizeof(char));
    }

    // Lê o labirinto do arquivo
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            fscanf(file, " %c", &maze[i][j]);
            if (maze[i][j] == 'e') {
                initial_pos.i = i;
                initial_pos.j = j;
            }
        }
    }

    fclose(file);
    return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

// Função responsável pela navegação
bool walk(pos_t pos) {
    while (true) {
        maze[pos.i][pos.j] = '.'; // Marca a posição atual com o símbolo '.'

        // Limpa a tela (funciona em sistemas Unix)
        printf("\033[H\033[J");

        // Imprime o labirinto
        print_maze();

        // Verifica se a posição atual é a saída
        if (maze[pos.i][pos.j] == 's') {
            return true;
        }

        // Verifica as próximas posições válidas e as adiciona à pilha
        if (pos.i > 0 && maze[pos.i - 1][pos.j] == 'x') {
            pos_t next_pos = {pos.i - 1, pos.j};
            valid_positions.push(next_pos);
        }
        if (pos.i < num_rows - 1 && maze[pos.i + 1][pos.j] == 'x') {
            pos_t next_pos = {pos.i + 1, pos.j};
            valid_positions.push(next_pos);
        }
        if (pos.j > 0 && maze[pos.i][pos.j - 1] == 'x') {
            pos_t next_pos = {pos.i, pos.j - 1};
            valid_positions.push(next_pos);
        }
        if (pos.j < num_cols - 1 && maze[pos.i][pos.j + 1] == 'x') {
            pos_t next_pos = {pos.i, pos.j + 1};
            valid_positions.push(next_pos);
        }

        // Verifica se a pilha de posições não está vazia
        if (!valid_positions.empty()) {
            pos = valid_positions.top();
            valid_positions.pop();
        } else {
            return false;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_labirinto>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Carregar o labirinto com o nome do arquivo recebido como argumento
    pos_t initial_pos = load_maze(argv[1]);

    // Chamar a função de navegação
    bool exit_found = walk(initial_pos);

    // Tratar o retorno
    if (exit_found) {
        printf("Saída encontrada!\n");
    } else {
        printf("Não há saída neste labirinto.\n");
    }

    return EXIT_SUCCESS;
}
