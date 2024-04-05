#include <iostream>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

void Printf(int& number, int& degree, int& deductionModule);       // scan and print
bool isValidPrimeNumber(int validPrimeNumber);                 // проверка на простое число
int FermsTheorema(int a, int p);                               // малая теорема ферма
void PrintThFerma(int& number, int& degree, int& deductionModule); // вывод теоремы ферма
pair<int, int> remainderModLog(int& number, int& degree, int& deductionModule);// algorithm log2
string toBinary(int number);// translate from dec to bin
void functionSwitchCase(int& number, int& degree, int& deductionModule);

int main()
{
	int degree = 0, deductionModule = 0, number = 0, number2 = 0;;
	functionSwitchCase(number,degree,deductionModule);
	if (degree == deductionModule && isValidPrimeNumber(deductionModule) == true)// проверка использования теоремы ферма
	{
		PrintThFerma(number, degree, deductionModule);
	}
	pair<int, int> result = remainderModLog(number, degree, deductionModule);
	cout << "\nResult by model = " << result.first << "\nResult By logarifm = " << result.second << endl;

	return 0;
}

void Printf(int& number, int& degree, int& deductionModule)// scan and print
{ 
	cout << "Input the number: \nnumber = ";
	cin >> number;
	do {
		cout << "Input the degree: \ndegree = ";
		cin >> degree;
		if (degree < 0)
		{
			cout << "\nDegree cannot be subzero!!!\n\n";
		}
	} while (degree < 0);
	do {
		cout << "Input deduction module: \ndeductionModule = ";
		cin >> deductionModule;
		if (deductionModule < 0)
		{
			cout << "\nDeduction module cannot be subzero!!!\n\n";
		}
	} while (deductionModule < 0);
}

int FermsTheorema(int a, int p)// теорема ферма
{ 
	if (a % p == 0)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}

bool isValidPrimeNumber(int validPrimeNumber)// проверка на простое число
{
	if (validPrimeNumber == 0 || validPrimeNumber == 1) return false;
	for (int i = 2; i < sqrt(validPrimeNumber) + 1; i++)
	{
		if (validPrimeNumber % i == 0) return false;

	}
	return true;
}

void PrintThFerma(int& number, int& degree, int& deductionModule)// вывод теоремы ферма
{ 
	cout << "\nBy Ferm's theorem:\n" << endl;
	if (FermsTheorema(number, deductionModule) == 0)// когда целое кратно простому
	{          
		cout << number << "^" << degree << " mod " << deductionModule << " = 0" << endl;
	}
	else //когда целое не кратно простому
	{    
		cout << number << "^" << degree << " mod " << deductionModule << " = " << number << "^" << degree - 1 << " mod " << deductionModule << " = 1";
	}
}

pair<int, int> remainderModLog(int& number, int& degree, int& deductionModule)
{
	pair<int, int> result = { 1,1 };

	for (int i = 1; i <= degree; i++)
	{
		result.first *= number;
		result.first %= deductionModule;
	}
	int logByNumber = log2(number);
	string binary = toBinary(number);
	vector<int> numForResult;
	for (int i = 0; i <= logByNumber; i++)
	{
		numForResult.push_back(pow(number, pow(2, i)));
	}
	int resultForPrime = 0;
	for (int i = 0; i < binary.length(); i++)
	{
		if (binary[i] == '1') {
			resultForPrime *= numForResult[i];
		}
	}
	result.second = resultForPrime % deductionModule;

	return result;
}

string toBinary(int number) // translate from dec to bin
{
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

void propertiesOfComparisons(int& number, int& degree, int& deductionModule, int& number2)//свойства сравнений
{
	cout << "Enter number "
	Printf(number, degree, deductionModule);

}
void functionSwitchCase(int& number, int& degree, int& deductionModule)
{
	cout << "To select module comprasion properties press 1\n";
	cout << "To selecte everything else press 2\n";
	cout << "Enter number: ";
	char s;
	cin >> s;
	switch (s) {

	case('1'):
		propertiesOfComparisons();
		break;
	case ('2'):
		Printf(number, degree, deductionModule);
		break;
	default:
		cout << "Error";
		break;
	}
}