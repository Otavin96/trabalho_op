#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main() {
    queue<string> fila;
    string comando;

    cout << "Fila de Impressora Simples\n";
    cout << "Digite 'add <nome>' para adicionar documento\n";
    cout << "Digite 'print' para imprimir o proximo documento\n";
    cout << "Digite 'exit' para sair\n";

    while (true) {
        cout << "> ";
        getline(cin, comando);

        if (comando.substr(0, 4) == "add ") {
            string nome = comando.substr(4);
            fila.push(nome);
            cout << "Documento '" << nome << "' adicionado a fila.\n";
        } else if (comando == "print") {
            if (fila.empty()) {
                cout << "Fila vazia.\n";
            } else {
                cout << "Imprimindo documento: " << fila.front() << endl;
                fila.pop();
            }
        } else if (comando == "exit") {
            cout << "Saindo...\n";
            break;
        } else {
            cout << "Comando inválido.\n";
        }
    }

    return 0;
}

