//Вариант 24, Соваренко Максим Васильевич
#include <iostream>
#include <vector>

using namespace std;

//Создаём структуру для багажа раньше, чем для пассажира, т.к планируем её ввести в структуру пассажира
struct Baggage {
    string name;
    int weight;
};

struct Passager {
    string fio;
    vector<Baggage> baggages;
};

int main() {
    vector<Passager> passagers;
    vector<int> tweights;

    int n, m, sumw, k;
    float sr;

    cout << "Введите кол-во пассажиров: ";
    cin >> n;
    cin.ignore();

    if (n <= 0) {
        cout << "Ошибка! Пассажиров не может быть "<< n << "." << endl; //Проверка на кол-во пассажиров
        return 0;
    }

    for (int i = 0; i < n; i++) { //Цикл для записи каждого пассажира
        sumw = 0;

        Passager psgr;

        cout <<"Введите фио: ";
        cin.ignore();
        getline(cin, psgr.fio);

        cout << "Введите кол-во багажей: ";
        cin >> m;

        if (m < 0) { //Проверка на кол-во багажей
            cout << "Ошибка! Багажей не может быть "<< m << "." << endl;
            return 0;
        }

        for (int j=0; j < m; j++) { //Цикл для записи каждого багажа
            Baggage b1;

            cout <<"Что за багаж: ";
            cin.ignore();
            getline(cin, b1.name);

            cout << "Вес багажа: ";
            cin >> b1.weight;

            sumw += b1.weight;

            psgr.baggages.push_back(b1);
        }
        tweights.push_back(sumw); //Добавляем все веса в один вектор, это понадобится для нахождения среднего веса
        passagers.push_back(psgr);
     }

    sumw = 0;

    for (int i = 0; i < tweights.size(); i++) {
        sumw += tweights[i];
    }

    sr = float( sumw) /n;

    k=0; //Добавляем счётчик

    for (int c=0; c < tweights.size();c++) {
        if ( tweights[c] > sr) ++k; //Перебираем кол-во пассажиров, вес багажа которых выше, чем средний
    }
    
    cout << "Количество пассажиров, вес багажа которых превосходит средний: " << k << endl;
    return 0;
}
