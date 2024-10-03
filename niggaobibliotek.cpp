#include <iostream>
#include <string.h>
#include <locale.h>
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

bool checarID(struct Livro livros[], int *contLivros, int ID, int *pos){
	bool checkID;
	for(int i = 0; i<*contLivros; i++){
		if(ID==livros[i].id){
			*pos=i;
			return checkID = true;
		}
	}
	return checkID = false;
}

void printLivro(struct Livro L) {
	cout << "Título: " << L.titulo << endl;
	cout << "Autor: " << L.autor << endl;
	cout << "Número de Páginas: " << L.numPag << endl;
	cout << "Ano de Publicação: " << L.anoPublic << endl;
	cout << "ID: " << L.id << endl;
	cout << "Quantidade Disponível: " << L.qtd << endl;

	bool temEmprestimo = false;
	cout << "Emprestado para: ";
	for (int i = 0; i < sizeof(L.nomeEmprest) / sizeof(L.nomeEmprest[0]); i++) {
		if (L.nomeEmprest[i] != "") {
			cout << L.nomeEmprest[i] << " / ";
			temEmprestimo = true;
		}
	}
	cout << endl << endl ;
	if (temEmprestimo == false) {
		cout<<"Esse livro ainda não foi emprestado!"<<endl;
	}
}

void cadastrarLivro(struct Livro livros[], int *contLivros) {
	struct Livro L;
	int p;
	cout<<"\nDigite o titulo do livro: ";
	cin.ignore();
	getline(cin, L.titulo);
	cout<<"\nDigite o nome do autor: ";
	getline(cin, L.autor);
	cout<<"\nDigite a quantidade de páginas: ";
	cin >> L.numPag;
	cout<<"\nDigite o ano de publicação: ";
	cin >> L.anoPublic;
	cout<<"\nDigite o ID: ";
	cin >> L.id;
	while(checarID(livros, contLivros, L.id, &p)){
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
			cout << "Não existem livros cadastrados!" << endl<<endl;
			break;
		}
		while (existeLivro == false) {
			cout << "Digite um ID válido de livro: " << endl;
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
	int idLivro, pos;

	cout << "Digite um ID de livro: ";
    cin >> idLivro;

	while (!checarID(livros , contLivros, idLivro, &pos)) {
        cout << "Id não encontrado.\nDigite novamente: ";
        cin >> idLivro;
	}

		for (int i = 0; i < *contLivros; i++) {
			if (livros[i].id == idLivro) {
				if (livros[i].qtd > 0) {
					for (int j = 0; j < 10; j++) {
						if (livros[i].nomeEmprest[j] == "") {
							cin.ignore();
							cout << "Digite o nome da pessoa: ";
							getline(cin, livros[i].nomeEmprest[j]);
							livros[i].qtd--;
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
	}


void devolverLivro(struct Livro livros[], int *contLivros) {
	int idLivro, pos;
	string nomeDevolve;
	bool existePessoa = false;
	cout << "Digite o ID do livro: ";
    cin >> idLivro;
	while(!checarID(livros, contLivros, idLivro, &pos)){
       cout<<"Id não encontrado.\nDigite novamente: ";
       cin>>idLivro;
	}
    for(int i = 0; i < *contLivros; i++) {
        if(livros[i].id == idLivro) {
            cout << "Digite o nome da pessoa que vai devolver: ";
            cin >> nomeDevolve;
            for(int j = 0; j < 10; j++) {
                if(livros[i].nomeEmprest[j] == nomeDevolve) {
                    cout << "Livro devolvido!"<<endl<<endl;
                    for (int x = 0; x < 10; x++) {
                        livros[i].nomeEmprest[j] = "";
                        existePessoa = true;
                    }
                    break;
                }
            }
            while (existePessoa == false) {
                cout<<"Essa pessoa não está com o livro selecionado!\nDigite novamente: "<<endl;
                cin>>nomeDevolve;
                for(int j = 0; j < 10; j++) {
                    if(livros[i].nomeEmprest[j] == nomeDevolve) {
						existePessoa = true;
					}}
            }
            livros[i].qtd++;
            break;
        }
	}
}

void removerLivro(struct Livro livros[], int *contLivros) {
	int ID, pos;
	cout<<"Digite o ID do livro que deverC! ser removido: ";
	cin>>ID;
	while(!checarID(livros , contLivros, ID, &pos)){
		cout<<"Id não encontrado, digite outro: ";
		cin>>ID;
	}

	if(*contLivros==1){
		livros = NULL;
		(*contLivros)--;
	}
	else if(pos+1==*contLivros){
		struct Livro livrosNovo[*contLivros-1];
		for(int i = 0; i<*contLivros-1; i++){
			livrosNovo[i]=livros[i];
		}
		for(int i = 0; i<*contLivros-1; i++){
			livros[i]=livrosNovo[i];
		}
		(*contLivros)--;
	}
	else{
		struct Livro aux[*contLivros-1];
		for(int i=0; i<*contLivros; i++) {
			if(ID==livros[i].id){
				for(int j=i; j<*contLivros; j++){
					livros[j]=livros[j+1];
				}
			}
		}
		(*contLivros)--;
	}
	cout<<"O livro de id:"<<ID<<" foi removido"<<endl;

}

int main() {
    setlocale(LC_ALL, "Portuguese");
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
