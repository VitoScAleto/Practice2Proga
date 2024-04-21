#include <iostream>
#include <cstring>
#include <locale.h>
#include <string>
#include <fstream>

using namespace std;

int generationKey(int number, int privetKey, int deductionModule);
string encrypt_text( string& plaintext, string& key);// шифрование текста
string decrypt_text( string& ciphertext, string& key);// расшифрование текста
bool isValidPrimeNumber(int validPrimeNumber); // проверка на простое число
void Diffie_Hellman(void);

int main()
{
    setlocale(LC_ALL, "Rus");
    cout << "Введите текст для шифрования" << endl;
    string plaintext = "\0";
    getline(cin, plaintext);

    Diffie_Hellman();
    

    string secret_Key_Alice = "\0";  // Ключ для XOR-шифра
    cout << "Ввдеите секретный ключ Алисы" << endl;
    cin >> secret_Key_Alice;
    
    
    // Шифрование текста
    string encryptedText = encrypt_text(plaintext, secret_Key_Alice);
    cout << "Зашифрованный текст: " << encryptedText << endl;

    string secret_Key_Bob = "\0";
    cout << "Введите секретный ключ Боба" << endl;
    cin >> secret_Key_Bob;
    // Дешифрование текста
    string decryptedText = decrypt_text(encryptedText, secret_Key_Bob);
    cout << "Расшифрованный текст: " << decryptedText << endl;

    return 0;
}


void Diffie_Hellman(void)
{
    int simpleNumber = 0, base = 0, private_key_Alice = 0, private_key_Bob = 0;

    // Задаем простое число и основание
    do
    {
        cout << "Введите модуль(простое число) (p): ";
        cin >> simpleNumber;
        if (isValidPrimeNumber(simpleNumber) == false)
        {
            cout << "Это не простое число. Повторите ввод" << endl;
        }
    } while (isValidPrimeNumber(simpleNumber) != true);

    cout << "Введите основание (g): ";
    cin >> base;

    // Задаем секретные ключи для Alice и Bob
    cout << "Alice: Введите секретный ключ (a): ";
    cin >> private_key_Alice;
    cout << "Bob: Введите секретный ключ (b): ";
    cin >> private_key_Bob;

    // Вычисляем открытые ключи для Alice и Bob
    int public_key_A = generationKey(base, private_key_Alice, simpleNumber);
    int public_key_B = generationKey(base, private_key_Bob, simpleNumber);

    // Вычисляем общий секретный ключ для Alice и Bob
    int secret_key_A = generationKey(public_key_B, private_key_Alice, simpleNumber);
    int secret_key_B = generationKey(public_key_A, private_key_Bob, simpleNumber);

    cout << "Открытый ключ Алисы: " << public_key_A << endl;
    cout << "Открытый ключ Боба: " << public_key_B << endl;
    cout << "Секретный ключ Алисы: " << secret_key_A << endl;
    cout << "Секретный ключ Боба: " << secret_key_B << endl;
}
// Функция для вычисления возведения числа в степень по модулю
int generationKey(int number, int privetKey, int deductionModule)
{
    int result = 1;
    for (int i = 1; i <= privetKey; i++)
    {
        result = (result * number) % deductionModule;
    }
    return result;
}

// Функция для шифрования текста с использованием простого XOR-шифра
string encrypt_text(string& plaintext,  string& key) {
    string encryptedText = plaintext;
    size_t keyLength = key.length();
    size_t textLength = plaintext.length();

    for (size_t i = 0; i < textLength; ++i) {
        encryptedText[i] ^= key[i % keyLength];
    }

    return encryptedText;
}

// Функция для дешифрования текста с использованием простого XOR-шифра
string decrypt_text( string& ciphertext,  string& key) {
    return encrypt_text(ciphertext, key);  // Так как операция XOR обратима, дешифрование и шифрование идентичны
}

bool isValidPrimeNumber(int validPrimeNumber)  // проверка на простое число
{
    if (validPrimeNumber == 0 || validPrimeNumber == 1) //если модуль 0 или 1
    {
        return false;
    }
    for (int i = 2; i < sqrt(validPrimeNumber) + 1; i++) //если нашли число, которое делит модуль, то верни ошибку
    {
        if (validPrimeNumber % i == 0)
        {
            return false;
        }
    }
    return true;
}