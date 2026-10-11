//Вариант 24, Соваренко Максим Васильевич
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Car {
protected:
    string model;
    int speed;
public:
    Car(string m, int s) : model(m), speed(s){
    }

    virtual void print() {
        cout << "Модель: " << model << endl;
        cout << "max скорость: " << speed << endl;
    }
    void print(int x) {
        cout << "Дополнительная характеристика: " << x << endl;
    }
};

class Bus : public Car {
private:
    int passengers;
public:
    /* Строка ниже открывает доступ к перегруженным методам print базового класса,
     * чтобы их можно было вызывать непосредственно через объект Bus. */
    using Car::print;
    Bus (string m, int s, int p) : Car(m, s), passengers(p) {
    }

    void print() override {
        Car::print();
        cout << "Кол-во пассажиров: " << passengers << endl;
    }
};

int main() {

    Car car ("Audi",220);
    Bus bus ("Mitsubishi",140,100);

    //Динамический полиформизм
    vector <Car*> vehicles = {&car, &bus};
    for (Car* vehicle : vehicles) {
        vehicle->print();
    }

    //Статический полиформизм
    car.print(10);
    bus.print(20);

    return 0;
}
