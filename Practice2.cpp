#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

int findRemainder(int& number, int& degree, int& deductionModule, int& remainder); //поиска остатка
void Input (int& number, int& degree, int& deductionModule);    // вывод
bool isValidPrimeNumber (int validPrimeNumber);                 // проверка на простое число
int FermsTheorema (int a, int p);                               // малая теорема ферма
void PrintThFerma (int& number, int& degree, int& deductionModule); // вывод теоремы ферма когда а кратно р
pair<int, int> remainderModLog (int& number, int& degree, int& primeNumber); //функция для вычисления остатка
void propertiesOfComparisons(int& number, int& degree, int& deductionModule, int& remainder); //просмотр свойств сравнений

int main () {
	int degree = 0, deductionModule = 0, number = 0, remainder = 0;
	findRemainder(number, degree, deductionModule, remainder);

	cout << "\nIf you want watch properities of comparisons input '1'\n"; //если хотим посмотреть свойства сравнений
	cout << "For exit select any other key\n";
	cout << "Enter number: ";
	char s;
	cin >> s;
	switch (s) {
		case('1'):
			propertiesOfComparisons(number, degree, deductionModule, remainder);
			break;
		default:
			cout << "Thank for using";
			break;
	}
}

int findRemainder(int& number, int& degree, int& deductionModule, int& remainder){
	Input (number, degree, deductionModule);

	if (degree == deductionModule && isValidPrimeNumber(deductionModule) == true) { // используем теорему ферма
		PrintThFerma( number, degree, deductionModule);
	}

	pair<int, int> result = remainderModLog(number, degree, deductionModule);
	cout << "Result by model = " << result.first << " and by logarifm = " << result.second << endl;
	remainder = result.first;

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

int FermsTheorema(int number, int deductionModule) { // теорема ферма
	if (number % deductionModule == 0) { //если число делится на простое число без остатка
		return 0;                        //идем по другой ветке
	} else {
		return 1;
	}
}

bool isValidPrimeNumber(int validPrimeNumber) {      // проверка на простое число
	if (validPrimeNumber == 0 || validPrimeNumber == 1) {
		return false;
	}
	for (int i = 2; i < sqrt(validPrimeNumber) + 1; i++) {
		if (validPrimeNumber % i == 0){
			return false;
		} 
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

string toBinary (int number) {   //перевод степени числа в 2сс для поиска остатка
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

pair<int, int> remainderModLog(int& number, int& degree, int& deductionModule){
	pair<int,int> result = {1,1};

    for (int i = 1; i <= degree; i++){   //идем по каждой степени и оставляем только остатки
        result.first *= number;
        result.first %= deductionModule;
    }

	int logByNumber = log2(number);     //рассматриваем остатки через логаривм и 2сс.
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

int findDiviner(int&number, int& degree, int& deductionModule, int& remainder) {
	int NUM = pow(number, degree);
	for (int div = 2; div <= min( NUM, remainder); div++) {
		if ( NUM % div == 0 && remainder % div == 0){
			if (div % deductionModule != 0){
				return div;
			}
		}
	}
	return 0;
}

void propertiesOfComparisons(int& number, int& degree, int& deductionModule, int& remainder) { //свойства сравнений
	cout << "\nThe nearest numbers with the same remainder: ";                        //первое, ближайшие числа с тем же остатком
	cout << " less: "<< remainder - deductionModule << "; more: " << remainder + deductionModule << endl;

	int diviner = findDiviner(number, degree, deductionModule, remainder);   //есть существует делитель, то
	if (diviner != 0) {
		cout << number << " / " << diviner << " = " << remainder << " / " << diviner << " mod " << deductionModule << endl;
	} else {
		cout << "\nThe diviner was not found" << endl;
	}
	cout << "\nInput the data for the second equality, ENTER THE SAME SIMPLE NUMBER:" << endl; //найдем второе число и остаток
	int degree2 = 0, number2 = 0, deductionModule2 = 0, remainder2 = 0;                                              //по тому же модулю
	findRemainder(number2, degree2, deductionModule2, remainder2);
	if (deductionModule2 != deductionModule) {
		cout << "The input modules are not equal!" <<endl;
	} else {
		cout << "Accordingly: " << number << "**" << degree << " (*, +, -) " << number2 << "**" << degree2 << " = ";
		cout << remainder << " (*, +, -) " << remainder2 << " mod " << deductionModule << endl;  //выведем второе свойство	
	}

}