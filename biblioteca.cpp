#include <iostream>
#include <string.h>
using namespace std;

// Criação do struct livro
struct Livro {
    string titulo;
    string autor;
    int numPag;
    int anoPublic;
    int id;
    int qtd;
    string nomeEmprest[10];
};

// printa linhas para organização
void linha(){
    cout << "|";
    for(int i = 0; i < 100; i++){
        cout << "-";
    }
    cout << "|\n";
}

// pergunta para o usuário a confirmação de qualquer ação
bool confirma(){
    bool aceita = false;
    int numAceita;

    cout << "Deseja mesmo realizar a acao?" << endl << "1 - SIM\n2 - NAO" << endl << "Digite: ";
    cin >> numAceita;

    while(numAceita != 1 && numAceita != 2){
        cout << "Digite um numero valido" << endl << "1 - SIM\n2 - NAO";
        cin >> numAceita;
    }

    if(numAceita == 1) aceita = true;

    // se o usuário aceitar, retorna true
    // caso contrário, retorna falso
    return aceita;
}

// indica se um ID já existe
bool checarID(struct Livro livros[], int *contLivros, int ID, int *pos){
    bool checkID;
    for(int i = 0; i < *contLivros; i++){
        if(ID == livros[i].id){
            *pos = i;
            // se o ID existe, retorna true
            return checkID = true;
        }
    }
    // se o ID não existir, retorna false
    return checkID = false;
}

// imprime as informações de um livro
void printLivro(struct Livro L) {
    string nomes[10];
    linha();
    cout << "|Titulo: " << L.titulo << endl;
    cout << "|Autor: " << L.autor << endl;
    cout << "|Numero de Paginas: " << L.numPag << endl;
    cout << "|Ano de Publicacao: " << L.anoPublic << endl;
    cout << "|ID: " << L.id << endl;
    cout << "|Quantidade Disponivel: " << L.qtd << endl;

    // verifica se um livro ja foi emprestado,
    // se ele foi emprestado, imprime todos os nomes
    // caso contrário, avisa que ele ainda não foi emprestado
    bool temEmprestimo = false;
    for (int i = 0; i < sizeof(L.nomeEmprest) / sizeof(L.nomeEmprest[0]); i++) {
        if (L.nomeEmprest[i] != "") {
            nomes[i] = L.nomeEmprest[i];
            temEmprestimo = true;
        }
    }
    if(temEmprestimo == true){
        cout << "|Emprestado para: ";
        for (int i = 0; i < sizeof(nomes) / sizeof(nomes[0]); i++) {
            if (nomes[i] != ""){
                cout << nomes[i] << " | ";
            }
        }
    }
    if (temEmprestimo == false) {
        cout << "|Esse livro ainda nao foi emprestado!" << endl;
    }
    cout << "\n";
}

// cadastra um livro
void cadastrarLivro(struct Livro livros[], int *contLivros) {
    struct Livro L;
    int p;
    cout << "|Digite o titulo do livro: ";
    cin.ignore();
    getline(cin, L.titulo);
    cout << "|Digite o nome do autor: ";
    getline(cin, L.autor);
    cout << "|Digite a quantidade de paginas: ";
    cin >> L.numPag;
    cout << "|Digite o ano de publicacao: ";
    cin >> L.anoPublic;
    cout << "|Digite o ID: ";
    cin >> L.id;
    while(checarID(livros, contLivros, L.id, &p)){
        cout << "|ID ja existente, digite outro: ";
        cin >> L.id;
    }
    cout << "|Digite a quantidade: ";
    cin >> L.qtd;
    // limita a quantidade de livros para 10
    while (L.qtd > 10) {
        cout << "|O limite de livros eh 10. Digite um valor valido: ";
        cin >> L.qtd;
    }
    // aumenta o contador de livros e cadastra um livro no vetor de struct
    livros[*contLivros] = L;
    (*contLivros)++;
    cout << "|Livro cadastrado com sucesso!" << endl;
}

// imprime livros específicos ou todos os cadastrados
void consultarLivro(struct Livro livros[], int *contLivros) {
    int opt = 0, pos;
    int idLivro;
    bool existeLivro = false;
    // pergunta se o usuário deseja listar um livro específico ou todos que existem
    cout << "|1 - Listar todos os livros" << endl;
    cout << "|2 - Listar livro especifico" << endl;
    cout << "|Selecione: ";
    cin >> opt;
    // previne erro do usuário ao digitar uma opção inválida
    while(opt > 2 || opt < 1) {
        cout << "|Digite uma opcao existente" << endl;
        cout << "|1 - Listar todos os livros" << endl;
        cout << "|2 - Listar livro especifico" << endl;
        cout << "|Selecione: ";
        cin >> opt;
    }
    switch (opt) {
        case 1:
            // se não há livros cadastrados, indica esse fato ao usuário.
            if(*contLivros == 0) {
                cout << "|Nao existem livros cadastrados!" << endl << endl;
                break;
            } else {
                for(int i = 0; i < *contLivros; i++) {
                    printLivro(livros[i]);
                }
            }
            break;

        case 2:
            if(*contLivros == 0) {
                // se não há livros cadastrados, indica esse fato ao usuário.
                cout << "|Nao existem livros cadastrados!" << endl << endl;
                break;
            }
            cout << "|Digite um ID de livro: ";
            cin >> idLivro;
            // se o ID digitado é inválido, faz o usuário digitar uma opção válida.
            while (!checarID(livros, contLivros, idLivro, &pos)) {
                cout << "|ID nao encontrado.\n|Digite novamente: ";
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

// função de emprestar livros
void emprestarLivro(struct Livro livros[], int *contLivros) {
    int idLivro, pos;
    // se não há livros cadastrados, indica esse fato ao usuário.
    if (*contLivros == 0){
        cout << "|Nao ha livros cadastrados." << endl;
    }
    // Faz o usuário digitar o ID de um livro.
    else{
        cout << "|Digite um ID de livro: ";
        cin >> idLivro;
        // se o ID digitado é inválido, faz o usuário digitar uma opção válida.
        while (!checarID(livros, contLivros, idLivro, &pos)) {
            cout << "|ID nao encontrado.\n|Digite novamente: ";
            cin >> idLivro;
        }

        for (int i = 0; i < *contLivros; i++) {
            if (livros[i].id == idLivro) {
                if (livros[i].qtd > 0) {
                    for (int j = 0; j < 10; j++) {
                        if (livros[i].nomeEmprest[j] == "") {
                            cin.ignore();
                            // Usuário digita o nome de quem emprestou o livro.
                            cout << "|Digite o nome da pessoa: ";
                            getline(cin, livros[i].nomeEmprest[j]);
                            // Confirmação
                            if(confirma()){
                                livros[i].qtd--;
                                cout << "|Livro emprestado com sucesso!" << endl;
                                break;
                            } else {
                                livros[i].nomeEmprest[j] = "";
                                cout << "Operacao cancelada" << endl << endl;
                                return;
                            }
                        }
                    }
                  // Se não há mais cópias disponíveis, indica isso ao usuário e retorna ao menu.
                } else {
                    cout << "Nao existem mais copias disponiveis para esse livro!" << endl << endl;
                    return;
                }
            }
        }
    }
}

// função de devolver livros
void devolverLivro(struct Livro livros[], int *contLivros) {
    int idLivro, pos;
    string nomeDevolve;
    bool nomeEncontrado = false;
    // se não há livros cadastrados, indica esse fato ao usuário.
    if (*contLivros == 0){
        cout << "|Nao ha livros cadastrados." << endl;
    }
    else{

        // Faz o usuário digitar o ID de um livro.
        cout << "|Digite o ID do livro: ";
        cin >> idLivro;
        // se o ID digitado é inválido, faz o usuário digitar uma opção válida.
        while (!checarID(livros, contLivros, idLivro, &pos)) {
            cout << "|ID nao encontrado.\n|Digite novamente: ";
            cin >> idLivro;
        }
        // Verifica se o livro está atualmente emprestado
        bool temEmprestimo = false;
        for (int j = 0; j < 10; j++) {
            if (livros[pos].nomeEmprest[j] != "") {
                temEmprestimo = true;
                break;
            }
        }
        // Se o livro não possui empréstimos, indica ao usuário e retorna ao menu.
        if (!temEmprestimo) {
            cout << "|Esse livro nao foi emprestado para ninguem!" << endl;
            return;
        }
        // Pede ao usuário o nome de alguém que emprestou o livro.
        cin.ignore();
        while (!nomeEncontrado) {
            cout << "|Digite o nome da pessoa que vai devolver o livro: ";
            getline(cin, nomeDevolve);

            for (int j = 0; j < 10; j++) {
                if (livros[pos].nomeEmprest[j] == nomeDevolve) {
                    if (confirma()) {
                        livros[pos].nomeEmprest[j] = "";  // Remove o nome da lista de empréstimos.
                        livros[pos].qtd++;
                        cout << "|Livro devolvido com sucesso!" << endl;
                        nomeEncontrado = true;
                        break;
                    } else {
                        cout << "Operacao cancelada." << endl;
                        return;
                    }
                }
            }
            // Se a pessoa não estiver com o livro, indica isso ao usuário.
            if (!nomeEncontrado) {
                cout << "|Essa pessoa nao esta com o livro!" << endl;
            }
        }
    }
}

// função de remover livros
void removerLivro(struct Livro livros[], int *contLivros) {
    int ID, pos;
    // se não há livros cadastrados, indica esse fato ao usuário.
    if (*contLivros == 0){
        cout << "|Nao ha livros cadastrados." << endl;
    }
    else{
        // Faz o usuário digitar o ID de um livro.
        cout << "|Digite o ID do livro que deve ser removido: ";
        cin >> ID;

        // se o ID digitado é inválido, faz o usuário digitar uma opção válida.
        while (!checarID(livros, contLivros, ID, &pos)){
            cout << "|ID nao encontrado, digite outro: ";
            cin >> ID;
        }
        bool temEmprestimo = false;
        for (int j = 0; j < 10; j++) {
            if (livros[pos].nomeEmprest[j] != "") {
                temEmprestimo = true;
                cout<<"|O livro nao pode ser removido enquanto esta emprestado."<<endl;
                return;
            }
        }
        // Confirmação
        if(confirma()){
            if(*contLivros == 1){
                livros = NULL;
                (*contLivros)--;
            }
            else if(pos + 1 == *contLivros){
                struct Livro livrosNovo[*contLivros - 1];
                for(int i = 0; i < *contLivros - 1; i++){
                    livrosNovo[i] = livros[i];
                }
                for(int i = 0; i < *contLivros - 1; i++){
                    livros[i] = livrosNovo[i];
                }
                (*contLivros)--;
            }
            else{
                struct Livro aux[*contLivros - 1];
                for(int i = 0; i < *contLivros; i++) {
                    if(ID == livros[i].id){
                        for(int j = i; j < *contLivros; j++){
                            livros[j] = livros[j + 1];
                        }
                    }
                }
                // O livro é removido da lista de livros
                (*contLivros)--;
                cout << "|O livro de ID: " << ID << " foi removido" << endl;
            }
        } else {
            cout << "Operacao cancelada";
            return;
        }
    }
}

int main() {
    struct Livro livros[100];
    int contLivros = 0;
    int opt;
    // Menu
    do {
        linha();
        cout << "|\t\t\t\t\t| Biblioteca |\t\t\t\t\t\t     |" << endl;
        linha();
        cout << "|1. Cadastrar Livro" << endl;
        cout << "|2. Consultar Livro" << endl;
        cout << "|3. Emprestar Livro" << endl;
        cout << "|4. Remover Livro" << endl;
        cout << "|5. Devolver Livro" << endl;
        cout << "|6. Sair do programa" << endl;
        cout << "|Selecione: ";
        cin >> opt;
        linha();

        switch (opt) {
            //Cadastrar livro
            case 1:
                cout << "|Cadastro de livros:" << endl;
                cadastrarLivro(livros, &contLivros);
                break;
            // Consultar livros
            case 2:
                cout << "|Consulta de livros:" << endl;
                consultarLivro(livros, &contLivros);
                break;
            // Emprestar livro
            case 3:
                cout << "|Emprestimo de livros:" << endl;
                emprestarLivro(livros, &contLivros);
                break;
            // Apagar livro
            case 4:
                cout << "|Apagar livros:" << endl;
                removerLivro(livros, &contLivros);
                break;
            // Devolver Livro
            case 5:
                cout << "|Devolver livros:" << endl;
                devolverLivro(livros, &contLivros);
                break;
            // Encerra o programa
            case 6:
                cout << "|Programa encerrado." << endl;
                break;
            // Faz o usuário digitar uma opção válida.
            default:
                cout << "|Digite uma opcao valida!" << endl;
        }

    } while (opt != 6);

    return 0;
}
