#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

using Maze = std::vector<std::vector<char>>;

struct Position {
    int row;
    int col;
};

Maze maze;
int num_rows;
int num_cols;
std::mutex maze_mutex;  
std::atomic<bool> exit_found(false);  

void print_maze() {
    std::lock_guard<std::mutex> lock(maze_mutex);  
    std::cout << '\n';
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            std::cout << maze[i][j];
        }
        std::cout << '\n';
    }
}

Position load_maze(const std::string& file_name) {
    std::ifstream arquivoE(file_name);
    if (!arquivoE.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
        return {0, 0};
    }

    arquivoE >> num_rows >> num_cols;
    maze.resize(num_rows, std::vector<char>(num_cols));

    arquivoE.ignore();
    Position posicao_inicial = {-1, -1};  

    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            arquivoE.get(maze[i][j]);
            if (maze[i][j] == 'e') {
                posicao_inicial = {i, j};
            }
        }
        arquivoE.ignore(); 
    }

    arquivoE.close();
    return posicao_inicial;
}


bool is_valid_position(int row, int col) {
    std::lock_guard<std::mutex> lock(maze_mutex);
    return row >= 0 && row < num_rows &&
           col >= 0 && col < num_cols &&
           (maze[row][col] == 'x' || maze[row][col] == 's');
}


void walk(Position pos) {
    if (exit_found.load()) return; 

    {
        std::lock_guard<std::mutex> lock(maze_mutex);  
        if (maze[pos.row][pos.col] == 's') {
            exit_found.store(true);  
            std::cout << "Saída encontrada!\n";
            return;
        }
        maze[pos.row][pos.col] = '.';  
    }

    print_maze();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    Position direcoes[] = {
        {pos.row - 1, pos.col},  
        {pos.row + 1, pos.col}, 
        {pos.row, pos.col - 1},  
        {pos.row, pos.col + 1}   
    };

    std::vector<std::thread> threads;

    for (const Position& nova_pos : direcoes) {
        if (is_valid_position(nova_pos.row, nova_pos.col)) {
            threads.emplace_back(walk, nova_pos);  
        }
    }

    for (std::thread& t : threads) {
        if (t.joinable()) t.join();
    }
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

    std::thread t(walk, initial_pos);  
    t.join();  

    if (!exit_found) {
        std::cout << "Não foi possível encontrar a saída." << std::endl;
    }

    return 0;
}
