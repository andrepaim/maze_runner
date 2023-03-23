#include <stdio.h>
#include <stack>
#include "Maze.hpp"

maze::maze(std::string_view filepath)
{
	initial_position = load_maze(filepath.data());
}

maze::~maze()
{
}

pos_t maze::get_initial_pos()
{
	return initial_position;
}

void maze::print_maze()
{
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			printf("%c", maze_data[i][j]);
		}
		printf("\n");
	}
}

bool maze::walk(pos_t pos)
{
	// Repita até que a saída seja encontrada ou não existam mais posições não exploradas
		// Marcar a posição atual com o símbolo '.'
		// Limpa a tela
		// Imprime o labirinto

		/* Dado a posição atual, verifica quais sao as próximas posições válidas
			Checar se as posições abaixo são validas (i>0, i<num_rows, j>0, j <num_cols)
			e se são posições ainda não visitadas (ou seja, caracter 'x') e inserir
			cada uma delas no vetor valid_positions
				- pos.i, pos.j+1
				- pos.i, pos.j-1
				- pos.i+1, pos.j
				- pos.i-1, pos.j
			Caso alguma das posiçÕes validas seja igual a 's', retornar verdadeiro
		*/



		// Verifica se a pilha de posições nao esta vazia 
		//Caso não esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funçao walk com esse valor
		// Caso contrario, retornar falso
	if (!valid_positions.empty()) {
		pos_t next_position = valid_positions.top();
		valid_positions.pop();
	}
	return false;
}

pos_t maze::load_maze(const char* file_name)
{
	pos_t initial_pos;
	// Abre o arquivo para leitura (fopen)

	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols

	// Aloca a matriz maze (malloc)
	for (int i = 0; i < num_rows; ++i)
		// Aloca cada linha da matriz

		for (int i = 0; i < num_rows; ++i) {
			for (int j = 0; j < num_cols; ++j) {
				// Le o valor da linha i+1,j do arquivo e salva na posição maze[i][j]
				// Se o valor for 'e' salvar o valor em initial_pos
			}
		}
	return initial_pos;
}
