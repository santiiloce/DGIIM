/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Dado unos angulos de entrada el programa imprime su seno y coseno
 * The program takes directly the input and prints the output
 */
#include <iostream>
#include <cmath>
#include <iomanip>
#include <math.h>
#define _USE_MATH_DEFINES

double TransformaRad( double grados){
  return (grados * M_PI)/180;
}

int main(){
  double numero;
  while(std::cin >> numero){
	std::cout << std::fixed << std::setprecision(6) << sin(TransformaRad(numero));
	std::cout << " " << std::fixed << std::	setprecision(6) << cos(TransformaRad(numero)) << std::endl;	
  }
  return 0;
}
