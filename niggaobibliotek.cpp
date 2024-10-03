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
void linha(){
	cout<<"|";
	for(int i=0; i<100; i++){
		cout<<"-";
	}
	cout<<"|\n";
}
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
	string nomes[10];
	linha();
	cout << "|T¡tulo: " << L.titulo << endl;
	cout << "|Autor: " << L.autor << endl;
	cout << "|N£mero de P ginas: " << L.numPag << endl;
	cout << "|Ano de Publica‡Æo: " << L.anoPublic << endl;
	cout << "|ID: " << L.id << endl;
	cout << "|Quantidade Dispon¡vel: " << L.qtd << endl;

	bool temEmprestimo = false;
	for (int i = 0; i < sizeof(L.nomeEmprest) / sizeof(L.nomeEmprest[0]); i++) {
		if (L.nomeEmprest[i] != "") {
			nomes[i]=L.nomeEmprest[i];
			temEmprestimo = true;
		}
	}
	if(temEmprestimo == true){
		cout << "|Emprestado para: ";
		for (int i = 0; i < sizeof(nomes) / sizeof(nomes[0]); i++) {
			if (nomes[i] != ""){
			cout<<nomes[i]<<" | ";
			}
		}
	}
	if (temEmprestimo == false) {
		cout<<"|Esse livro ainda nÆo foi emprestado!"<<endl;
	}
	cout<<"\n";
}

void cadastrarLivro(struct Livro livros[], int *contLivros) {
	struct Livro L;
	int p;
	cout<<"|Digite o titulo do livro: ";
	cin.ignore();
	getline(cin, L.titulo);
	cout<<"|Digite o nome do autor: ";
	getline(cin, L.autor);
	cout<<"|Digite a quantidade de p ginas: ";
	cin >> L.numPag;
	cout<<"|Digite o ano de publica‡Æo: ";
	cin >> L.anoPublic;
	cout<<"|Digite o ID: ";
	cin >> L.id;
	while(checarID(livros, contLivros, L.id, &p)){
		cout<<"|Id ja existente, digite outro: ";
		cin>>L.id;
	}
	cout<<"|Digite o quantidade: ";
	cin >> L.qtd;
	while (L.qtd > 10) {
		cout<<"|O limite de livros ‚ 10. Digite um valor v lido: ";
		cin>>L.qtd;
	}
	livros[*contLivros] = L;
	(*contLivros)++;
	cout<<"|Livro cadastrado com sucesso!"<<endl;
}

void consultarLivro(struct Livro livros[], int *contLivros) {
	int opt = 0, pos;
	int idLivro;
	bool existeLivro = false;

	cout<<"|1 - Listar todos os livros"<<endl;
	cout<<"|2 - Listar livro espec¡fico"<<endl;
	cout<<"|Selecione: ";
	cin>>opt;
	while(opt > 2 || opt < 1) {
		cout<<"|Digite uma op‡Æo existente" << endl;
		cout<<"|1 - Listar todos os livros"<<endl;
		cout<<"|2 - Listar livro especifico"<<endl;
		cout<<"|Selecione: ";
		cin>>opt;
	}
	switch (opt)
	{
	case 1:
		if(*contLivros == 0) {
			cout << "|NÆo existem livros cadastrados!" << endl<<endl;
			break;
		} else {
			for(int i = 0; i < *contLivros; i++) {
				printLivro(livros[i]);
			}
		}
		break;

	case 2:
		if(*contLivros == 0) {
			cout << "|NÆo existem livros cadastrados!" << endl<<endl;
			break;
		}
		cout << "|Digite um ID de livro: ";
		cin >> idLivro;
		while (!checarID(livros, contLivros, idLivro, &pos)) {
			cout << "|Id nÆo encontrado.\n|Digite novamente: ";
        	cin >> idLivro;
		}
		for(int i = 0; i < *contLivros; i++) {
			if(livros[i].id == idLivro) {
				printLivro(livros[i]);
				break;
			}
		}
	}

}


void emprestarLivro(struct Livro livros[], int *contLivros) {
	int idLivro, pos;

	cout << "|Digite um ID de livro: ";
    cin >> idLivro;

	while (!checarID(livros , contLivros, idLivro, &pos)) {
        cout << "|Id nÆo encontrado.\n|Digite novamente: ";
        cin >> idLivro;
	}

	for (int i = 0; i < *contLivros; i++) {
		if (livros[i].id == idLivro) {
			if (livros[i].qtd > 0) {
				for (int j = 0; j < 10; j++) {
					if (livros[i].nomeEmprest[j] == "") {
						cin.ignore();
						cout << "|Digite o nome da pessoa: ";
						getline(cin, livros[i].nomeEmprest[j]);
						livros[i].qtd--;
						cout << "|Livro emprestado com sucesso!" << endl;
						break;
					}
				}
			} else {
				cout << "|NÆo existem mais c¢pias dispon¡veis para esse livro!" << endl<<endl;
				return;
			}
		}
	}

}


void devolverLivro(struct Livro livros[], int *contLivros) {
	int idLivro, pos;
	string nomeDevolve;
	bool existePessoa = false;
	cout << "|Digite o ID do livro: ";
    cin >> idLivro;
	while(!checarID(livros, contLivros, idLivro, &pos)){
       cout<<"|Id nÆo encontrado.\n|Digite novamente: ";
       cin>>idLivro;
	}
    for(int i = 0; i < *contLivros; i++) {
        if(livros[i].id == idLivro) {
            cout << "|Digite o nome da pessoa que vai devolver: ";
            cin >> nomeDevolve;
            for(int j = 0; j < 10; j++) {
                if(livros[i].nomeEmprest[j] == nomeDevolve) {
                    cout << "|Livro devolvido!"<<endl<<endl;
                    for (int x = 0; x < 10; x++) {
                        livros[i].nomeEmprest[j] = "";
                        existePessoa = true;
                    }
                    break;
                }
            }
            while (existePessoa == false) {
                cout<<"|Essa pessoa nÆo est  com o livro selecionado!\nDigite novamente: "<<endl;
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
	cout<<"|Digite o ID do livro que deverC! ser removido: ";
	cin>>ID;
	while(!checarID(livros , contLivros, ID, &pos)){
		cout<<"|Id nÆo encontrado, digite outro: ";
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
	cout<<"|O livro de id:"<<ID<<" foi removido"<<endl;

}

int main() {
    setlocale(LC_ALL, "Portuguese");
	struct Livro livros[100];
	int contLivros = 0;
	int opt;

	do {
		linha();
		cout<<"|\t\t\t\t\t| Biblioteca |\t\t\t\t\t\t     |"<<endl;
		linha();
		cout << "|1. Cadastrar Livro" << endl;
		cout << "|2. Consultar Livro" << endl;
		cout << "|3. Emprestar Livro" << endl;
		cout << "|4. Remover Livro" << endl;
		cout << "|5. Devolver Livro" << endl;
		cout << "|6. Sair do programa" <<endl;
		cout << "|Selecione: ";
		cin >> opt;
		linha();

		switch (opt) {
		case 1:
			cout<<"|Cadastro de livros:"<<endl;
			cadastrarLivro(livros, &contLivros);
			break;
		case 2:
			cout<<"|Consulta de livros:"<<endl;
			consultarLivro(livros, &contLivros);
			break;
		case 3:
			cout<<"|Emprestimo de livros:"<<endl;
			emprestarLivro(livros, &contLivros);
			break;
		case 4:
			cout<<"|Apagar livros:"<<endl;
			removerLivro(livros, &contLivros);
			break;
		case 5:
			cout<<"|Devolver livros:"<<endl;
		    devolverLivro(livros, &contLivros);
		    break;
		case 6:
			cout << "|Programa encerrado." << endl;
			break;
		default:
			cout << "|Digite uma opcao valida!" << endl;
		}

	} while (opt != 6);

	return 0;
}
