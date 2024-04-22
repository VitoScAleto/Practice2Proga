package main

import (
	"fmt"
	"math"
)

func main() {
	var choice string
	for {
		fmt.Println("Выберите операцию:")
		fmt.Println("Теорема Эйлера '1'")
		fmt.Println("Логарифм '2'")
		fmt.Println("Малая теорема Ферма '3'")
		fmt.Println("a(+,-,*)b mod m = a mod m (+,-,*) b mod m '4'")
		fmt.Println("Для выхода нажмите любую кнопку, кроме '1', '2', '3' или '4'")
		fmt.Print("Введите ваш выбор: ")
		fmt.Scanln(&choice)

		switch choice {
		case "1":
			eulerOperation()
		case "2":
			logarithmOperation()
		case "3":
			fermatTheoremOperation()
		case "4":
			propertyOperation()
		default:
			fmt.Println("Спасибо за использование")
			return
		}
	}
}

func eulerOperation() {
	var number, degree, deductionModule int
	fmt.Println("Введите число, степень и модуль:")
	fmt.Scanln(&number, &degree, &deductionModule)
	eulerResult := euler(number, degree, deductionModule)
	if eulerResult != 0 {
		fmt.Printf("%d^%d mod %d = %d mod %d\n", number, degree, deductionModule, eulerResult, deductionModule)
	}
}

func logarithmOperation() {
	var number, degree, deductionModule int
	fmt.Println("Введите число, степень и модуль:")
	fmt.Scanln(&number, &degree, &deductionModule)
	remainderLogResult := remainderLog(number, degree, deductionModule)
	fmt.Printf("%d^%d mod %d = %d mod %d\n", number, degree, deductionModule, remainderLogResult, deductionModule)
}

func fermatTheoremOperation() {
	var number, degree, deductionModule int
	fmt.Println("Введите число, степень и модуль:")
	fmt.Scanln(&number, &degree, &deductionModule)
	fermatTheorem(number, degree, deductionModule)
}

func propertyOperation() {
	var number, degree, result1, result2, deductionModule1, deductionModule2 int
	for {
		fmt.Println("Введите 1 пример")
		input(&number, &degree, &deductionModule1)
		result1 = resultMod(number, degree, deductionModule1)

		fmt.Println("Введите 2 пример")
		input(&number, &degree, &deductionModule2)
		result2 = resultMod(number, degree, deductionModule2)
		if deductionModule1 != deductionModule2 {
			fmt.Println("Модули должны быть равны. Повторите ввод")
		} else {
			break
		}
	}
	fmt.Println("Выберите операцию")
	fmt.Println("+ '1'")
	fmt.Println("- '2'")
	fmt.Println("* '3'")
	var choice string
	fmt.Scanln(&choice)
	switch choice {
	case "1":
		fmt.Println(result1 + result2)
	case "2":
		fmt.Println(result1 - result2)
	case "3":
		fmt.Println(result1 * result2)
	default:
		fmt.Println("Неверный выбор операции")
	}
}

func input(number, degree, deductionModule *int) {
	for {
		fmt.Println("Введите целое число: \nnumber = ")
		_, err := fmt.Scanln(number)
		if err != nil {
			fmt.Println("Это не целое число. Повторите ввод")
		} else {
			break
		}
	}
	for {
		fmt.Println("Введите степень(целое неотрицательное число): \ndegree = ")
		_, err := fmt.Scanln(degree)
		if err != nil || *degree < 0 {
			fmt.Println("Ошибка. Повторите ввод")
		} else {
			break
		}
	}
	for {
		fmt.Println("Введите модуль, по которому сравниваются числа(целое число не равное 0,1) \ndeductionModule = ")
		_, err := fmt.Scanln(deductionModule)
		if err != nil {
			fmt.Println("Ошибка. Повторите ввод")
		} else {
			break
		}
	}
}

func fermatTheorem(number, degree, deductionModule int) {
	if isValidPrimeNumber(deductionModule) && deductionModule == degree {
		if number%deductionModule == 0 {
			fmt.Printf("%d^%d mod %d = 0\n", number, degree, deductionModule)
		} else {
			fmt.Printf("%d^%d mod %d = %d^%d mod %d = 1\n", number, degree, deductionModule, number, degree-1, deductionModule)
		}
	} else {
		fmt.Println("Ошибка. Повторите ввод")
	}
}

func isValidPrimeNumber(validPrimeNumber int) bool {
	if validPrimeNumber == 0 || validPrimeNumber == 1 {
		return false
	}
	for i := 2; i < int(math.Sqrt(float64(validPrimeNumber)))+1; i++ {
		if validPrimeNumber%i == 0 {
			return false
		}
	}
	return true
}

func resultMod(number, degree, deductionModule int) int {
	result := 1
	for i := 1; i <= degree; i++ {
		result = (result * number) % deductionModule
	}
	return result
}

func remainderLog(number, degree, deductionModule int) int {
	result := 1
	logByNumber := int(math.Log2(float64(degree)))
	binary := make([]int, 0)
	degree2 := degree
	for degree2 > 0 {
		binary = append(binary, degree2%2)
		degree2 /= 2
	}
	resultForPrime := 1
	for i := 0; i <= logByNumber; i++ {
		if binary[i] == 1 {
			oneDegree := int(math.Pow(2, float64(i)))
			resultForPrime *= resultMod(number, oneDegree, deductionModule)
		}
	}
	result = resultForPrime % deductionModule
	return result
}

func euler(number, degree, deductionModule int) int {
	degreeForEuler := 0
	eulerResult := 0
	if nod(number, deductionModule) == 1 {
		degreeForEuler = degree % countCoprimes(deductionModule)
		eulerResult = resultMod(number, degreeForEuler, deductionModule)
		return eulerResult
	} else {
		fmt.Println("Теорема Эйлера для этих чисел не выполнима. Повторите попытку")
	}
	return 0
}

func nod(a, b int) int {
	for b != 0 {
		t := b
		b = a % b
		a = t
	}
	return a
}

func countCoprimes(deductionModule int) int {
	count := 0
	for i := 1; i < deductionModule; i++ {
		if nod(deductionModule, i) == 1 {
			count++
		}
	}
	return count
}
