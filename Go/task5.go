package main

import "fmt"

func main() {
	var number, degree1, degree2 int

	fmt.Println("Input number: ")
	fmt.Scanln(&number)
	fmt.Println("Input degree: ")
	fmt.Scanln(&degree1)
	fmt.Println("Input degree for degree: ")
	fmt.Scanln(&degree2)

	numberInDegree1 := 1            // результат возведения в первую степень
	for i := 1; i <= degree1; i++ { // возводим число в первую степень
		numberInDegree1 = (numberInDegree1 * number) % 10 // смотрим последнюю цифру
	}

	numberInDegree2 := 1            // результат возведения во вторую степень
	for i := 1; i <= degree2; i++ { // возводим число в степени во вторую степень
		numberInDegree2 = (numberInDegree2 * numberInDegree1) % 10 // смотрим последнюю цифру
	}

	fmt.Println("The last digit in the number is in the degree:", numberInDegree2)
}
