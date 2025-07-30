#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>     
#include <unistd.h>     
#include <sys/types.h>

using namespace std;

void list_files() {
    DIR* dir = opendir(".");
    if (!dir) {
        cout << "Erro ao abrir diretório.\n";
        return;
    }

    struct dirent* entry;
    cout << "Arquivos no diretório atual:\n";
    while ((entry = readdir(dir)) != NULL) {
        cout << "  " << entry->d_name << "\n";
    }

    closedir(dir);
}

void show_file(const string& filename) {
    ifstream file(filename.c_str());
    if (!file) {
        cout << "Erro ao abrir o arquivo '" << filename << "'\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
}

bool change_directory(const string& path) {
    if (chdir(path.c_str()) == 0) {
        return true;
    } else {
        return false;
    }
}

bool backup_file(const string& filename) {
    ifstream src(filename.c_str(), ios::binary);
    if (!src) {
        cout << "Erro ao abrir o arquivo para backup.\n";
        return false;
    }

    ofstream dst((filename + ".bak").c_str(), ios::binary);
    if (!dst) {
        cout << "Erro ao criar arquivo de backup.\n";
        return false;
    }

    dst << src.rdbuf();
    return true;
}

bool restore_file(const string& filename) {
    ifstream src((filename + ".bak").c_str(), ios::binary);
    if (!src) {
        cout << "Backup não encontrado.\n";
        return false;
    }

    ofstream dst(filename.c_str(), ios::binary);
    if (!dst) {
        cout << "Erro ao restaurar o arquivo.\n";
        return false;
    }

    dst << src.rdbuf();
    return true;
}

int main() {
    string comando;

    cout << "Mini Shell";
    cout << "Comandos: ls, cat <arquivo>, cd <pasta>, backup <arquivo>, restore <arquivo>, exit\n";

    while (true) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            cout << string(cwd) << " > ";
        } else {
            cout << "? > ";
        }

        getline(cin, comando);

        string cmd, arg;
        size_t espaco = comando.find(' ');
        if (espaco != string::npos) {
            cmd = comando.substr(0, espaco);
            arg = comando.substr(espaco + 1);
        } else {
            cmd = comando;
        }

        if (cmd == "ls") {
            list_files();
        } else if (cmd == "cat") {
            if (arg.empty()) cout << "Uso: cat <arquivo>\n";
            else show_file(arg);
        } else if (cmd == "cd") {
            if (arg.empty()) cout << "Uso: cd <diretório>\n";
            else if (!change_directory(arg)) cout << "Diretório inválido\n";
        } else if (cmd == "backup") {
            if (arg.empty()) cout << "Uso: backup <arquivo>\n";
            else if (backup_file(arg)) cout << "Backup criado: " << arg << ".bak\n";
        } else if (cmd == "restore") {
            if (arg.empty()) cout << "Uso: restore <arquivo>\n";
            else if (restore_file(arg)) cout << "Arquivo restaurado do backup\n";
        } else if (cmd == "exit") {
            break;
        } else {
            cout << "Comando não reconhecido.\n";
        }
    }

    return 0;
}

