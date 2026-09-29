//Вариант 24, Соваренко Максим Васильевич
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    
    double a;
    a=sqrt(50);
    
    //Начинаем цикл с конца, так как если решать данную задачу циклом, идущим с начала, получим неверный вывод
    
    for (int i=49;i>=1;--i) { 
        a=sqrt(i+a);
    }

    cout<<a<<endl;


    return 0;
}
