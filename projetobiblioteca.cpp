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
    cin.getline(L.titulo, 50);
    cout<<"\nDigite o nome do autor: ";
    cin.getline(L.autor, 50);
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
}

void emprestarLivro(struct Livro livros[], int *contLivros){
    int idLivro;
    bool existeLivro = false;

    while(existeLivro == false){
        cout << "Digite o id do livro: ";
        cin >> idLivro;



        for(int i = 0; i < *contLivros; i++){
            if(livros[i].id == idLivro){
                for(int j = 0; j < 10; j++){
                    if(livros[i].nomeEmprest[j] == 'A'){
                        cin.getline(livros[i].nomeEmprest[j], 50);
                        break;
                    }
                }
                livros[i].qtd--;
                existeLivro = true;
                break;
            }
        }
        if(existeLivro == false){
            cout << "Id nao encontrado: " << endl;
            cout << "Digite outro id: " << endl;
        }
    }
}

void removerLivro(struct Livro livros[], int *contLivros){
    int ID;
    cout<<"Digite o ID do livro que deverá ser removido: ";
    cin>>ID;
    for(int i=0; i<*contLivros; i++){
        if(ID==livros[i].id){
            livros[i]=livros[i+1];
            for(int j=i+1; j<*contLivros; j++){
                if(j+1==*contLivros){
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
        cout << "5. Sair" << endl;
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
                cout << "Programa encerrado." << endl;
                break;
            default:
                cout << "Digite uma opcao valida!" << endl;
        }

    } while (opt != 5); 

    return 0;
}