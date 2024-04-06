#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

void Input (int& number, int& degree, int& deductionModule);       // вывод
bool isValidPrimeNumber (int validPrimeNumber);                 // проверка на простое число
int FermsTheorema (int a, int p);                               // малая теорема ферма
void PrintThFerma (int& number, int& degree, int& deductionModule); // вывод теоремы ферма когда а кратно р
pair<int, int> remainderModLog (int& number, int& degree, int& primeNumber);
string toBinary (int number);
void functionSwitchCase(int& number, int& degree, int& deductionModule);

int main () {
	int degree = 0, deductionModule = 0, number = 0;
	functionSwitchCase(number,degree,deductionModule);

	if (degree == deductionModule && isValidPrimeNumber(deductionModule) == true) { // используем теорему ферма
		PrintThFerma( number, degree, deductionModule);
	}

	pair<int, int> result = remainderModLog(number, degree, deductionModule);
	cout << "Result by model = " << result.first << " and by logarifm = " << result.second << endl;

	return 0;
}

void Input(int& number, int& degree, int& deductionModule) { // вывод
	cout << "Input the data: \nnumber = ";
	cin >> number;
	do {
		cout << "Input the degree: \ndegree = ";
		cin >> degree;
		if (degree < 0){
			cout << "\nDegree cannot be subzero!!!\n\n";
		}
	} while(degree < 0);
	do {
		cout << "Input prime number: \nprimeNumber = ";
		cin >> deductionModule;
		if (deductionModule < 0){
			cout << "\nThis is not a prime!!!\n\n";
		}
	} while (deductionModule < 0);
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
	for (int i = 2; i < sqrt(validPrimeNumber) + 1; i++) {
		if (validPrimeNumber % i == 0) return false;

	}
	return true;
 }

void PrintThFerma(int& number, int& degree, int& deductionModule){ // вывод теоремы ферма когда а кратно р
		cout << "\nBy Fermat's theorem:\n" << endl;
		if (FermsTheorema(number, deductionModule) == 0) {          // когда целое кратно простому
			cout << number << "^" << degree << " mod " << deductionModule << " = 0" << endl;
		}
		else {    //когда целое не кратно простому
			cout << number << "^" << degree << " mod " << deductionModule << " = " << number << "^" << degree - 1 << " mod " << deductionModule << " = 1";
		}
}

pair<int, int> remainderModLog(int& number, int& degree, int& deductionModule){
	pair<int,int> result = {1,1};

    for (int i = 1; i <= degree; i++){
        result.first *= number;
        result.first %= deductionModule;
    }

	int logByNumber = log2(number);
	string binary = toBinary(number);
	vector<int> numForResult;
	for (int i = 0, forVector = 0; i <= logByNumber; i++){
		forVector = pow(number, pow(2,i));
		numForResult.push_back(forVector % deductionModule);
	}

	int resultForPrime = 1;
	for (int i = 0; i< binary.length(); i++){
		if (binary[i] == '1'){
			resultForPrime *= numForResult[i];
		}
	}
	result.second = resultForPrime % deductionModule;

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

void propertiesOfComparisons(int& number, int& degree, int& deductionModule, int& number2) { //свойства сравнений
	cout << "Enter number: "
	Input (number, degree, deductionModule);
}

void functionSwitchCase(int& number, int& degree, int& deductionModule){
	cout << "To select module comprasion properties press 1\n";
	cout << "To selecte everything else press 2\n";
	cout << "Enter number: ";
	char s;
	cin >> s;
	switch (s) {

	case('1'):
		propertiesOfComparisons(number, degree, deductionModule, );
		break;
	case ('2'):
		Input (number, degree, deductionModule);
		break;
	default:
		cout << "Error";
		break;
	}
}