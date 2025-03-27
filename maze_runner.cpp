
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>
#include <cstdlib>

// Representação do labirinto
using Maze = std::vector<std::vector<char>>;

// Estrutura para representar uma posição no labirinto
struct Position {
    int row;
    int col;
};

// Variáveis globais
Maze maze;
int num_rows;
int num_cols;
std::stack<Position> valid_positions;

// Função para carregar o labirinto de um arquivo
Position load_maze(const std::string& file_name) {
    std::ifstream file(file_name);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return {-1, -1};
    }
    
    file >> num_rows >> num_cols;
    maze.resize(num_rows, std::vector<char>(num_cols));
    
    Position start = {-1, -1};
    
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            file >> maze[i][j];
            if (maze[i][j] == 'e') {
                start = {i, j};
            }
        }
    }
    
    file.close();
    return start;
}

// Função para limpar a tela
void clear_screen() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

// Função para imprimir o labirinto
void print_maze() {
    clear_screen();
    for (const auto& row : maze) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "\n";
}

// Função para verificar se uma posição é válida
bool is_valid_position(int row, int col) {
    return (row >= 0 && row < num_rows && col >= 0 && col < num_cols && (maze[row][col] == 'x' || maze[row][col] == 's'));
}

// Função principal para navegar pelo labirinto
bool walk(Position pos) {
    if (maze[pos.row][pos.col] == 's') {
        return true; // Saída encontrada
    }
    
    maze[pos.row][pos.col] = 'o';
    print_maze();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    maze[pos.row][pos.col] = '.';
    
    Position directions[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    for (auto& dir : directions) {
        int new_row = pos.row + dir.row;
        int new_col = pos.col + dir.col;
        
        if (is_valid_position(new_row, new_col)) {
            if (walk({new_row, new_col})) {
                return true;
            }
        }
    }
    
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_labirinto>" << std::endl;
        return 1;
    }

    Position initial_pos = load_maze(argv[1]);
    if (initial_pos.row == -1 || initial_pos.col == -1) {
        std::cerr << "Posição inicial não encontrada no labirinto." << std::endl;
        return 1;
    }

    bool exit_found = walk(initial_pos);

    if (exit_found) {
        std::cout << "Saída encontrada!" << std::endl;
    } else {
        std::cout << "Não foi possível encontrar a saída." << std::endl;
    }

    return 0;
}
