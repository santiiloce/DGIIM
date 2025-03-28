/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Dado unos numero de entrada el programa imprime su cuadrado y s
 *        raiz cuadrada
 * The program takes directly the input and prints the output
 */
#include <iostream>
#include <cmath>
#include <iomanip>

void ImprimeRaizCuadrada(int number){
  std::cout << std::fixed << std::setprecision(6) << sqrt(number);
}

void ImprimeCuadrado(int number){
  std::cout << number*number;
}

int main(){
  int number;
  while (std::cin >> number){
  	ImprimeCuadrado(number);
  	std::cout << " ";
  	ImprimeRaizCuadrada(number);
	std::cout << std::endl;
  }
  return 0;
}

