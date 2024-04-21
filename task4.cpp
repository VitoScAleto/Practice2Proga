#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// Функция для вычисления возведения числа в степень по модулю
int power(int a, int b, int mod) {
    int result = 1;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % mod;
        }
        b = b / 2;
        a = (a * a) % mod;
    }
    return result;
}

// Генерация общего секретного ключа
int generateKey(int base, int private_key, int prime) {
    return power(base, private_key, prime);
}



int main() {
    setlocale(LC_ALL, "Rus");
    int prime, base, private_key_Alice, private_key_Bob;

    // Задаем простое число и основание
    cout << "Введите простое число (p): ";
    cin >> prime;
    cout << "Введите основание (g): ";
    cin >> base;

    // Задаем секретные ключи для Alice и Bob
    cout << "Alice: Введите секретный ключ (a): ";
    cin >> private_key_Alice;
    cout << "Bob: Введите секретный ключ (b): ";
    cin >> private_key_Bob;

    // Вычисляем открытые ключи для Alice и Bob
    int public_key_A = generateKey(base, private_key_Alice, prime);
    int public_key_B = generateKey(base, private_key_Bob, prime);

    // Вычисляем общий секретный ключ для Alice и Bob
    int secret_key_A = generateKey(public_key_B, private_key_Alice, prime);
    int secret_key_B = generateKey(public_key_A, private_key_Bob, prime);

    cout << "Открытый ключ Алисы: " << public_key_A << endl;
    cout << "Открытый ключ Боба: " << public_key_B << endl;
    cout << "Секретный ключ Алисы: " << secret_key_A << endl;
    cout << "Секретный ключ Боба: " << secret_key_B << endl;

    return 0;
}