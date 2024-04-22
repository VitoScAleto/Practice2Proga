#include <locale.h>
#include <iostream>
using namespace std;

// Функция для нахождения обратного элемента
int extendedEuclideanAlgorithm(int number, int module, int& x, int& y)
{
    if (module == 0) {
        x = 1;
        y = 0;
        return number;
    }
    int x1 = 0, y1 = 0;
    int NOD = extendedEuclideanAlgorithm(module, number % module, x1, y1); // в реккуретной форме переставляем число и модуль местами
    x = y1;
    y = x1 - (number / module) * y1;
    return NOD;
}

int findInverseElement(int number, int module)
{
    int x = 0, y = 0;
    int NOD = extendedEuclideanAlgorithm(number, module, x, y);
    if (NOD != 1) {
        cout << "Обратного элемента не существует";
        return 0;
    }
    else {
        return (x % module + module) % module; // обработка отрицательных значений
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int number = 0;
    int module = 0;
    cout << "Введите число" << endl;
    cin >> number;
    cout << "Введите модуль" << endl;
    cin >> module;
    int inverse_number = findInverseElement(number, module);
    cout << number << "^-1" << " mod " << module << " = " << inverse_number << endl;
    cout << number << " * " << inverse_number << " по модулю " << module << " = 1" << endl;
    return 0;
}