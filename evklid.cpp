#include <iostream>
using namespace std;

tuple<int, int, int> evklid(int number1, int number2, int countOfN1, int countOfn2){

    tuple<int, int, int> forNumber1 = make_tuple(number1, 1, 0);  //инициализируем два картежа только с первым числом
    tuple<int, int, int> forNumber2 = make_tuple(number2, 0, 1);  //и только со вторым числом

    cout << get<0>(forNumber1) << "\t" << get<1>(forNumber1) << "\t" << get<2>(forNumber1) << endl; //выводим текущие картежи
    cout << get<0>(forNumber2) << "\t" << get<1>(forNumber2) << "\t" << get<2>(forNumber2) << endl;

    while (get<0>(forNumber2) != 0) {
        int integerPart = get<0>(forNumber1) / get<0>(forNumber2); //целая часть от деления чисел в картеже

        tuple<int, int, int> remains = make_tuple(get<0>(forNumber1) % get<0>(forNumber2), get<1>(forNumber1) - integerPart * get<1>(forNumber2), get<2>(forNumber1) - integerPart * get<2>(forNumber2));
        cout << get<0>(remains) << "\t" << get<1>(remains) << "\t" << get<2>(remains) << "\t" << integerPart << endl;

        forNumber1 = forNumber2;  //в первый картеж закидываем второй 
        forNumber2 = remains;     //во второй закидываем с остатком
    }
    return forNumber1;     //верни первый картеж, ибо во втором будет картеж с остатком 0
}

int main(){
    int number1 = 28;  //числа, которые перемножаются
    int number2 = 19;  
    int countOfN1 = 0, countOfN2 = 0; //количество первого числа и второго числа
    tuple<int, int, int> result = evklid(number1, number2, countOfN1, countOfN2); //создаем картеж с остатком, количеством первого числа и второго числа

    cout << endl;
    cout << " "<< number1 << " * (" << get<1> (result) << ") + " << number2 << " * ("<< get<2> (result) << ") = " << get<0> (result) << endl;

    return 0;
}