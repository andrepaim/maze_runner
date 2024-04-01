#include <iostream>
#include <fstream>
#include <iostream>
#include <string>

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;


using namespace std;


int main () {
    
    system("clear\n");
    
    ifstream arquivo("maze.txt");

    // Verificando se o arquivo foi aberto corretamente
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    string linha;

    // Lendo a linha do arquivo
    if (getline(arquivo, linha)) {
        // Usando um stringstream para ler os valores da linha
        stringstream ss(linha);

        int valor1, valor2;

        // Lendo os valores da linha
        ss >> valor1 >> valor2;
    }

    else cout << "Unable to open file\n";
    
    myfile.close();    


return 0;
}
