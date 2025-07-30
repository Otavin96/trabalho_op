#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

queue<int> buffer;
const int MAX = 5;

mutex mtx;
condition_variable cv;
bool done = false;

void produtor() {
    for (int i = 0; i < 10; i++) {
        unique_lock<mutex> lock(mtx);
        while (buffer.size() >= MAX) {
            cv.wait(lock);
        }

        buffer.push(i);
        cout << "Produziu: " << i << endl;

        cv.notify_all();
    }

    // Marca que acabou
    unique_lock<mutex> lock(mtx);
    done = true;
    cv.notify_all();
}

void consumidor() {
    while (true) {
        unique_lock<mutex> lock(mtx);
        while (buffer.empty() && !done) {
            cv.wait(lock);
        }

        if (!buffer.empty()) {
            int valor = buffer.front();
            buffer.pop();
            cout << "Consumiu: " << valor << endl;
        } else if (done) {
            break;
        }

        cv.notify_all();
    }
}

void contar_palavras(string nome_arquivo, int& total) {
    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo: " << nome_arquivo << endl;
        return;
    }

    string linha, palavra;
    int cont = 0;
    while (getline(arquivo, linha)) {
        istringstream ss(linha);
        while (ss >> palavra) {
            cont++;
        }
    }

    total = cont;
}

int main() {
    cout << "==== PRODUTOR-CONSUMIDOR ====\n";
    thread t1(produtor);
    thread t2(consumidor);
    t1.join();
    t2.join();

    cout << "\n==== CONTAGEM DE PALAVRAS ====\n";
    int total1 = 0, total2 = 0;

    thread w1(contar_palavras, "arquivos/exemplo1.txt", ref(total1));
    thread w2(contar_palavras, "arquivos/exemplo2.txt", ref(total2));
    w1.join();
    w2.join();

    cout << "Arquivo 1: " << total1 << " palavras\n";
    cout << "Arquivo 2: " << total2 << " palavras\n";
    cout << "Total: " << (total1 + total2) << " palavras\n";

    return 0;
}

