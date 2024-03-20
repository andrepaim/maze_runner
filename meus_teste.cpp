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

/*
int main()
{
                  ifstream is;
                  is.open ("texto.txt", ios::in);

                  return 0;
}

std::ifstream file(str);
      if( file.is_open() ){
        std::getline(file, this->title);

*/



int main () {
    
    system("clear\n");

    string line;
    ifstream myfile ("maze.txt"); // ifstream = padrão ios:in
    
    if (myfile.is_open()){
        while (! myfile.eof() ) //enquanto end of file for false continua
        {
            getline (myfile,line); // como foi aberto em modo texto(padrão) //e não binário(ios::bin) pega cada linha
            cout << line.size() << endl;
            cout << line << endl;
            
        }
    }
    else cout << "Unable to open file\n";
    
    myfile.close();    


return 0;
}
