#include "Maze.hpp"

int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
	maze maze_var(argv[1]);

	pos_t initial_pos = maze_var.get_initial_pos();
	// chamar a função de navegação
	bool exit_found = maze_var.walk(initial_pos);

	// Tratar o retorno (imprimir mensagem)

	return 0;
}
