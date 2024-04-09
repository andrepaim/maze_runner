/*Este código agora deve funcionar corretamente para carregar um
labirinto a partir de um arquivo de texto, imprimir o labirinto,
e navegar através dele em busca da saída. 
Certifique-se de ter um arquivo de labirinto no formato 
adequado para testar o código.
*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

using namespace std;

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

// Função que carrega o labirinto a partir de um arquivo de texto
pos_t load_maze(const char* file_name) {
    pos_t initial_pos;
    ifstream file(file_name);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        exit(1);
    }

    file >> num_rows >> num_cols;
    maze = new char*[num_rows];
    for (int i = 0; i < num_rows; ++i) {
        maze[i] = new char[num_cols];
        for (int j = 0; j < num_cols; ++j) {
            file >> maze[i][j];
            if (maze[i][j] == 'e') {
                initial_pos.i = i;
                initial_pos.j = j;
            }
        }
    }

    file.close();
    return initial_pos;
}

// Função que imprime o labirinto
void print_maze() {
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

// Função responsável pela navegação no labirinto
bool walk(pos_t pos) {
    stack<pos_t> valid_positions;
    valid_positions.push(pos);

    while (!valid_positions.empty()) {
        pos = valid_positions.top();
        valid_positions.pop();

        // Verifica se a posição atual é a saída
        if (maze[pos.i][pos.j] == 's') {
            cout << "Saída encontrada!" << endl;
            return true;
        }

        // Marca a posição atual como visitada
        maze[pos.i][pos.j] = '.';

        // Verifica posições adjacentes válidas
        if (pos.i > 0 && maze[pos.i - 1][pos.j] != 'x') {
            valid_positions.push({pos.i - 1, pos.j});
        }
        if (pos.i < num_rows - 1 && maze[pos.i + 1][pos.j] != 'x') {
            valid_positions.push({pos.i + 1, pos.j});
        }
        if (pos.j > 0 && maze[pos.i][pos.j - 1] != 'x') {
            valid_positions.push({pos.i, pos.j - 1});
        }
        if (pos.j < num_cols - 1 && maze[pos.i][pos.j + 1] != 'x') {
            valid_positions.push({pos.i, pos.j + 1});
        }
    }

    cout << "Saída não encontrada." << endl;
    return false;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <nome_arquivo>" << endl;
        return 1;
    }

    pos_t initial_pos = load_maze("maze.txt");
    print_maze();

    bool exit_found = walk(initial_pos);

    return 0;
}



