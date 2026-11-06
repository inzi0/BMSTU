// Вариант 24, Соваренко Максим Васильевич
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <limits>
using namespace std;

// Описание структуры Ship
struct Ship {
    string name;
    string cap;
    double water;
    int crew;
};

// Функция для ввода данных кораблей
vector<Ship> createShip() {
    int n;
    cout << "Введите кол-во судов: ";

    if ( !(cin >>n ) || n<1 ) {
        cout << "Ошибка!" << endl;
        return 1;
    }

    vector<Ship> ships(n);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i=0; i<n; i++) {
        Ship s;
        cout << "Судно №" << i + 1 << ":"<< endl;
        cout << "Название: " << endl;
        getline(cin, s.name);
        cout << "Имя капитана: " << endl;
        getline(cin, s.cap);
        cout << "Водоизмещение, тыс. тонн: " << endl;

        if (!(cin >> s.water) || s.water <= 0) {
            cout << "Некорректное водоизмещение!" << endl;
            return 1;
        }

        cout << "Численность экипажа: " << endl;

        if (!(cin >> s.crew) || s.crew < 1) {
            cout << "Некорректная численность экипажа!" << endl;
            return 1;
        }

        ships[i]=s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return ships;
}
// Функция вывода данных кораблей
void print (vector<Ship> ships){
    for (int i=0; i<ships.size(); i++) {
    cout << "Судно №" << i + 1 << ":" << endl;
    cout << ships[i].name << endl;
    cout << ships[i].cap << endl;
    cout << ships[i].water << endl;
    cout << ships[i].crew << endl;
}}

int main(int argc, char* argv[]) {

    // Проверка кол-ва аргументов, которые пользователь вводит в командную строку
    if (argc !=4) {
        cout << "Неверное кол-во аргументов!" << endl;
        return 1;
    }

    // Объявление переменных
    int n;
    string line;
    uintmax_t size1;
    uintmax_t size2;

    string action = argv[1];
    string format = argv[2];
    string filename = argv[3];
    string bfile;
    string tfile;

    string extension = filesystem::path(filename).extension();
    filesystem::path otherFile = filename;


    if (action != "write" && action != "read") {
        cout << "Неизвестное действие!" << endl;
        return 1;
    }

    if (format != "text" && format != "binary") {
        cout << "Неизвестный формат!" << endl;
        return 1;
    }

    if (format == "text" && extension != ".txt") {
        cout << "Используйте файлы с расширением .txt для текстового формата!" << endl;
        return 1;
    }

    if (format == "binary" && extension != ".dat") {
        cout << "Используйте файлы с раширением .dat для бинарного формата!" << endl;
        return 1;
    }

    // Определение имён текстового и бинарного файлов
    otherFile.replace_extension(format == "text" ? ".dat" : ".txt");

    if (format == "text") {
        tfile = filename;
        bfile = otherFile.string();
    }
    else {
        bfile = filename;
        tfile = otherFile.string();
    }


    // Запись данных в текстовый файл (write text...)
    if (action == "write" && format == "text") {
        cout << "Запись в текстовый файл..." << endl;

        vector<Ship> ships = createShip();

        if (ships.empty()) {
            cout << "Данные не введены!" << endl;
            return 1;
        }

        ofstream fout(filename);

        if (!fout.is_open()) {
            cout << "Ошибка открытия файла!" << endl;
            return 1;
        }

        fout << ships.size() << endl;

        for (int i=0; i<ships.size(); i++) {
            fout << "Судно №" << i + 1 << ":" << endl;
            fout << ships[i].name << endl;
            fout << ships[i].cap << endl;
            fout << ships[i].water << endl;
            fout << ships[i].crew << endl;
        }

        if (!fout) {
            cout << "Ошибка записи в текстовый файл!" << endl;
            return 1;
        }

        fout.close();
    }


    // Запись данных в бинарный файл (write binary...)
    else if (action == "write" && format == "binary") {
        cout << "Запись в бинарный файл..." << endl;

        vector<Ship> ships = createShip();

        if (ships.empty()) {
            cout << "Данные не введены!" << endl;
            return 1;
        }

        ofstream foutb(filename, ios::binary);

        if (!foutb.is_open()) {
            cout <<"Ошибка открытия бинарного файла!" << endl;
            return 1;
        }

        int n = ships.size();
        foutb.write((char*)&n, sizeof(n));

        for (int i=0; i<ships.size(); i++) {
            foutb << ships[i].name << ends;
            foutb << ships[i].cap << ends;
            foutb.write((char*)&ships[i].water, sizeof(ships[i].water));
            foutb.write((char*)&ships[i].crew, sizeof(ships[i].crew));
        }

        if (!foutb) {
            cout << "Ошибка записи в бинарный файл!" << endl;
            return 1;
        }

        foutb.close();
    }


    // Чтение данных из текстового файла (read text...)
    else if (action == "read" && format == "text") {
        cout << "Чтение текстового файла..." << endl;

        ifstream fin(filename);

        if (!fin.is_open()) {
            cout << "Ошибка открытия файла!" << endl;
            return 1;
        }

        if (!(fin >> n) || n<1 ) {
            cout << "Некорректный файл!" << endl;
            return 1;
        }

        vector<Ship> ships(n);

        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int i=0; i<ships.size(); i++) {
            getline(fin, line);
            getline(fin, ships[i].name);
            getline(fin, ships[i].cap);

            if (!(fin >> ships[i].water) || !(fin >> ships[i].crew)) {
                cout << "Ошибка чтения данных из файла!" << endl;
                return 1;
            }

            fin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (fin.fail()) {
            cout << "Ошибка чтения данных из файла!" << endl;
            return 1;
        }
        fin.close();

        print (ships);
    }


    // Чтение данных из бинарного файла (read binary...)
    else if (action == "read" && format == "binary") {
        cout << "Чтение бинарного файла..." << endl;

        ifstream finb(filename, ios::binary);

        if (!finb.is_open()) {
            cout << "Ошибка открытия бинарного файла!" << endl;
            return 1;
        }

        if (!finb.read((char*)&n, sizeof(n))  || n<1 ) {
            cout << "Некорректный файл!" << endl;
            return 1;
        }

        vector<Ship> ships(n);

        for (int i=0; i<ships.size(); i++) {
            getline(finb,  ships[i].name, '\0');
            getline(finb, ships[i].cap, '\0');
            finb.read((char*)&ships[i].water, sizeof(ships[i].water));
            finb.read((char*)&ships[i].crew, sizeof(ships[i].crew));

            if (!finb) {
                cout << "Ошибка чтения данных из файла!" << endl;
                return 1;
            }
        }

        if (finb.fail()) {
            cout << "Ошибка чтения данных из файла!" << endl;
            return 1;
        }

        finb.close();

        print(ships);
    }

    // Проверка наличия обоих файлов + получение их объёма
    if (filesystem::exists(tfile) && filesystem::exists(bfile)) {
        size1 = filesystem::file_size(tfile);
        size2 = filesystem::file_size(bfile);

        cout << "Размер текстового файла: " << size1 << " байт" << endl;
        cout << "Размер бинарного файла: " << size2 << " байт" << endl;

        if (size1 > size2) {
            cout << "Текстовый файл больше на: " << size1 - size2 << " байт" << endl;
        }
        else if (size2 > size1) {
            cout << "Бинарный файл больше на: " << size2 - size1 << " байт" << endl;
        }
        else {
            cout << "Размеры файлов одинаковые!" << endl;
        }
    }

    return 0;
}
