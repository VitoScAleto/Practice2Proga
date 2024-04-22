package main

import (
	"fmt"
	"math"
)

func main() {
	var plaintext, secretKeyAlice, secretKeyBob string
	fmt.Println("Введите текст для шифрования")
	fmt.Scanln(&plaintext)

	diffieHellman()

	fmt.Println("Ввдеите секретный ключ Алисы")
	fmt.Scanln(&secretKeyAlice)

	encryptedText := encryptText(plaintext, secretKeyAlice)
	fmt.Println("Зашифрованный текст:", encryptedText)

	fmt.Println("Введите секретный ключ Боба")
	fmt.Scanln(&secretKeyBob)

	decryptedText := decryptText(encryptedText, secretKeyBob)
	fmt.Println("Расшифрованный текст:", decryptedText)
}

func diffieHellman() {
	var simpleNumber, base, privateKeyAlice, privateKeyBob int

	for {
		fmt.Println("Введите модуль(простое число) (p): ")
		_, err := fmt.Scanln(&simpleNumber)
		if err != nil || !isValidPrimeNumber(simpleNumber) {
			fmt.Println("Это не простое число. Повторите ввод")
		} else {
			break
		}
	}

	fmt.Println("Введите основание (g): ")
	fmt.Scanln(&base)

	fmt.Println("Alice: Введите секретный ключ (a): ")
	fmt.Scanln(&privateKeyAlice)
	fmt.Println("Bob: Введите секретный ключ (b): ")
	fmt.Scanln(&privateKeyBob)

	publicKeyAlice := generationKey(base, privateKeyAlice, simpleNumber)
	publicKeyBob := generationKey(base, privateKeyBob, simpleNumber)

	secretKeyAlice := generationKey(publicKeyBob, privateKeyAlice, simpleNumber)
	secretKeyBob := generationKey(publicKeyAlice, privateKeyBob, simpleNumber)

	fmt.Println("Открытый ключ Алисы:", publicKeyAlice)
	fmt.Println("Открытый ключ Боба:", publicKeyBob)
	fmt.Println("Секретный ключ Алисы:", secretKeyAlice)
	fmt.Println("Секретный ключ Боба:", secretKeyBob)
}

func generationKey(number, privateKey, deductionModule int) int {
	result := 1
	for i := 1; i <= privateKey; i++ {
		result = (result * number) % deductionModule
	}
	return result
}

func encryptText(plaintext, key string) string {
	encryptedText := []rune(plaintext)
	keyLength := len(key)
	textLength := len(plaintext)

	for i := 0; i < textLength; i++ {
		encryptedText[i] ^= rune(key[i%keyLength])
	}

	return string(encryptedText)
}

func decryptText(ciphertext, key string) string {
	return encryptText(ciphertext, key)
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
