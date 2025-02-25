/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 03 2024
 * @brief Programa que imprime que dado dos enteros a y b imprime a^b
 * The program takes directly the input and prints the output
 */
#include <iostream>
#include <cmath>

int main() {
  int base, potencia;
  while (std::cin >> base >> potencia) {
  	int aux = 1;
    for( int i = 0; i < potencia; i++)
      aux *= base;
    std::cout << aux << std::endl;  
  }
  return 0;
}
  
