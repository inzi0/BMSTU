#include "Vector.h"

Vector::Vector(int x) {
    n = x;
    p = new int[n];
}

Vector::Vector(const Vector& other) {
    n = other.n;
    p = new int[n];

    for (int i = 0; i < n; i++) {
        p[i] = other.p[i];
    }
}

Vector::Vector(int* array, int size) {
    n = size;
    p = new int[n];

    for (int i = 0; i < n; i++) {
        p[i] = array[i];
    }
}

Vector::Vector(Vector&& other) {
    n = other.n;
    p = other.p;
    other.p = nullptr;
}

Vector::~Vector() {
    delete[] p;
}

Vector& Vector::operator=(const Vector& other) {
    delete[] p;

    n = other.n;
    p = new int[n];

    for (int i = 0; i < n; i++) {
        p[i] = other.p[i];
    }

    return *this;
}

Vector& Vector::operator=(Vector&& other) {
    delete[] p;

    n = other.n;
    p = other.p;
    other.p = nullptr;

    return *this;
}

int& Vector::operator[](int i) {
    return p[i];
}

ostream& operator<<(ostream& out, const Vector& v) {
    for (int i = 0; i < v.n; i++) {
        out << v.p[i] << endl;
    }

    return out;
}

istream& operator>>(istream& in, Vector& v) {
    for (int i = 0; i < v.n; i++) {
        in >> v.p[i];
    }

    return in;
}

bool operator<(int* array, const Vector& v) {
    bool result = false;
    int i = 0;

    while (i < v.n) {
        if (array[i] > v.p[i]) {
            return false;
        }

        if (array[i] < v.p[i]) {
            result = true;
        }

        i++;
    }

    return result;
}