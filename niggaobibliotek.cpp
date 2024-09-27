#include <iostream>
#include <string.h>
using namespace std;

struct Livro {
	string titulo;
	string autor;
	int numPag;
	int anoPublic;
	int id;
	int qtd;
	string nomeEmprest[10];
};
bool checarID(struct Livro livros[], int &contLivros, int ID){
	bool checkID;
	for(int i = 0; i<contLivros; i++){
		if(ID==livros[i].id){
			return checkID = true;
		}
	}
	return checkID = false;
}

void printLivro(struct Livro L) {
	cout << L.titulo << endl;
	cout << L.autor << endl;
	cout << L.numPag << endl;
	cout << L.anoPublic << endl;
	cout << L.id << endl;
	cout << L.qtd << endl;
	bool temEmprestimo = false;
	for (int i = 0; i < sizeof(L.nomeEmprest) / sizeof(L.nomeEmprest[0]); i++) {
		if (L.nomeEmprest[i] != "") {
			cout << "Emprestado para: " << L.nomeEmprest[i] << endl;
			temEmprestimo = true;
		}
	}
	if (temEmprestimo == false) {
		cout<<"Esse livro ainda não foi emprestado!"<<endl;
	}
}

void cadastrarLivro(struct Livro livros[], int *contLivros) {
	struct Livro L;
	cout<<"\nDigite o titulo do livro: ";
	cin.ignore();
	getline(cin, L.titulo);
	cout<<"\nDigite o nome do autor: ";
	//cin.ignore(); estava tirando a primeira letra do nome do autor
	getline(cin, L.autor);
	cout<<"\nDigite a quantidade de páginas: ";
	cin >> L.numPag;
	cout<<"\nDigite o ano de publicação: ";
	cin >> L.anoPublic;
	cout<<"\nDigite o ID: ";
	cin >> L.id;
	while(checarID(livros, *contLivros, L.id)){
		cout<<"Id ja existente, digite outro: ";
		cin>>L.id;
	}
	cout<<"\nDigite o quantidade: ";
	cin >> L.qtd;
	while (L.qtd > 10) {
		cout<<"\nO limite de livros é 10. Digite um valor válido: ";
		cin>>L.qtd;
	}
	livros[*contLivros] = L;
	(*contLivros)++;
}

void consultarLivro(struct Livro livros[], int *contLivros) {
	int opt = 0;
	int idLivro;
	bool existeLivro = false;

	cout<<"1 - Listar todos os livros"<<endl;
	cout<<"2 - Listar livro específico"<<endl;
	cout<<"Selecione: ";
	cin>>opt;
	while(opt > 2 || opt < 1) {
		cout << "Digite uma opção existente" << endl;
		cout<<"1 - Listar todos os livros"<<endl;
		cout<<"2 - Listar livro especifico"<<endl;
		cout<<"Selecione: ";
		cin>>opt;
	}
	switch (opt)
	{
	case 1:
		if(*contLivros == 0) {
			cout << "Não existem livros cadastrados!" << endl<<endl;
			break;
		} else {
			for(int i = 0; i < *contLivros; i++) {
				printLivro(livros[i]);
			}
		}
		break;

	case 2:
		if(*contLivros == 0) {
			cout << "NC#o existem livros!" << endl<<endl;
			break;
		}
		while (existeLivro == false) {
			cout << "Digite um ID vC!lido de livro: " << endl;
			cin >> idLivro;
			for(int i = 0; i < *contLivros; i++) {
				if(livros[i].id == idLivro) {
					printLivro(livros[i]);
					existeLivro = true;
					break;
				}
			}
		}
	}
}

void emprestarLivro(struct Livro livros[], int *contLivros) {
	int idLivro;
	bool existeLivro = false;

	while (existeLivro == false) {
		cout << "Digite um ID válido de livro: ";
		cin >> idLivro;

		for (int i = 0; i < *contLivros; i++) {
			if (livros[i].id == idLivro) {
				if (livros[i].qtd > 0) {
					for (int j = 0; j < 10; j++) {
						if (livros[i].nomeEmprest[j] == "") {
							cin.ignore();
							cout << "Digite o nome da pessoa: ";
							getline(cin, livros[i].nomeEmprest[j]);
							livros[i].qtd--;
							existeLivro = true;
							cout << "Livro emprestado com sucesso!" << endl;
							break;
						}
					}
				} else {
					cout << "Não existem mais cópias disponíveis para esse livro!" << endl<<endl;
					return;
				}
			}
		}

		if (existeLivro == false) {
			cout << "ID nC#o encontrado!" << endl;
		}
	}
}

void devolverLivro(struct Livro livros[], int *contLivros) {
	int idLivro;
	bool existeLivro = false;
	string nomeDevolve;

	while(existeLivro == false) {
		cout << "Digite o id do livro: ";
		cin >> idLivro;
		for(int i = 0; i < *contLivros; i++) {
			if(livros[i].id == idLivro) {
				cout << "Digite o nome da pessoa que vai devolver: ";
				cin >> nomeDevolve;
				for(int j = 0; j < 10; j++) {
					if(livros[i].nomeEmprest[j] == nomeDevolve) {
						cout << "Livro devolvido";
						break;
					}
				}
				livros[i].qtd++;
				existeLivro = true;
				break;
			}
		}
		if(existeLivro == false) {
			cout << "Id nao encontrado: " << endl;
			cout << "Digite outro id: " << endl;
		}
	}

}

void removerLivro(struct Livro livros[], int *contLivros) {
	int ID;
	cout<<"Digite o ID do livro que deverC! ser removido: ";
	cin>>ID;
	for(int i=0; i<*contLivros; i++) {
		if(ID==livros[i].id) {
			livros[i]=livros[i+1];
			for(int j=i+1; j<*contLivros; j++) {
				if(j+1==*contLivros) {
					(*contLivros)--;
					break;
				}
				livros[j]=livros[j+1];
			}
			break;
		}
	}
	cout<<"O livro de id:"<<ID<<" foi removido"<<endl;
}

int main() {
	struct Livro livros[100];
	int contLivros = 0;
	int opt;

	do {

		cout << "1. Cadastrar Livro" << endl;
		cout << "2. Consultar Livro" << endl;
		cout << "3. Emprestar Livro" << endl;
		cout << "4. Remover Livro" << endl;
		cout << "5. Devolver Livro" << endl;
		cout << "6. Sair do programa" <<endl;
		cout << "Selecione: ";
		cin >> opt;

		switch (opt) {
		case 1:
			cadastrarLivro(livros, &contLivros);
			break;
		case 2:
			consultarLivro(livros, &contLivros);
			break;
		case 3:
			emprestarLivro(livros, &contLivros);
			break;
		case 4:
			removerLivro(livros, &contLivros);
			break;
		case 5:
		    devolverLivro(livros, &contLivros);
		    break;
		case 6:
			cout << "Programa encerrado." << endl;
			break;
		default:
			cout << "Digite uma opcao valida!" << endl;
		}

	} while (opt != 6);

	return 0;
}