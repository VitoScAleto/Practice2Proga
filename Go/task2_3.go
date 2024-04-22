package main

import "fmt"

// Функция для нахождения обратного элемента
func extendedEuclideanAlgorithm(number, module int) (int, int, int) {
	if module == 0 {
		return number, 1, 0
	}
	NOD, x1, y1 := extendedEuclideanAlgorithm(module, number%module)
	x := y1
	y := x1 - (number/module)*y1
	return NOD, x, y
}

func findInverseElement(number, module int) int {
	NOD, x, _ := extendedEuclideanAlgorithm(number, module)
	if NOD != 1 {
		fmt.Println("Обратного элемента не существует")
		return 0
	} else {
		return (x%module + module) % module // обработка отрицательных значений
	}
}

func main() {
	var number, module int
	fmt.Println("Введите число")
	fmt.Scanln(&number)
	fmt.Println("Введите модуль")
	fmt.Scanln(&module)
	inverseNumber := findInverseElement(number, module)
	fmt.Printf("%d^-1 mod %d = %d\n", number, module, inverseNumber)
	fmt.Printf("%d * %d по модулю %d = 1\n", number, inverseNumber, module)
}
