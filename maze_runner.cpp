#include <stdio.h>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <iostream>


// Matriz de char representnado o labirinto
char** maze; // Voce tambÃ©m pode representar o labirinto como um vetor de vetores de char (vector<vector<char>>)

// Numero de linhas e colunas do labirinto
int num_rows;
int num_cols;

// RepresentaÃ§Ã£o de uma posiÃ§Ã£o
struct pos_t {
	int i;
	int j;
};

// Estrutura de dados contendo as prÃ³ximas
// posicÃµes a serem exploradas no labirinto
std::stack<pos_t> valid_positions;
/* Inserir elemento: 

	 pos_t pos;
	 pos.i = 1;
	 pos.j = 3;
	 valid_positions.push(pos)
 */
// Retornar o numero de elementos: 
//    valid_positions.size();
// 
// Retornar o elemento no topo: 
//  valid_positions.top(); 
// 
// Remover o primeiro elemento do vetor: 
//    valid_positions.pop();


// FunÃ§Ã£o que le o labirinto de um arquivo texto, carrega em 
// memÃ³ria e retorna a posiÃ§Ã£o inicial
pos_t load_maze(const char* file_name) {
	pos_t initial_pos;
	// Abre o arquivo para leitura (fopen)
	FILE* file = fopen(file_name, "r");

	
	if (file == nullptr) {
		std::cout << "Erro ao abrir o arquivo!" << std::endl;
        	initial_pos.i = -1;
        	initial_pos.j = -1;
		return initial_pos;
	}

	// Le o numero de linhas e colunas (fscanf) 
	// e salva em num_rows e num_cols
	
	fscanf(file,"%d", &num_rows);
	fscanf(file,"%d", &num_cols);

	// Aloca a matriz maze (malloc)
	maze = (char**)malloc(num_rows*sizeof(char*));
	for (int i = 0; i < num_rows; ++i) {
		maze[i] = (char*)malloc(num_cols*sizeof(char));
		// Aloca cada linha da matriz
	}

	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			// Le o valor da linha i+1,j do arquivo e salva na posiÃ§Ã£o maze[i][j]
			// Se o valor for 'e' salvar o valor em initial_pos
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

// FunÃ§Ã£o que imprime o labirinto
void print_maze() {
	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_cols; ++j) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}


// FunÃ§Ã£o responsÃ¡vel pela navegaÃ§Ã£o.
// Recebe como entrada a posiÃ§Ã£o initial e retorna um booleando indicando se a saÃ­da foi encontrada
 bool walk(pos_t pos) {
	
	// Repita atÃ© que a saÃ­da seja encontrada ou nÃ£o existam mais posiÃ§Ãµes nÃ£o exploradas
		// Marcar a posiÃ§Ã£o atual com o sÃ­mbolo '.'
		// Limpa a tela
		// Imprime o labirinto

	int i = pos.i;
	int j = pos.j;

	
	if(maze[i][j] == 's'){
		return true;
	}

	
	if (maze[i][j] != 'e'){
	maze[i][j] = '.';
	}

	
	
	system("clear");
	print_maze(); 
		
		/* Dado a posiÃ§Ã£o atual, verifica quais sao as prÃ³ximas posiÃ§Ãµes vÃ¡lidas
			Checar se as posiÃ§Ãµes abaixo sÃ£o validas (i>0, i<num_rows, j>0, j <num_cols)
		 	e se sÃ£o posiÃ§Ãµes ainda nÃ£o visitadas (ou seja, caracter 'x') e inserir
		 	cada uma delas no vetor valid_positions
		 		- pos.i, pos.j+1
		 		- pos.i, pos.j-1
		 		- pos.i+1, pos.j
		 		- pos.i-1, pos.j
		 	Caso alguma das posiÃ§Ã•es validas seja igual a 's', retornar verdadeiro
	 	*/


	
	 if(i < (num_rows-1)){ // movimento vertical pra baixo

		if (maze[i+1][j] == 's'){ // verifica se a saida esta abaixo
			return true;
	}
	
		else if ( maze[i+1][j] == 'x'){
			// inserir a posicao [i+1] [j] na pilha 
			pos_t posicao_empilhada = pos;
			posicao_empilhada.i = posicao_empilhada.i+1;
			valid_positions.push(posicao_empilhada);
		
	  }
	}


	if(i > 0){ // movimento vertical pra cima

		if ( maze[i-1][j] == 's'){ // verifica a se a saida esta acima
			return true;
	}
		else if ( maze[i-1][j] == 'x'){
		// inserir a posicao [i-1] [j] na pilha 
			pos_t posicao_empilhada = pos;
			posicao_empilhada.i = posicao_empilhada.i-1;
			valid_positions.push(posicao_empilhada);
	  }}
		
		
		//pos.i = i-1;
		//valid_positions.push(pos);	
		//pos.i = i+1;


	if(j < (num_cols-1)){ // movimento horizontal pra direita

		if (maze[i][j+1] == 's'){ // verifica se a saida esta a direita
			return true;
		}
	  
		else if ( maze[i][j+1] == 'x'){
		// inserir a posicao [i] [j+1] na pilha 

			pos_t posicao_empilhada = pos;
			posicao_empilhada.j = posicao_empilhada.j+1;
			valid_positions.push(posicao_empilhada);
			
		}
	}
		
		
		//pos.j = j+1;
		//valid_positions.push(pos);
		//pos.j = j-1;
		
		

	if(j > 0){ // movimento horizontal pra esquerda

		if (maze[i][j-1] == 's'){ // verifica se a saida esta a esquerda
			return true;
	}

		else if (maze[i][j-1] == 'x'){
		// inserir a posicao [i] [j-1] na pilha 
		
		pos_t posicao_empilhada = pos;
		posicao_empilhada.j = posicao_empilhada.j-1;
		valid_positions.push(posicao_empilhada);
		}
	}
		
		
		//pos.j = j-1;
		//valid_positions.push(pos);
		//pos.j = j+1;
	

		// Verifica se a pilha de posiÃ§Ãµes nao esta vazia 
		//Caso nÃ£o esteja, pegar o primeiro valor de  valid_positions, remove-lo e chamar a funÃ§ao walk com esse valor
		// Caso contrario, retornar falso
	if (!valid_positions.empty()) {
			pos_t next_position = valid_positions.top();
			valid_positions.pop();
			return walk(next_position);
	}
	return false;
}


int main(int argc, char* argv[]) {
	// carregar o labirinto com o nome do arquivo recebido como argumento
	pos_t initial_pos = load_maze(argv[1]);
	

	// chamar a funÃ§Ã£o de navegaÃ§Ã£o
	bool exit_found = walk(initial_pos);
	
	
		// Tratar o retorno (imprimir mensagem)
	if(exit_found == true) {
		std::cout << "existe saida" << std::endl;
	}
	else{
		std::cout << "nao existe saida" << std::endl;
	}

	
	return 0;
}
