#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstring>
#include <locale.h>
using namespace std;

void Input(int& number, int& degree, int& deductionModule);    // вывод +
bool isValidPrimeNumber(int validPrimeNumber);                 // проверка на простое число +
void FermsTheorema(int& number, int& degree, int& deductionModule);                        // малая теорема ферма+
int remainderLog(int& number, int& degree, int& deductionModule);//+
int Eiler(int& number, int& degree, int& deductionModule);//+
int countCoprimes(int& deductionModule);// взаимно простые числа для модуля. Для теоремы Эйлера+
int resultMod(int number, int degree, int deductionModule);//+
int NOD(int a, int b);//+

int main()
{
	setlocale(LC_ALL, "Rus");
	int degree = 0, deductionModule = 0, number = 0, remainder = 0;
	cout << "Теорема Эйлера '1'\n";
	cout << "Логарифм '2'\n";
	cout << "Малая теорема Ферма '3' " << endl;
	cout << "Для выхода нажмите любую кнопку\n"; //для выхода любой кроме
	cout << "Введите число: ";
	char s;
	cin >> s;
	cout << "\n";
	
	while (true)
	{
		switch (s)
		{
		case('1'):
			if (Eiler(number, degree, deductionModule) != 0)
			{
				cout << number << "^" << degree << " mod " << deductionModule << " = " << Eiler(number, degree, deductionModule) << " mod " << deductionModule << endl;
			}
			break;
		case('2'):
			cout << number << "^" << degree << " mod " << deductionModule << " = " << remainderLog(number, degree, deductionModule) << " mod " << deductionModule << endl;
			break;
		case('3'):
			FermsTheorema(number, degree, deductionModule);
			break;
		default:
			cout << "Thanks for using\n";
			break;
		}
	}
}


void Input(int& number, int& degree, int& deductionModule) // ввод
{
	while (true)
	{
		cout << "Введите целое число: \nnumber = "; //введите число
		cin >> number;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(5, '\n');
			cout << "Это не целое число. Повторите ввод\n" << endl;
		}
		else break;
	}
	while (true)
	{
		cout << "Введите степень(целое неотрицательное число): \ndegree = ";  //введите число в степени
		cin >> degree;
		if (cin.fail() || degree < 0)
		{
			cin.clear();
			cin.ignore(5, '\n');
			cout << "Ошибка. Повторите ввод\n" << endl;
		}
		else break;
	}
	while (true)
	{
		cout << "Введите модуль, по которому сравниваются числа(целое число не равное 0,1) \ndeductionModule = ";  //введите простое число
		cin >> deductionModule;
		if (cin.fail())// cin.fail - проверка пользовательского ввода
		{
			cin.clear();// очистка cin
			cin.ignore(5, '\n');// и удаляем значения предыдущего ввода из входного буфера
			cout << "Ошибка. Повторите ввод\n" << endl;
		}
		else break;
	}
}

void FermsTheorema(int& number,int& degree, int& deductionModule) // теорема ферма
{
	Input(number, degree, deductionModule);
	if (isValidPrimeNumber(deductionModule) == true && deductionModule == degree)
	{
		if (number % deductionModule == 0) //если число делится на простое число без остатка
		{
			cout << number << "^" << degree << " mod " << deductionModule << " = 0" << endl;
		}
		else
		{
			cout << number << "^" << degree << " mod " << deductionModule << " = " << number << "^" << degree - 1 << " mod " << deductionModule << " = 1";
		}
	}
	else
	{
		cout << "Ошибка. Повторите ввод" << endl;
	}
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


int resultMod(int number, int degree, int deductionModule)
{
	int result = 1;
	for (int i = 1; i <= degree; i++)
	{
		result = (result * number) % deductionModule;
	}
	return result;
}

int remainderLog(int& number, int& degree, int& deductionModule) 
{
	Input(number, degree, deductionModule);
	int result = 0;
	int logByNumber = log2(degree);     //рассматриваем остатки через логарифм и 2сс.
	vector<int> binary;  //переводим степень в 2сс.
	int degree2 = degree;
	while (degree2 > 0) {
		binary.push_back(degree2 % 2);
		degree2 /= 2;
	}

	int resultForPrime = 1;
	for (int i = 0; i <= logByNumber; i++) {
		if (binary[i] == 1) { //бинарное не переворачиваем, а просто идем с "конца"
			int oneDegree = pow(2, i);
			resultForPrime *= resultMod(number, oneDegree, deductionModule); //вместо второго этапа воспользуемся уже имеющейся функцией и будем вычислять при необходимости
		}
	}
	result = resultForPrime % deductionModule;  //после смотрим на остаток

	return result;  //вернем пару значений
}


int Eiler(int& number, int& degree, int& deductionModule)
{
	int degreeForEiler = 0;
	int Eilerresult = 0;
	Input(number, degree, deductionModule);
	if (NOD(number, deductionModule) == 1)// если число с модулем взаимно простые, то теорема Эйлера выполнима
	{
		degreeForEiler = degree % countCoprimes(deductionModule);// остаток степени по кол-ву взаимно простых с модулем
		Eilerresult = resultMod(number, degreeForEiler, deductionModule);// результат по Эйлеру
		return Eilerresult;
	}
	else
	{
		cout << "Теорема Эйлера для этих чисел не выполнима. Повторите попытку" << endl;
		
	}
	return 0;
}

int NOD(int a, int b) //находит наибольший общий делитель
{
	while (b != 0)
	{
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}

int countCoprimes(int& deductionModule) // ищем количество взаимно простых чисел с модулем
{
	int count = 0;
	for (int i = 1; i < deductionModule; i++) //проходит от 1 до числа
	{
		if (NOD(deductionModule, i) == 1) //если наибольший общий делитель 1 
		{
			count++;
		}
	}
	return count;
}
