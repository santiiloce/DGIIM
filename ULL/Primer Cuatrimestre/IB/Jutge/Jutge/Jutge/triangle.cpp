/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenier�a y Tecnolog�a
 * Grado en Ingenier�a Inform�tica
 * Inform�tica B�sica
 *
 * @author Santiago L�pez Cerro
 * @date Nov 03 2024
 * @brief  Programa que, dado un n�mero n, imprime un "tri�ngulo de tama�o n".
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
