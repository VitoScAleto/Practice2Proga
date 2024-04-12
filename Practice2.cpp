 #include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

int findRemainder(int& number, int& degree, int& deductionModule, int& remainder); //поиска остатка
void Input(int& number, int& degree, int& deductionModule);    // вывод
bool isValidPrimeNumber(int validPrimeNumber);                 // проверка на простое число
int FermsTheorema(int a, int p);                               // малая теорема ферма
void PrintThFerma(int& number, int& degree, int& deductionModule); // вывод теоремы ферма когда а кратно р
pair<int, int> remainderModLog(int& number, int& degree, int& primeNumber); //функция для вычисления остатка
void propertiesOfComparisons(int& number, int& degree, int& deductionModule, int& remainder); //просмотр свойств сравнений
int Eiler(int& number, int& degree, int& deductionModule);
int countCoprimes(int& deductionModule);

int main() {
	int degree = 0, deductionModule = 0, number = 0, remainder = 0;
	findRemainder(number, degree, deductionModule, remainder);  //ищем остаток по модулю

	cout << "\nIf you want watch properities of comparisons input '1'\n"; //если хотим посмотреть свойства сравнений
	cout << "Watch theorem Eiler of comparisons input '2'\n";
	cout << "For exit select any other key\n"; //для выхода любой кроме
	cout << "Enter number: ";
	char s;
	cin >> s;
	cout << "\n";
	int remainderEiler=0;

	switch (s) {
	case('1'):
		propertiesOfComparisons(number, degree, deductionModule, remainder); //переходим к свойствам сравнений
		break;
	case('2'):
		remainderEiler = Eiler(number, degree, deductionModule);
		if (remainderEiler != -1) {
			cout << "\n" << "By Eiler Theorem remainder = " << remainderEiler;
		}
		else {
			cout << "Error input!";
		}
		break;
	default:
		cout << "Thanks for using";
		break;
	}
}

int findRemainder(int& number, int& degree, int& deductionModule, int& remainder) {
	Input(number, degree, deductionModule);    //сначала вводим с клавиатуры данные

	if (degree == deductionModule && isValidPrimeNumber(deductionModule) == true) { // используем теорему ферма
		PrintThFerma(number, degree, deductionModule);    //если степень равна модулю и проверка на простое
	}

	pair<int, int> result = remainderModLog(number, degree, deductionModule);  //рассматриваем остатки через функцию
	cout << "Result by model = " << result.first << " and by logarifm = " << result.second << endl;
	remainder = result.first;  //выводим остатки, полученные двумя способами

	return 0;
}

void Input(int& number, int& degree, int& deductionModule) { // вывод
	cout << "Input the data: \nnumber = "; //введите число
	cin >> number;
	do {
		cout << "Input the degree: \ndegree = ";  //введите число в степени
		cin >> degree;
		if (degree < 0) {                         //степень не должна быть отрицательной
			cout << "\nDegree cannot be subzero!!!\n\n";
		}
	} while (degree < 0);
	do {
		cout << "Input prime number: \nprimeNumber = ";  //введите простое число
		cin >> deductionModule;
		if (deductionModule < 0) {        //если число меньше нуля вылетаем
			cout << "\nThis is not a prime!!!\n\n";
		}
	} while (deductionModule < 0);
}

int FermsTheorema(int number, int deductionModule) { // теорема ферма
	if (number % deductionModule == 0) { //если число делится на простое число без остатка
		return 0;                        //идем по другой ветке
	}
	else {
		return 1;
	}
}

bool isValidPrimeNumber(int validPrimeNumber) {      // проверка на простое число
	if (validPrimeNumber == 0 || validPrimeNumber == 1) {  //если модуль 0 или 1
		return false;
	}
	for (int i = 2; i < sqrt(validPrimeNumber) + 1; i++) {  //если нашли число, которое делит модуль, то верни ошибку
		if (validPrimeNumber % i == 0) {
			return false;
		}
	}
	return true;
}

void PrintThFerma(int& number, int& degree, int& deductionModule) { // вывод теоремы ферма когда а кратно р
	cout << "\nBy Fermat's theorem:\n" << endl;
	if (FermsTheorema(number, deductionModule) == 0) {          // когда целое кратно простому модулю
		cout << number << "^" << degree << " mod " << deductionModule << " = 0" << endl;
	}
	else {    //когда целое не кратно простому
		cout << number << "^" << degree << " mod " << deductionModule << " = " << number << "^" << degree - 1 << " mod " << deductionModule << " = 1";
	}
}

int degree1(int number, int degree, int simple) {
	int result = 1;
	for (int i = 1; i <= degree; i++) {
		result = (result * number) % simple;
	}
	return result;
}

pair<int, int> remainderModLog(int& number, int& degree, int& deductionModule) {
	pair<int, int> result = { 1,1 };

	result.first = degree1(number, degree, deductionModule);

	int logByNumber = log2(degree);     //рассматриваем остатки через логаривм и 2сс.
	vector<int> binary;  //переводим степень в 2сс.
	while (degree > 0) {
		binary.push_back(degree % 2);
		degree /= 2;
	}

	int resultForPrime = 1;
	for (int i = 0; i <= logByNumber; i++) {
		if (binary[i] == 1) { //бинарное не переворачиваем, а просто идем с "конца"
			int oneDegree = pow(2, i);
			resultForPrime *= degree1(number, oneDegree, deductionModule); //вместо второго этапа воспользуемся уже имеющейся функцией и будем вычислять при необходимости
		}
	}
	result.second = resultForPrime % deductionModule;  //после смотрим на остаток

	return result;  //вернем пару значений
}

int findDiviner(int& number, int& degree, int& deductionModule) {

	int NUM = pow(number, degree);

	for (int div = 2; div <= min(NUM, deductionModule); div++) { //проходимся по делителям
		if (NUM % div == 0 && deductionModule % div == 0) {  //если он делит оба числа
			if (div % deductionModule != 0) {           //и не делится на модуль
				return div;                           //это он
			}
		}
	}
	return 0;
}

void propertiesOfComparisons(int& number, int& degree, int& deductionModule, int& remainder) { //свойства сравнений
	cout << "\nThe nearest numbers with the same remainder: ";                        //первое, ближайшие числа с тем же остатком
	cout << " less: " << remainder - deductionModule << "; more: " << remainder + deductionModule << endl;

	int diviner = findDiviner(number, degree, deductionModule);   //есть существует делитель, то
	if (diviner != 0) {
		cout << number << " / " << diviner << " = " << remainder << " / " << diviner << " mod " << deductionModule << endl;
	}
	else {
		cout << "\nThe diviner was not found" << endl;
	}

	cout << "\nInput the data for the second equality, ENTER THE SAME SIMPLE NUMBER:" << endl; //найдем второе число и остаток
	int degree2 = 0, number2 = 0, deductionModule2 = 0, remainder2 = 0;                        //по тому же модулю
	findRemainder(number2, degree2, deductionModule2, remainder2);
	if (deductionModule2 != deductionModule) {
		cout << "The input modules are not equal!" << endl;
	}
	else {
		cout << "Accordingly: " << number << "**" << degree << " (*, +, -) " << number2 << "**" << degree2 << " = ";
		cout << remainder << " (*, +, -) " << remainder2 << " mod " << deductionModule << endl;  //выведем второе свойство	
	}
}

int Eiler(int& number, int& degree, int& deductionModule) {
	int result = 1;
	if (findDiviner(number, degree, deductionModule) == 0) {
		degree = degree % countCoprimes(deductionModule);
		for (int i = 1; i <= degree; i++) {   //идем по каждой степени и оставляем только остатки
			result *= number;
			result %= deductionModule;
		}
	}
	if (number % deductionModule == 0 or deductionModule % number == 0) {
		return -1;
	}
	return result;
}

int NOD(int a, int b) {  //находит наибольший общий делитель
    while (b != 0) {  //пока 
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int countCoprimes(int &deductionModule) {
    int count = 0;
    for (int i = 1; i < deductionModule; i++) {  //проходит от 1 до числа
        if (NOD(deductionModule, i) == 1) {     //если наибольший общий делитель 1 
            count++;
        }
    }
    return count;
}