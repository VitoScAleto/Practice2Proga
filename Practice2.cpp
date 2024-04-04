#include <iostream>
#include <math.h>
#include <locale.h>

using namespace std;
void Printf(int& number, int& degree, int& primeNumber);// вывод
bool isValidPrimeNumber(int validPrimeNumber);// проверка на простое число
int FermsTheorema(int a, int p);// малая теорема ферма
void PrintThFerma1(int& number, int& degree, int& primeNumber);// вывод теоремы ферма когда а кратно р
void PrintThFerma2(int& number, int& degree, int& primeNumber);// вывод теоремы ферма когда а не кратно р
int isValidDegree(int& degree);// проверка степени
int main(void)
{
	setlocale(LC_ALL, "Rus");
	int degree = 0, primeNumber = 0, number = 0;
	Printf(number,degree,primeNumber);
	if (degree == primeNumber)// используем теорему ферма
	{
		if (FermsTheorema(number,primeNumber) == 0)// когда целое кратно простому
		{
			PrintThFerma1(number, degree, primeNumber);
		}
		else 
		{
			PrintThFerma2(number,degree,primeNumber);//когда целое не кратно простому
		}
	}


	return 0;
}

void Printf(int& number, int& degree, int& primeNumber)// вывод
{
	cout << "Введите целое число: \nnumber = ";
	cin >> number;
	do
	{
		cout << "Введите степень, в которую возводится число number: \ndegree = ";
		cin >> degree;
		if (isValidDegree(degree) == false)
		{
			cout << "\nСтепень не может быть отрицательной!!!\n\n";
		}
	} while(isValidDegree(degree) == false);
	do
	{
		cout << "Введите простое число primeNumber: \nprimeNumber = ";
		cin >> primeNumber;
		if (isValidPrimeNumber(primeNumber) == false)
		{
			cout << "\nЭто не просто число!!!\n\n";
		}
	} while (isValidPrimeNumber(primeNumber) == false);
}
int isValidDegree(int& degree)
{
	if (degree == 0 || degree < 0) return false;
	return true;
}
int FermsTheorema(int a, int p)// теорема ферма
{
	if (a % p == 0) return 0;
	return 1;
}

bool isValidPrimeNumber(int validPrimeNumber)// проверка на простое число
{
	if (validPrimeNumber == 0 || validPrimeNumber == 1) return false;
	for (int i = 2; i < validPrimeNumber; i++)
	{
		if (validPrimeNumber % i == 0) return false;
		
	}
	return true;
 }

void PrintThFerma1(int& number, int& degree, int& primeNumber)// вывод теоремы ферма когда а кратно р
{
	cout << "\nПо теореме Ферма:\n" << number << "^" << degree << " mod " << primeNumber << " = 0" << endl;
}
void PrintThFerma2(int& number, int& degree, int& primeNumber)// вывод теоремы ферма когда а не кратно р
{
	cout << "\nПо теореме Ферма:\n" << number << "^" << degree << " mod " << primeNumber << " = " << number << "^" << degree - 1 << " mod " << primeNumber << " = 1";
}