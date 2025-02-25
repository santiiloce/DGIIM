/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 08 2024
 * @brief Programa que devuelve mayor numero entre dos dados
 * The program takes directly the input and prints the output
 */
#include <iostream>
int Maximo(int num1, int num2){
  int max = num1;
  if(num2 > num1)
    max = num2;
  return max;
}

int main(){
  int num1, num2;
  std::cin >> num1;
  std::cin >> num2;
  std::cout << Maximo(num1, num2) << std::endl;
  return 0;
}
