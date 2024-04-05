#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

void Printf (int& number, int& degree, int& primeNumber);       // вывод
bool isValidPrimeNumber (int validPrimeNumber);                 // проверка на простое число
int FermsTheorema (int a, int p);                               // малая теорема ферма
void PrintThFerma (int& number, int& degree, int& primeNumber); // вывод теоремы ферма когда а кратно р
int isValidDegree (int& degree);                                // проверка степени
pair<int, int> remainderModLog (int& number, int& degree, int& primeNumber);
string toBinary (int number);

int main () {
	int degree = 0, primeNumber = 0, number = 0;
	Printf(number,degree,primeNumber);

	if (degree == primeNumber) { // используем теорему ферма
		PrintThFerma( number, degree, primeNumber);
	}

	pair<int, int> result = remainderModLog(number, degree, primeNumber);
	cout << "Result by model = " << result.first << " and by logarifm = " << result.second << endl;

	return 0;
}

void Printf(int& number, int& degree, int& primeNumber) { // вывод
	cout << "Input the data: \nnumber = ";
	cin >> number;
	do {
		cout << "Input the degree: \ndegree = ";
		cin >> degree;
		if (isValidDegree(degree) == false){
			cout << "\nDegree cannot be subzero!!!\n\n";
		}
	} while(isValidDegree(degree) == false);
	do {
		cout << "Input prime number: \nprimeNumber = ";
		cin >> primeNumber;
		if (isValidPrimeNumber(primeNumber) == false){
			cout << "\nThis is not a prime!!!\n\n";
		}
	} while (isValidPrimeNumber(primeNumber) == false);
}

int isValidDegree(int& degree){
	if (degree == 0 || degree < 0) return false;
	return true;
}

int FermsTheorema(int a, int p) { // теорема ферма
	if (a % p == 0) {
		return 0;
	} else {
		return 1;
	}
}

bool isValidPrimeNumber(int validPrimeNumber) { // проверка на простое число
	if (validPrimeNumber == 0 || validPrimeNumber == 1) return false;
	for (int i = 2; i < sqrt(validPrimeNumber) + 1; i++)
	{
		if (validPrimeNumber % i == 0) return false;

	}
	return true;
 }

void PrintThFerma(int& number, int& degree, int& primeNumber){ // вывод теоремы ферма когда а кратно р
		cout << "\nBy Fermat's theorem:\n" << endl;
		if (FermsTheorema(number,primeNumber) == 0) {          // когда целое кратно простому
			cout << number << "^" << degree << " mod " << primeNumber << " = 0" << endl;
		}
		else {    //когда целое не кратно простому
			cout << number << "^" << degree << " mod " << primeNumber << " = " << number << "^" << degree - 1 << " mod " << primeNumber << " = 1";
		}
}

pair<int, int> remainderModLog(int& number, int& degree, int& primeNumber){
	pair<int,int> result = {1,1};

    for (int i = 1; i <= degree; i++){
        result.first *= number;
        result.first %= primeNumber;
    }

	int logByNumber = log2(number);
	string binary = toBinary(number);
	vector<int> numForResult;
	for (int i = 0; i <= logByNumber; i++){
		numForResult.push_back(pow(number, pow(2,i)));
	}
	int resultForPrime = 1;
	for (int i = 0; i< binary.length(); i++){
		if (binary[i] == '1'){
			resultForPrime *= numForResult[i];
		}
	}
	result.second = resultForPrime % primeNumber;

	return result;
}

string toBinary (int number) {
    if (number == 0) {
        return "0";
    }

    string binary = "";
    while (number > 0) {
        binary = to_string(number % 2) + binary;
        number /= 2;
    }

    return binary;
}