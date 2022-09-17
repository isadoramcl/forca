#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib> // pega numeros aleatorios

using namespace std;

string palavra_secreta;
map <char,bool> chutou;
vector <char> chutes_errados;//vetor dinamico(não precisa definir o tamanho)

bool letra_existe (char chute){
	for (char letra : palavra_secreta){//se erro, ver vídeo 5
		if (chute == letra){
		return true;	
		}
	}
	return false;
}

bool nao_acertou (){
	for (char letra : palavra_secreta){
		if (!chutou [letra]){
			return true;
		}
	}
	return false; //como se fosse um else
}

bool nao_enforcou(){
	return chutes_errados.size() < 5; //retorna um bool
}

void titulo (){
	cout <<"***************************"<< endl;
	cout <<"***********FORCA***********"<< endl;
	cout <<"***************************\n"<< endl;
}

void imprime_palavra (){
		cout << "Chute uma letra" << endl;
		for(char letra : palavra_secreta){
			if (chutou [letra]){//confere a chave no mapa
				cout<< letra <<" ";
			}else{
				cout << "_ ";
			}
		}
		cout << "\n";
}

void imprime_erros (){
		cout << "Chutes errados: ";
		for(char letra: chutes_errados){
			cout << letra << " ";
		}
		cout << endl;
}

void chuta (){
	char chute;
		cin >> chute;
		//altera o valor no map que o chute é verdadeiro
		chutou [chute] = chute;


		if (letra_existe (chute)){
			cout << "Você acertou!"<< endl;
		}else{
			cout << "Você errou!"<< endl;
			chutes_errados.push_back(chute); //adiciona a letra errada no fim do vector
		}
}

vector <string> le_arquivo(){
	ifstream arquivo;
	arquivo.open ("palavras.txt");
	vector <string> palavras_do_arquivo;

	if (arquivo.is_open()){
		int quantidade_de_palavras;
		arquivo >> quantidade_de_palavras;

		for (int i = 0; i < quantidade_de_palavras; i++){
			string palavra_lida;
			arquivo >> palavra_lida;
			palavras_do_arquivo.push_back(palavra_lida);
		}	
	}else{
		cout << "Não foi possível acessar o arquivo."<< endl;
		exit (0);
	}

	arquivo.close();

	return palavras_do_arquivo; //retorna o vector
}

void sorteia_palavra (){
	vector <string> frutas = le_arquivo();
	srand (time(NULL));	
	int indice_sorteado = rand() % frutas.size();
	palavra_secreta = frutas [indice_sorteado];
}

void salva_arquivo(vector <string> nova_lista){
	ofstream arquivo;
	arquivo.open ("palavras.txt");

	if(arquivo.is_open()){
		arquivo << nova_lista.size() <<endl;
		
		for (string palavra : nova_lista){
			arquivo << palavra << endl;
		}	
			arquivo.close();
	}else{
		cout << "Não foi possível acessar o banco de palavras"<< endl;
		exit (0);
	}

}

void adiciona_palavra(){
	string nova_palavra;
	cout << "Escreva a palavra com letras maiúsculas:";
	cin >> nova_palavra;

	vector <string> frutas = le_arquivo();
	frutas.push_back(nova_palavra);

	salva_arquivo (frutas);

}

int main() {

	titulo ();
	le_arquivo();
	sorteia_palavra();

	while(nao_acertou () && nao_enforcou ()){
		imprime_palavra ();
		imprime_erros ();
		chuta();
	}

	cout << "Fim de jogo!" << endl;

	if (!nao_acertou()){
		char resposta;
		cout << "Você ganhou! Quer adicionar uma nova palavra a lista?" << endl;
		cin >> resposta;
		if (resposta == 'S'){
			adiciona_palavra();
		}else{
			cout << "Até o próximo jogo.";
		}
	}else{
		cout << "Você perdeu!" <<endl;
	}
	
}