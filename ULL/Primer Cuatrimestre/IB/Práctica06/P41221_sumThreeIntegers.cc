/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date 10 Oct 2024
* @brief Suma de tres numeros enteros
 *
 * @see http://www.cplusplus.com/doc/tutorial/program_structure/
 * @see http://cpp.sh/2dd
 */

#include <iostream>

int main () {
  int num1, num2, num3;

  std::cin >> num1;
  std::cin >> num2;
  std::cin >> num3;

  std::cout << num1 + num2 + num3 << std::endl;
  
  return 0;
}

