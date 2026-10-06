#include <iostream>
using namespace std;

class Vector {
private:
    int n;
    int* p;

public:
    Vector(int x);
    Vector(const Vector& other);
    Vector(int* array, int size);
    Vector(Vector&& other);

    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);

    int& operator[](int i);

    friend ostream& operator<<(ostream& out, const Vector& v);
    friend istream& operator>>(istream& in, Vector& v);
    friend bool operator<(int* array, const Vector& v);
};