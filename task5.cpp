#include <iostream>
using namespace std;

void main() {
    int number, degree1, degree2;
    
    cout << "Input number: ";
    cin >> number;
    cout << "Input degree: ";
    cin >> degree1;
    cout << "Input degree for degree: ";
    cin >> degree2;

    int numberInDegree = 1;                            // результат возведения в первую степень
    for (int i = 1; i <= degree1; i++) {               // возводим число в первую степень
        numberInDegree = (numberInDegree * number) % 10; // смотрим последнюю цифру 
    }

    int numberInDegree2 = 1;                            // результат возведения во вторую степень
    for (int i = 1; i <= degree2; i++) {                // возводим число в степени во вторую степень
        numberInDegree2 = (numberInDegree2 * numberInDegree) % 10; // смотрим последнюю цифру
    }

    cout << "Последняя цифра "<< numberInDegree2 << endl;
}