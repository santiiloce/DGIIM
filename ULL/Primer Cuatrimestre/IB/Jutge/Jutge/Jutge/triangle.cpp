/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Informática Básica
 *
 * @author Santiago López Cerro
 * @date Nov 03 2024
 * @brief  Programa que, dado un número n, imprime un "triángulo de tamaño n".
 * The program takes directly the input and prints the output
 */
 
#include <iostream>
#include <string>

int main(){
  int size;
  std::string triangle="*";
  std::cin >> size;
  for (int i=size; i > 0; i--){
  	std::cout << triangle << std::endl;
  	triangle += "*";
  }
  return 0;
}
