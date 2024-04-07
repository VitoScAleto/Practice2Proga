#include <iostream>
using namespace std;

void advanced_evclid(int number, int modulo, int& reverse, int& countOfModulo, int& diviner) {
  int integerPart, remains, reverseOld, reverseNew, countOfModuloOld, countOfModuloNew;

  if (modulo == 0) {     //если берем число по модулю 0
    diviner = number;    //остаток это само число
    reverse = 1;         //обратное - 1
    countOfModulo = 0;   //количество модуля - 0
    return;
  }

  reverseNew = 1;
  reverseOld = 0;
  countOfModuloNew = 0;
  countOfModuloOld = 1;

  while (modulo > 0) {        //идем до того момента, пока можно уменьшать модуль
    integerPart = number / modulo;      //целый остаток от деления числа на модуль
    remains = number - integerPart * modulo;  //остаток от деления разность числа и целой части на модуль

    reverse = reverseNew - integerPart * reverseOld;     //вычисляем новое обратное число, вычитая из текущего предыдущее значение на целое
    countOfModulo = countOfModuloNew - integerPart * countOfModuloOld; //вычисляем новое количество модуля, вычитая из текущего предыдущее значение на целое

    number = modulo;  //перемещаем модуль в число
    modulo = remains;       //в модуль остаток от деления
    
    reverseNew = reverseOld; //предыдущее становится текущим
    reverseOld = reverse;  // в предыдущее записываем новое
    countOfModuloNew = countOfModuloOld; //предыдущее становится текущим
    countOfModuloOld = countOfModulo;  //в предыдущее записываем новое
  }
  diviner = number;  //в делитель записываем то, что осталось от модуля
  reverse = reverseNew; //в полученное значение записываем предыдущее, так как прошли через 0, а нам нужна 1 
  countOfModulo = countOfModuloOld;   //количество модулей по такому же принципу
}

int inverse(int number, int modulo){
  int diviner, reverse, countOfModulo;
  advanced_evclid(number, modulo, reverse, countOfModulo, diviner); //ищем обратное число через функцию
  
  if (diviner == 1) {     //если остаток от деления на модуль 1
    return reverse;       //мы нашли этот остаток
  } else{
      return -3;
  }
}

void inputReverse(int& number, int& modulo){
    int reverseNumber = inverse( number, modulo);
    
    if (reverseNumber == -3){
        cout << "There is no inverse number" << endl;  //нет обратного числа
    } else {
        cout << "Reverse from " << number  << " modulo " << modulo << " = " << reverseNumber << endl;
    }
}

int main(){
  int number = 5, modulo = 7;   //входные данные
  inputReverse(number, modulo);

  number = 2, modulo = 12;
  inputReverse(number, modulo);
}