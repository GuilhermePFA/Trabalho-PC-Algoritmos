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

void printLivro(struct Livro L){
    cout << L.titulo;
    cout << L.autor;
    cout << L.numPag;
    cout << L.anoPublic;
    cout << L.id;
    cout << L.qtd;
    cout << L.nomeEmprest;
}

void cadastrarLivro(struct Livro livros[], int *contLivros) {
    struct Livro L;
    cout<<"\nDigite o titulo do livro: ";
    cin >> L.titulo;
    cout<<"\nDigite o nome do autor: ";
    cin >> L.autor;
    cout<<"\nDigite a quantidade de paginas: ";
    cin >> L.numPag;
    cout<<"\nDigite o ano de publicação: ";
    cin >> L.anoPublic;
    cout<<"\nDigite o ID: ";
    cin >> L.id;
    cout<<"\nDigite o quantidade: ";
    cin >> L.qtd;
    while (L.qtd > 10) {
        cout<<"\nDigite um numero ate 10: ";
        cin>>L.qtd;
    }
    cout<<"\nDigite o nome de quem pegou o livro: ";
    cin >> L.nomeEmprest[10];

    livros[*contLivros] = L;
    (*contLivros)++;
}

void consultarLivro(struct Livro livros[], int *contLivros) {
    int opt = 0;
    int idLivro;
    bool existeLivro = false;

    cout<<"1 - Listar todxs os livres"<<endl;
    cout<<"2 - Listar livre especifico"<<endl;
    cout<<"Selecione: ";
    cin>>opt;
    while(opt < 3 || opt > 0){
        switch (opt)
        {
        case 1:
            for(int i = 0; i < *contLivros; i++){
                printLivro(livros[i]);
            }
            break;
        
        case 2:

            cout << "Digite o id do livro: " << endl;
            cin >> idLivro;

            while(existeLivro == false){
                cout << "Digite o id do livro: ";
                cin >> idLivro;

                for(int i = 0; i < *contLivros; i++){
                    if(livros[i].id == idLivro){
                        printLivro(livros[i]);
                        existeLivro = true;
                        break;
                    }
                }
                if(existeLivro == false){
                    cout << "Id nao encontrado: " << endl;
                    cout << "Digite outro id: " << endl;
                }
            }
            break;
        }
}