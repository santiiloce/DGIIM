/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 03 2024
 * @brief Programa que imprime que dado dos enteros a y b imprime el logaritmo
 *        en base a de b
 * The program takes directly the input and prints the output
 */
#include <cmath>
#include <iostream>

int main() {
  int base, value;

  while (std::cin >> base >> value) {
    if (base < 2 || value < 1) {  // Validación de entrada
      return 1;
    }
    double log_result = std::log(value) / std::log(base);
    int result = static_cast<int>(round(log_result));
    // Verificamos si base^result es realmente igual a value
    if (std::pow(base, result) > value) 
      result--;  
    std::cout << result << std::endl;
  }
  
  return 0;
}


