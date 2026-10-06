#include <iostream>
#include <utility>
#include <fstream>
#include "Vector.h"

using namespace std;

int main() {

    Vector v(3); // Создание вектора

    v[0] = 10;
    v[1] = 20;
    v[2] = 30;

    Vector copy(v); // Копирующий конструктор

    copy[0] = 999;

    cout << "v:" << endl;
    cout << v;

    cout << "copy:" << endl;
    cout << copy;

    Vector a(3); // Копирующее присваивание

    a = v;

    a[0] = 777;

    cout << "v:" << endl;
    cout << v;

    cout << "a:" << endl;
    cout << a;

    int m[] = {5, 10, 15}; // Проверка оператора <

    cout << "m < v: " << (m < v) << endl;

    Vector move(std::move(v)); // Move-конструктор

    cout << "move:" << endl;
    cout << move;

    Vector b(3); // Move-присваивание

    b = std::move(move);

    cout << "b:" << endl;
    cout << b;

    // Работа с файлами
    ifstream file("input.txt");
    ofstream out("output.txt");

    if (!file.is_open() || !out.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return 1;
    }

    Vector fromFile(3);

    file >> fromFile;
    out << fromFile;

    file.close();
    out.close();

    return 0;
}